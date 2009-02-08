#ifndef PITO_LIBRARY_HPP
#define PITO_LIBRARY_HPP

#include <pito/interceptor/jail/environment.hpp>

#include "config.hpp"

namespace pito {

namespace jail = interceptor::jail;

namespace detail {
    void search_for_preload_library(std::string const& libraryFileName) {
        char const *ldPath = jail::getenv(PITO_LD_LIBRARY_PATH);
        if (ldPath) {
            char const *ldPathEnd = ldPath;
            while (*(++ldPathEnd) != '\0') {}

            char const *colon = ldPath;
            do {
                colon = std::find(colon, ldPathEnd, ':');
                if (colon != ldPath) {
                    jail::preload.assign(ldPath, colon);
                    jail::preload.append("/").append(libraryFileName);
                    if (! access(jail::preload.c_str(), R_OK)) return;
                    else jail::preload = "";
                }
                ldPath = ++colon; 
            } while (colon < ldPathEnd);
        }

        jail::preload = PITO_LIB_DIR;
        jail::preload.append(libraryFileName);
        if (access(jail::preload.c_str(), R_OK)) jail::preload = "";
    }
}

void search_for_preload_library(std::string& libraryFileName) {
    libraryFileName.append(PITO_SHARED_LIB_FILE_EXTENSION);
    detail::search_for_preload_library(libraryFileName);
}


// search in $LD_LIBRARY_PATH, then installed location
void search_for_preload_library(std::string& libraryFileName, std::string const& pathOverride) {
    libraryFileName.append(PITO_SHARED_LIB_FILE_EXTENSION);
    if ('/' != *(jail::preload.end() - 1)) jail::preload.append("/");
    jail::preload.append(libraryFileName);
    if (access(jail::preload.c_str(), R_OK)) detail::search_for_preload_library(libraryFileName);
}

}

#endif
