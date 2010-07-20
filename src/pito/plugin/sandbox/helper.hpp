#ifndef PITO_SANDBOX_HELPER_HPP
#define PITO_SANDBOX_HELPER_HPP

#include <pito/system_call.hpp>
#include <pito/lib/c_traits.hpp>
#include <pito/config.hpp>

#include <chilon/iterator_range.hpp>
#include <chilon/print.hpp>
#include <chilon/argument.hpp>
#include <chilon/filesystem/realpath.hpp>
#include <chilon/meta/contains.hpp>
#include <chilon/meta/find_int.hpp>
#include <chilon/meta/same.hpp>
#include <chilon/meta/at.hpp>
#include <chilon/meta/contains.hpp>

#include <vector>
#include <unordered_map>
#include <cmath>

#include <sys/stat.h>

#define PITO_SANDBOX_DEFAULT  "PITO_SANDBOX_DEFAULT"
#define PITO_SANDBOX_PATHS    "PITO_SANDBOX_PATHS"

namespace pito { namespace sandbox {

namespace meta = chilon::meta;
namespace fs = chilon::filesystem;

// options
struct create_file;
struct on_symlink;
template <int i> struct path_index;
template <int i> struct dir_fd;
// end options

template <class Tag>
struct system_call;

namespace color = chilon::color;

typedef char write_mode;

// unknown is A, so the alphabetical order is the same as the precedence
write_mode const WRITE_MODE_UNKNOWN   = 'A';
write_mode const WRITE_MODE_BLACKLIST = 'B';
write_mode const WRITE_MODE_PRETEND   = 'P';
write_mode const WRITE_MODE_WHITELIST = 'W';

struct context {
    context();

    std::vector<range> paths;
    write_mode         default_mode;
};

extern context& ctxt;

template <class Tag, class... Options>
struct sandbox_call : system_call_real<Tag> {
    typedef PITO_RETURN(Tag) return_type;

  protected:
    enum {
        CreateFile =
            meta::contains<create_file, Options...>::value
    };

    enum { DirFdIdx = meta::find_int<dir_fd, -1, Options...>::value };

    enum { PathIdx = meta::find_int<path_index, DirFdIdx + 1, Options...>::value };

    system_call<Tag>& mixin() {
        return static_cast< system_call<Tag> & >(*this);
    }

    template <class... Args>
    return_type pretend(Args... args) const { return 0; }

    return_type blacklist() { return -1; }

    template <class... Args>
    char const *path_arg(Args... args) const {
        return chilon::argument<PathIdx>(args...);
    }

    // gets write mode for a path
    template <int DirFdIdx_, bool CreateFile_, class... Args>
    CHILON_RETURN_REQUIRE_I(write_mode, DirFdIdx_ == -1)
    call_mode(fs::realpath_type& realpath, Args... args) {
        return path_mode<CreateFile_>(realpath, path_arg(args...));
    }

    template <int DirFdIdx_, bool CreateFile_, class... Args>
    CHILON_RETURN_REQUIRE_I(write_mode, DirFdIdx_ > -1)
    call_mode(fs::realpath_type& realpath, Args... args) {
        auto path = path_arg(args...);
        if (! path)
            return WRITE_MODE_UNKNOWN;

        auto const dirfd = chilon::argument<DirFdIdx_>(args...);

        if ('/' == *path || AT_FDCWD == dirfd)
            return path_mode<CreateFile_>(realpath, path);

        fs::realpath_type abs_path;
        if (! get_fd_path(abs_path, dirfd))
            return WRITE_MODE_UNKNOWN;

        auto abs_path_it = chilon::end(abs_path);
        *abs_path_it = '/';
        for (auto it = path; *it != '\0'; ++it) {
            *(++abs_path_it) = *it;
        }
        *(++abs_path_it) = '\0';

        return path_mode<CreateFile_>(realpath, abs_path);
    }

    template <bool CreateFile_, class... Args>
    write_mode call_mode(fs::realpath_type& realpath, Args... args) {
        return call_mode<DirFdIdx, CreateFile_>(realpath, args...);
    }

    // test path, with default CreateFile option
    template <class... Args>
    write_mode call_mode(fs::realpath_type& realpath, Args... args) {
        return call_mode<DirFdIdx, CreateFile>(realpath, args...);
    }

    template <bool CreateFile_, class... Args>
    write_mode path_mode(fs::realpath_type& realpath, char const *path) {
        if (CreateFile_ ?
                ! fs::realpath(path, realpath) :
                (meta::contains<on_symlink, Options...>::value ?
                    ! fs::realpath_new(path, realpath) :
                    ! ::realpath(path, realpath)))
        {
            chilon::println(color::red,
                this->name(), ": error resolving path ", path);
            return WRITE_MODE_UNKNOWN;
        }
        else return absolute_path_mode(realpath);
    }

    write_mode absolute_path_mode(fs::realpath_type const& realpath) const {
        for (auto it = ctxt.paths.begin(); it != ctxt.paths.end(); ++it) {
            if (std::equal(it->begin() + 1, it->end(), realpath)) {
                char const last = realpath[it->size() - 1];
                if ('/' == last || '\0' == last) return it->front();
            }
        }

        return ctxt.default_mode;
    }

