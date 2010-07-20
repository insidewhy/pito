#ifndef PITO_SANDBOX_SYSTEM_CALL_HPP
#define PITO_SANDBOX_SYSTEM_CALL_HPP
#include <pito/plugin/sandbox/helper.hpp>

namespace pito { namespace sandbox {

using namespace system_call_tag;

template <class Tag>
struct system_call : system_call_real<Tag> {
    template <class... Args>
    PITO_RETURN(Tag) operator()(Args... args) {
        return this->system(args...);
    }
};

template <>
struct system_call<chmod> : sandbox_call<chmod> {};

template <>
struct system_call<fchmod> : sandbox_fd_call<fchmod> {};

template <>
struct system_call<fchmodat> : sandbox_call<fchmodat, dir_fd<0>> {};

template <>
struct system_call<chown> : sandbox_call<chown> {};

template <>
struct system_call<fchown> : sandbox_fd_call<fchown> {};

template <>
struct system_call<fchownat> : sandbox_call<fchownat, dir_fd<0>> {};

template <>
struct system_call<open> : sandbox_call_open<open> {};

template <>
struct system_call<open64> : sandbox_call_open<open64> {};

template <>
struct system_call<openat> : sandbox_call_open<openat, dir_fd<0>> {};

template <>
struct system_call<openat64> : sandbox_call_open<openat64, dir_fd<0>> {};

template <>
struct system_call<creat> : sandbox_call_open<creat, create_file> {};

template <>
struct system_call<creat64> : sandbox_call_open<creat64, create_file> {};

template <>
struct system_call<fopen> : sandbox_call_fopen<fopen> {};

template <>
struct system_call<fopen64> : sandbox_call_fopen<fopen64> {};

template <>
struct system_call<freopen> : sandbox_call_fopen<freopen> {};

template <>
struct system_call<lchown> : sandbox_call<lchown, on_symlink> {};

template <>
struct system_call<link>
  : sandbox_call_link<link, path_index<1>, create_file> {};

template <>
struct system_call<linkat>
  : sandbox_call_link<linkat, dir_fd<2>, create_file> {};

template <>
struct system_call<mkdir> : sandbox_call<mkdir, create_file> {};

template <>
struct system_call<mkdirat>
  : sandbox_call<mkdirat, dir_fd<0>, create_file> {};

template <>
struct system_call<mknod> : sandbox_call<mknod, create_file> {};

template <>
struct system_call<mknodat> : sandbox_call<mknodat, dir_fd<0>, create_file> {};

template <>
struct system_call<mkfifo> : sandbox_call<mkfifo, create_file> {};

template <>
struct system_call<mkfifoat> : sandbox_call<mkfifoat, dir_fd<0>, create_file> {};

template <>
struct system_call<rename> : sandbox_call_rename<rename> {};

template <>
struct system_call<renameat> : sandbox_call_rename<renameat> {};

template <>
struct system_call<rmdir> : sandbox_call<rmdir> {};

template <>
struct system_call<symlink>
  : sandbox_call<symlink, path_index<1>, create_file> {};

template <>
struct system_call<symlinkat>
  : sandbox_call<symlinkat, dir_fd<1>, create_file> {};

template <>
struct system_call<truncate> : sandbox_call<truncate> {};

template <>
struct system_call<truncate64> : sandbox_call<truncate64> {};

template <>
struct system_call<unlink> : sandbox_call<unlink, on_symlink> {};

template <>
struct system_call<unlinkat>
  : sandbox_call<unlinkat, dir_fd<0>, on_symlink> {};

template <>
struct system_call<utime> : sandbox_call<utime> {};

template <>
struct system_call<utimes> : sandbox_call<utimes> {};

template <>
struct system_call<utimensat>
  : sandbox_call<utimensat, dir_fd<0>> {};

template <>
struct system_call<futimesat>
  : sandbox_call<futimesat, dir_fd<0>> {};

template <>
struct system_call<lutimes> : sandbox_call<lutimes, on_symlink> {};

} }

#endif
