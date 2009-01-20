#include <pito/interceptor/lib/c.hpp>

extern "C" {

using namespace pito::interceptor;

int open(const char *pathname, int flags, mode_t mode) {
    std::cout << "wrapping open(" << pathname << ", " << flags << ", " << mode << ")\n";
    return PITO_SUPER(open)(pathname, flags, mode);
}

int open64(const char *pathname, int flags, mode_t mode) {
    std::cout << "wrapping open64(" << pathname << ", " << flags << ", " << mode << ")\n";
    return PITO_SUPER(open)(pathname, flags, mode);
}

}
