// This define is used by pito/jail/c.hpp and pito/lib/c.hpp to work
// out where to direct system calls. In this case the system calls
// go through the template class pito::log::system_call.
#define PITO_SYSTEM_CALL_BASE  log::system_call
#define PITO_LOG_PID
#include <pito/plugin/log/helper.hpp>
#include <pito/jail/c.hpp>
#include <pito/lib/c.hpp>
