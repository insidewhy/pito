#ifndef PITO_INTERCEPTOR_APPLICATION_HPP
#define PITO_INTERCEPTOR_APPLICATION_HPP

#include <pito/config.hpp>
#include <pito/interceptor/jail/environment.hpp>

namespace pito { namespace interceptor {

namespace detail {
    void search_for_preload_library(std::string const& libraryFileName, std::string& preloadLibrary) {
        char const *ldPath = jail::getenv(PITO_LD_LIBRARY_PATH);
        if (ldPath) {
            char const *ldPathEnd = ldPath;
            while (*(++ldPathEnd) != '\0') {}

            char const *colon = ldPath;
            do {
                colon = std::find(colon, ldPathEnd, ':');
                if (colon != ldPath) {
                    preloadLibrary.assign(ldPath, colon);
                    preloadLibrary.append("/").append(libraryFileName);
                    if (! access(preloadLibrary.c_str(), R_OK)) break;
                    else preloadLibrary = "";
                }
                ldPath = ++colon; 
            } while (colon < ldPathEnd);
        }

        preloadLibrary = PITO_LIB_PREFIX;
        preloadLibrary.append(libraryFileName);
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
}

void search_for_preload_library(std::string& libraryFileName, std::string& preloadLibrary) {
    libraryFileName.append(PITO_SHARED_LIB_FILE_EXTENSION);
    detail::search_for_preload_library(libraryFileName, preloadLibrary);
}


// search in $LD_LIBRARY_PATH, then installed location
void search_for_preload_library(std::string& libraryFileName, std::string& preloadLibrary, std::string const& pathOverride) {
    libraryFileName.append(PITO_SHARED_LIB_FILE_EXTENSION);
    if (! pathOverride.empty()) {
        if ('/' != *(preloadLibrary.end() - 1)) preloadLibrary.append("/");
        preloadLibrary.append(libraryFileName);
        if (! access(preloadLibrary.c_str(), R_OK)) return;
    }
    detail::search_for_preload_library(libraryFileName, preloadLibrary);
}

} }

#endif
