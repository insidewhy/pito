#ifndef PITO_SANDBOX_HELPER_HPP
#define PITO_SANDBOX_HELPER_HPP

#include <pito/system_call.hpp>
#include <pito/lib/c_traits.hpp>

#include <chilon/iterator_range.hpp>
#include <chilon/print.hpp>
#include <chilon/argument.hpp>
#include <chilon/realpath.hpp>

#include <vector>
#include <unordered_map>

#include <sys/stat.h>

#define PITO_SANDBOX_DEFAULT  "PITO_SANDBOX_DEFAULT"
#define PITO_SANDBOX_PATHS    "PITO_SANDBOX_PATHS"

namespace pito { namespace sandbox {

namespace color = chilon::color;

typedef char write_mode;

write_mode const WRITE_MODE_UNKNOWN   = 'U';
write_mode const WRITE_MODE_PRETEND   = 'P';
write_mode const WRITE_MODE_WHITELIST = 'W';
write_mode const WRITE_MODE_BLACKLIST = 'B';

struct context {
    context();

    std::vector<range> paths;
    write_mode         default_mode;
};

extern context& ctxt;

// would make idx = 0 a parameter of test_path, but gcc 4.5 can't handle it
template <class Tag, int idx = 0, bool FileMustExist = false>
struct sandbox_call : system_call_real<Tag> {

    typedef PITO_RETURN(Tag) return_type;

  protected:
    // executes the system call depending on the path argument
    template <bool FileMustExist_, class... Args>
    write_mode path_type(chilon::realpath_type& realpath, Args... args) {
        auto path_arg = chilon::argument<idx>(args...);
        if (FileMustExist_ ?
                ! ::realpath(path_arg, realpath) :
                ! chilon::realpath(path_arg, realpath))
        {
            chilon::println(color::red,
                this->name(), ": error resolving path ", path_arg);
            return WRITE_MODE_UNKNOWN;
        }

        for (auto it = ctxt.paths.begin(); it != ctxt.paths.end(); ++it) {
            if (std::equal(it->begin() + 1, it->end(), realpath)) {
                char const last = realpath[it->size() - 1];
                if ('/' == last || '\0' == last) return it->front();
            }
        }

        return WRITE_MODE_BLACKLIST;
    }

    // test path, with default FileMustExist option
    template <class... Args>
    return_type path_type(chilon::realpath_type& realpath, Args... args) {
        return path_type<FileMustExist>(realpath, args...);
    }

    template <class... Args>
    return_type test_path(Args... args) {
        chilon::realpath_type realpath;
        write_mode const write_type = path_type(realpath, args...);
        switch (write_type) {
            case WRITE_MODE_WHITELIST:
                return this->system(args...);
            case WRITE_MODE_BLACKLIST:
                errno = EACCES;
                return -1;
            case WRITE_MODE_PRETEND:
                return 0;
        }
    }

  public:
    template <class... Args>
    return_type operator()(Args... args) {
        return test_path(args...);
    }
};

template <class Tag, int fdIndex = 0, int pathIndex = -1>
struct sandbox_fd_call : system_call_real<Tag> {
    // todo:

    typedef PITO_RETURN(Tag) return_type;

    template <class... Args>
    return_type operator()(Args... args) {
        // todo: remember to check for AT_FDCWD
        return this->system(args...);
    }
};

// if CreateFile is false, it can still possibly create the file depending
// on the arguments
template <class Tag, bool CreateFile = false>
struct sandbox_call_open : sandbox_call<Tag> {

    typedef sandbox_call<Tag> base;

    template <class Arg2, class... ModeArg>
    PITO_RETURN(Tag) operator()(const char *path, Arg2 oflag, ModeArg... mode) {
        // can't test & with O_RDONLY because O_RDONLY can be 0
        if (! CreateFile && ! (oflag & (O_WRONLY | O_RDWR))) {
            // no O_CREAT if there is no mode
            if (! sizeof...(mode))
                return this->system(path, oflag, mode...);
        }

        char realpath[PATH_MAX];
        auto const write_type = CreateFile || sizeof...(mode) ?
            base::path_type(realpath, path, oflag) :
            base::template path_type<true>(realpath, path, oflag, mode...);

        switch (write_type) {
            case WRITE_MODE_WHITELIST: {
                return this->system(path, oflag, mode...);
            }

            case WRITE_MODE_BLACKLIST:
                errno = EACCES;
                chilon::println(color::red,
                    this->name(), ": ", realpath, " DENIED");

                return -1;

            case WRITE_MODE_PRETEND:
                chilon::println(color::red,
                    this->name(), ": ", realpath, " PRETEND");

                return this->system("/dev/null", oflag, mode...);
        }

        assert(false);
    }
};

} }

#endif
