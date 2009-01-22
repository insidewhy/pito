#include <rbutil/conf/cmd/command_line.hpp>
#include <pito/interceptor/jail/environment.hpp>

#include "config.hpp"

#include <iostream>
#include <unistd.h>

namespace pito {

using namespace interceptor;

namespace cmd_line = rb::util::conf::cmd;
using rb::util::conf::value;

bool verbose = false;

inline int main(int argc, char *argv[]) {
    {
        using cmd_line::options_description;
        bool showHelp = false;

        // TODO: make all arguments from second positional and inclusive the 
        //       new argv/argc
        options_description desc;
        desc.add_options()
            ("v,verbose", verbose, "increase verbosity")
            ("h,help", showHelp, "show help")
            ("l,library-dir", value(jail::preload).default_value(_LIB_DIR_), "pito library directory")
            ;

        try {
            cmd_line::parser(argc, argv, desc)();
        }
        catch (cmd_line::bad_value& e) {
            std::cerr << "bad value reading command line options" << std::endl;
            showHelp = true;
        }
        catch (cmd_line::expected_argument& e) {
            std::cerr << "expected command line argument" << std::endl;
            showHelp = true;
        }

        if (showHelp || argv[1] == 0) {
            // std::cout << desc << std::endl;
            return 1;
        }

        if (jail::preload.empty()) {
            std::cerr << "please do not provide an empty library directory, leave it blank to use the installed location" << std::endl;
            return 1;
        }

        std::string libraryFileName = "libpito_";
        libraryFileName.append(argv[1]).append(_SHARED_LIB_FILE_EXTENSION_);

        if ('/' != *(jail::preload.end() - 1)) jail::preload.append("/");
        jail::preload.append(libraryFileName);

        if (access(jail::preload.c_str(), R_OK)) {
            char const *ldPath = getenv("LD_LIBRARY_PATH");
            if (ldPath) {
                char const *ldPathEnd = ldPath;
                while (*(++ldPathEnd) != '\0') {}

                char const *colon = ldPath;
                do {
                    colon = std::find(colon + 1, ldPathEnd, ':');
                    // TODO: search for libraryFileName in ldPath,colon

                    jail::preload.assign(ldPath, colon);
                    jail::preload.append("/").append(libraryFileName);
                    if (! access(jail::preload.c_str(), R_OK)) break;
                    else jail::preload = "";

                    ldPath = colon;
                } while (colon != ldPathEnd);

                if (jail::preload.empty()) {
                    std::cerr << "library " << libraryFileName << " could not be found" << std::endl;
                    return 1;
                }
            }
            else {
                std::cerr << "library " << jail::preload << " does not exist" << std::endl;
                return 1;
            }
        }

        // make the library an absolute path
        if (*jail::preload.begin() != '/') {
            char buff_[512];
            getcwd(buff_, sizeof(buff_));
            std::string newLibraryPath = buff_;
            newLibraryPath.append("/").append(jail::preload);
            jail::preload = newLibraryPath;
        }

        if (verbose)
            std::cout << "load interceptor library (" << jail::preload << ")" << std::endl;

        jail::enforceEnvironment();

        // TODO: set argv[2] based on path and use execv
        execvp(argv[2], argv + 2);
    }
}

}

int main(int argc, char *argv[]) {
    return pito::main(argc, argv);
}