    template <bool CreateFile_, class... Args>
    return_type run(Args... args) {
        fs::realpath_type realpath;

        return handle_mode(
            call_mode<CreateFile_>(realpath, args...),
            realpath,
            args...);
    }

    template <class... Args>
    return_type handle_mode(
        write_mode const         write_type,
        fs::realpath_type const& realpath,
        Args...                  args)
    {
        switch (write_type) {
            case WRITE_MODE_PRETEND:
                chilon::println(color::red,
                    this->name(), ": ", realpath, " PRETEND");

                return this->mixin().pretend(args...);

            case WRITE_MODE_WHITELIST:
                return this->system(args...);

            case WRITE_MODE_BLACKLIST:
                errno = EACCES;
                chilon::println(color::red,
                    this->name(), ": ", realpath, " DENIED");

                return this->mixin().blacklist();

            default:
                errno = EACCES;
                return this->mixin().blacklist();
        }
    }

    template <class... Args>
    return_type handle_path(
        fs::realpath_type const& realpath,
        Args...                  args)
    { return handle_mode(absolute_path_mode(realpath), realpath, args...); }


    bool get_fd_path(fs::realpath_type& realpath, int fd) const {
        // 128-bit.. nah
        char proc_path[sizeof(PITO_PROC_FD "/") + PITO_MAX_FD_LENGTH];
        std::copy(PITO_PROC_FD "/", chilon::end(PITO_PROC_FD "/"), proc_path);

        int const fd_length = static_cast<int>(std::log10(fd));
        if (fd_length > PITO_MAX_FD_LENGTH)
            return false;

        char *proc_ptr = proc_path + sizeof(PITO_PROC_FD "/") + fd_length;

        for (*proc_ptr = '\0'; fd > 0; fd /= 10)
            *(--proc_ptr) = '0' + (fd % 10);

        return ::realpath(proc_path, realpath);
    }

    template <class... Args>
    return_type run(Args... args) {
        return run<CreateFile>(args...);
    }

  public:
    template <class... Args>
    return_type operator()(Args... args) {
        return run(args...);
    }
};

// if CreateFile is true, it is still possible for the file to
// exist, depending on the arguments to the call
template <class Tag, class... Opts>
struct sandbox_call_open : sandbox_call<Tag, Opts...> {
    typedef sandbox_call<Tag, Opts...> base;
    typedef PITO_RETURN(Tag)           return_type;

    template <class Path, class... Args>
    return_type pretend(Path, Args... args) {
        return this->system("/dev/null", args...);
    }

    template <class Path, class... Args>
    return_type pretend(int const dirfd, Path, Args... args) {
        return this->system(dirfd, "/dev/null", args...);
    }

    template <class... Args>
    return_type operator()(Args... args) {
        enum {
            FlagIdx = meta::same<
                typename meta::head<Args...>::type, int>::value + 1
        };

        enum {
            CreateFile =
                base::CreateFile || FlagIdx + 1 < sizeof...(args)
        };

        auto const oflag = argument<FlagIdx>(args...);

        // can't test & with O_RDONLY because O_RDONLY can be 0
        if (! CreateFile && ! (oflag & (O_WRONLY | O_RDWR)))
            return this->system(args...);
        else
            return this->template run<CreateFile>(args...);
    }
};

template <class Tag>
struct sandbox_fd_call : sandbox_call<Tag> {
    template <class... Args>
    PITO_RETURN(Tag) operator()(int fd, Args... args) {
        fs::realpath_type realpath;
        if (! this->get_fd_path(realpath, fd))
            return this->blacklist();
        else
            return this->handle_path(realpath, fd, args...);
    }
};

template <class Tag>
struct sandbox_call_fopen : sandbox_call_open<Tag> {
    typedef PITO_RETURN(Tag)  return_type;

    return_type blacklist() { return 0; }

    template <class Path, class... Args>
    return_type pretend(Path, Args... args) {
        return this->system("/dev/null", args...);
    }

    template <class... Stream>
    return_type operator()(const char *path,
                           const char *mode,
                           Stream...   stream)
    {
        if (! *mode)
            return this->system(path, mode, stream...);

        if ('r' == *mode) {
            if ('+' == *(mode + 1))
                return this->template run<true>(path, mode, stream...);
            else
                return this->system(path, mode, stream...);
        }
        else
            return this->run(path, mode, stream...);
    }
};

template <class Tag, class... Options>
struct sandbox_call_link : sandbox_call<Tag, Options...> {
    typedef PITO_RETURN(Tag) return_type;

    // TODO: stop file being hard linked to less permissive path in next 2
    return_type operator()(const char *source, const char *dest) {
        return this->system(source, dest);
    }

    return_type operator()(int olddirfd, const char *oldpath,
                           int newdirfd, const char *newpath, int flags)
    {
        return this->system(olddirfd, oldpath, newdirfd, newpath, flags);
    }
};

template <class Tag>
struct sandbox_call_rename : sandbox_call<Tag> {
    typedef PITO_RETURN(Tag) return_type;

    // TODO: protect oldpath and newpath
    return_type operator()(const char *oldpath, const char *newpath) {
        return this->system(oldpath, newpath);
    }

    return_type operator()(int olddirfd, const char *oldpath,
                           int newdirfd, const char *newpath)
    {
        return this->system(olddirfd, oldpath, newdirfd, newpath);
    }
};

} }

#endif
