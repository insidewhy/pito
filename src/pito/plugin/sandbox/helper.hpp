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

#define PITO_SANDBOX_DEFAULT  "PITO_SANDBOX_DEFAULT"
#define PITO_SANDBOX_PATHS    "PITO_SANDBOX_PATHS"

namespace pito { namespace sandbox {

typedef char write_mode;

write_mode const WRITE_MODE_PRETEND   = 'P';
write_mode const WRITE_MODE_WHITELIST = 'W';
write_mode const WRITE_MODE_BLACKLIST = 'B';

struct context {
    context();

    std::vector<range> paths;
    write_mode         mode;
    std::unordered_map<int, std::string>  fd_map;
};

extern context& ctxt;

// would make idx = 0 a parameter of test_path, but gcc 4.5 can't handle it
template <class Tag, int idx = 0, bool FileMustExist = false>
struct sandbox_call : system_call_real<Tag> {

    typedef PITO_RETURN(Tag) return_type;

  protected:
    // executes the system call depending on the path argument
    template <bool FileMustExist_, class... Args>
    return_type test_path(chilon::realpath_type& realpath, Args... args) {
        auto path_arg = chilon::argument<idx>(args...);
        if (FileMustExist_ ?
                ! ::realpath(path_arg, realpath) :
                ! chilon::realpath(path_arg, realpath))
        {
            chilon::println(chilon::color::red,
                this->name(), ": error resolving path ", path_arg);
            return -1;
        }

        // TODO: filter realpath here

        return this->system(args...);
    }

    // test path, with default FileMustExist option
    template <class... Args>
    return_type test_path(chilon::realpath_type& realpath, Args... args) {
        return test_path<FileMustExist>(realpath, args...);
    }

    template <class... Args>
    return_type test_path(Args... args) {
        chilon::realpath_type realpath;
        return test_path(realpath, args...);
    }

  public:
    template <class... Args>
    return_type operator()(Args... args) {
        return test_path(args...);
    }
};

template <class Tag, int fdIndex = 0, int pathIndex = -1>
struct sandbox_fd_call : system_call_real<Tag> {
    // TODO:

    typedef PITO_RETURN(Tag) return_type;

    template <class... Args>
    return_type operator()(Args... args) {
        return this->system(args...);
    }
};

// if CreateFile is false, it can still possibly create the file depending
// on the arguments
template <class Tag, bool CreateFile = false>
struct sandbox_call_open : sandbox_call<Tag> {

    typedef sandbox_call<Tag> base;

    template <class Arg2, class... ModeArg>
    PITO_RETURN(Tag) operator()(const char *path, Arg2 arg2, ModeArg... mode) {
        if (! CreateFile && arg2 & O_RDONLY) {
            // no O_CREAT if there is no mode
            if (! sizeof...(mode))
                return this->system(path, arg2, mode...);
        }

        char realpath[PATH_MAX];
        auto const ret = CreateFile || sizeof...(mode) ?
            base::test_path(realpath, path, arg2) :
            base::template test_path<true>(realpath, path, arg2, mode...);

        // chilon::println(chilon::color::red, this->name(), ": ", realpath, " = ", ret);

        if (-1 != ret) ctxt.fd_map[ret] = realpath;
        return ret;
    }
};

} }

#endif
