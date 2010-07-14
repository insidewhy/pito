#ifndef PITO_SANDBOX_HELPER_HPP
#define PITO_SANDBOX_HELPER_HPP

#include <pito/system_call.hpp>
#include <pito/lib/c_traits.hpp>

#include <chilon/iterator_range.hpp>
#include <chilon/print.hpp>

#include <vector>
#include <unordered_map>

#include <fcntl.h>

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
template <class Tag, int idx = 0, bool IsLink = false>
struct sandbox_call : system_call_real<Tag> {

    typedef PITO_RETURN(Tag) return_type;

  protected:
    template <class... Args>
    return_type test_path(std::unique_ptr<char>& realpath,
                          Args...                args)
    {
        return this->system(args...);
    }

    template <class... Args>
    return_type test_path(Args... args) {
        std::unique_ptr<char> realpath;
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

    typedef PITO_RETURN(Tag) return_type;

  protected:
    template <class... Args>
    return_type test_path(std::unique_ptr<char>& realpath,
                          Args...                args)
    {
        return this->system(args...);
    }

    template <class... Args>
    return_type test_path(Args... args) {
        std::unique_ptr<char> realpath;
        return test_path(realpath, args...);
    }

  public:
    template <class... Args>
    return_type operator()(Args... args) {
        return test_path(args...);
    }
};

template <class Tag, bool TestWrite = true>
struct sandbox_call_open : sandbox_call<Tag> {

    template <class P>
    int check_status(P const& path, int const status) const {
        return status;
    }

    template <class Arg2, class... ModeArg>
    PITO_RETURN(Tag) operator()(const char *path, Arg2 arg2, ModeArg... mode) {
        if (TestWrite && arg2 & O_RDONLY) {
            if (1 == sizeof...(mode)) {
                // if the file doesn't exist it could be created so this
                // is a write operation.. for now fall through and block
            }
            else return this->system(path, arg2, mode...);
        }

        std::unique_ptr<char> realpath;
        int ret = sandbox_call<Tag>::test_path(path, arg2, mode...);
        if (-1 != ret) ctxt.fd_map[ret] = realpath.get();
        return ret;
    }
};

} }

#endif
