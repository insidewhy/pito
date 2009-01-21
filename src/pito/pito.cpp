#include <rbutil/conf/cmd/command_line.hpp>
#include "config.hpp"

#include <iostream>
#include <unistd.h>

namespace pito {

namespace cmd_line = rb::util::conf::cmd;
using rb::util::conf::value;

bool verbose = false;

inline int main(int argc, char *argv[]) {
    {
        using cmd_line::options_description;
        bool showHelp = false;
        std::string libraryPath;

        // TODO: make all arguments from second positional and inclusive the 
        //       new argv/argc
        options_description desc;
        desc.add_options()
            ("v,verbose", verbose, "increase verbosity")
            ("h,help", showHelp, "show help")
            ("l,library-dir", value(libraryPath).default_value(_LIB_DIR_), "pito library directory")
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

        if (libraryPath.empty()) {
            std::cerr << "please do not provide an empty library directory, leave it blank to use the installed location" << std::endl;
            return 1;
        }

        std::string libraryFileName = "libpito_";
        libraryFileName.append(argv[1]).append(_SHARED_LIB_FILE_EXTENSION_);

        if ('/' != *(libraryPath.end() - 1)) libraryPath.append("/");
        libraryPath.append(libraryFileName);

        if (access(libraryPath.c_str(), R_OK)) {
            // TODO: search for libraryFileName in LD_LIBRARY_PATH
            std::cerr << "library " << libraryPath << " does not exist" << std::endl;
            return 1;
        }

        // make the library an absolute path
        if (*libraryPath.begin() != '/') {
            char buff_[512];
            getcwd(buff_, sizeof(buff_));
            std::string newLibraryPath = buff_;
            newLibraryPath.append("/").append(libraryPath);
            libraryPath = newLibraryPath;
        }

        if (verbose) {
            std::cout << "load interceptor library (" << libraryPath << ")" << std::endl;
        }

        // TODO: prepend it to exist library preloads
        setenv("LD_PRELOAD", libraryPath.c_str(), 1);

        execvp(argv[2], argv + 3);
    }
}

}

int main(int argc, char *argv[]) {
    return pito::main(argc, argv);
}
