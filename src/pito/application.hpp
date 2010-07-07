#ifndef PITO_APPLICATION_HPP
#define PITO_APPLICATION_HPP

#include <pito/config.hpp>
#include <pito/jail/environment.hpp>

namespace pito {

/**
 * @brief This command searches LD_LIBRARY_PATH for a given library name.
 * @param libPath The library to search for (e.g. libpito_log.so). This is system specific.
 * @param preloadLibrary The located library will be stored in this string.
 */
void search_for_preload_library(std::string const& libPath, std::string& preloadLibrary) {
    char const *ldPath = jail::getenv(PITO_LD_LIBRARY_PATH);
    if (ldPath) {
        char const *ldPathEnd = ldPath;
        while (*(++ldPathEnd) != '\0') {}

        char const *colon;
        do {
            char const *colon = std::find(ldPath, ldPathEnd, ':');
            if (colon > ldPath) {
                preloadLibrary.assign(ldPath, colon);
                preloadLibrary.append("/").append(libPath);
                if (! access(preloadLibrary.c_str(), R_OK)) return;
                else preloadLibrary = "";
            }
            else if (colon == ldPathEnd) break;

            ldPath = ++colon;
        } while (colon < ldPathEnd);
    }

    preloadLibrary = PITO_LIB_PREFIX;
    preloadLibrary.append(libPath);
    if (access(preloadLibrary.c_str(), R_OK)) preloadLibrary = "";
    else {
        // make the library an absolute path
        if (*preloadLibrary.begin() != '/') {
            char buff_[512];
            if (! getcwd(buff_, sizeof(buff_))) {
                exit(1);
            }
            else {
                std::string newLibraryPath = buff_;
                newLibraryPath.append("/").append(preloadLibrary);
                preloadLibrary = newLibraryPath;
            }
        }
    }
}

/**
 * @brief This command searches LD_LIBRARY_PATH for a given library name.
 * @param libPath The library to search for. This will be modified to represent the system library name (so if liblog is given it will be replaced with liblog.so on Linux).
 * @param preloadLibrary The located library will be stored in this string.
 */
void search_for_preload_library(std::string& libPath, std::string& preloadLibrary) {
    libPath.append(PITO_SHARED_LIB_FILE_EXTENSION);
    search_for_preload_library(
        static_cast<std::string const &>(libPath), preloadLibrary);
}

/**
 * @brief This command searches LD_LIBRARY_PATH for a given library name with a user provided search path override.
 * @param libPath The library to search for (e.g. liblog will search for liblog.so).
 * @param preloadLibrary The located library will be stored in this string.
 * @param preloadLibrary The override path to search for libraries in.
 */
void search_for_preload_library(std::string& libPath, std::string& preloadLibrary, std::string const& pathOverride) {
    libPath.append(PITO_SHARED_LIB_FILE_EXTENSION);
    if (! pathOverride.empty()) {
        if ('/' != *(preloadLibrary.end() - 1)) preloadLibrary.append("/");
        preloadLibrary.append(libPath);
        if (! access(preloadLibrary.c_str(), R_OK)) return;
    }
    search_for_preload_library(
        static_cast<std::string const &>(libPath), preloadLibrary);
}

}

#endif
