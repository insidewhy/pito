#ifndef PITO_SYSTEM_CALL_HPP
#define PITO_SYSTEM_CALL_HPP

#include <pito/library.hpp>
#include <pito/lib/traits.hpp>

#include <chilon/meta/function.hpp>
#include <chilon/singleton.hpp>

#include <dlfcn.h>
#include <string>

namespace pito {

using namespace chilon;

template <class Tag>
struct system_call;

namespace detail {
    template <class Tag>
    struct system_call : traits<Tag> {
        typedef traits<Tag>  type_base;

        // to handle variadic c functions, must accept other args
        template <class... Args>
        typename type_base::return_type operator()(Args... args) {
            if (! call_) {
                // the following might be needed for another architecture
                // call_ = reinterpret_cast<call_t>(
                //     dlsym(
                //         library_instance<LibraryTag>().handle(),
                //         name_.c_str()));
                call_ =
                    reinterpret_cast<typename type_base::call_t>(
                        dlsym(RTLD_NEXT, type_base::name()));
            }
            return call_(args...);
        }

        system_call() : call_(0) {}
      private:
        typename type_base::call_t call_;
    };
}

template <class Tag>
system_call<Tag>& system_call_instance() {
    return chilon::singleton< system_call<Tag> >::instance();
}

}

#define PITO_CALL(name_)   system_call_instance<system_call_tag::name_>()

#define PITO_ARGS_HELPER(name_, nArgs_) CHILON_ARGS(system_call<name_>::arg_types, nArgs_)
#define PITO_ARGS(name_) PITO_ARGS_HELPER(name_, PITO_NARGS_##name_)

#define PITO_ARG_NAMES_HELPER(nArgs_) CHILON_ARG_NAMES(nArgs_)
#define PITO_ARG_NAMES(name_) PITO_ARG_NAMES_HELPER(PITO_NARGS_##name_)

#define PITO_SYSTEM_CALL_WITH_BASE(name_, base_) \
    template <> \
    struct system_call<system_call_tag::name_> \
      : base_ <system_call_tag::name_> {}; \
    extern "C" { \
        system_call<system_call_tag::name_>::return_type  name_(PITO_ARGS(name_)) { \
            return PITO_CALL(name_)(PITO_ARG_NAMES(name_)); \
        } \
    }

#define PITO_SYSTEM_CALL(name_) \
    PITO_SYSTEM_CALL_WITH_BASE(name_, PITO_SYSTEM_CALL_BASE)

#define PITO_RETURN(name_)   \
    typename detail::system_call<name_>::return_type

#define PITO_SUPER(name_, ...)   \
    detail::system_call<name_>::operator()(__VA_ARGS__)

#endif
