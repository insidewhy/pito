#include <rbutil/conf/cmd/command_line.hpp>
#include <pito/interceptor/jail/environment.hpp>

#include "config.hpp"

#include <unistd.h>
#include <iostream>

#define PITO_PROGRAM_VERSION 0.9

namespace pito {

using namespace interceptor;

namespace cmd_line = rb::util::conf::cmd;
using rb::util::conf::value;

bool verbose = false;

void help(cmd_line::options_description const& options) {
    std::cout << "pito " << PITO_PROGRAM_VERSION << std::endl;
    std::cout << "usage: pito [arguments] <wrapper library name> <program> [program arguments]" << std::endl;
    std::cout << options << std::endl;
}

// search in $LD_LIBRARY_PATH, then installed location
void searchForLibrary(std::string const& libraryFileName) {
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

inline int main(int argc, char *argv[]) {
    {
        using cmd_line::options_description;
        // TODO: make all arguments from second positional and inclusive the 
        //       new argv/argc
        options_description options;

        bool showHelp = false;
        bool silent = false;
        options.add_options()
            ("v,verbose", verbose, "increase verbosity")
            ("h,help", showHelp, "show help")
            ("s,silent", silent, "don't say anything")
            ("l,library-dir", value(jail::preload), "pito library directory")
            ;

        if (argc < 3) {
            if (! silent) {
                help(options);
                if (argc == 2)
                    std::cout << "missing <program> argument" << std::endl;
                else
                    std::cout << "missing <wrapper library name> and <program> arguments" << std::endl;
            }
            return 1;
        }

        try {
            cmd_line::parser(argc, argv, options)();
        }
        catch (cmd_line::bad_value& e) {
            if (! silent) std::cerr << "bad value reading command line options" << std::endl;
            showHelp = true;
        }
        catch (cmd_line::expected_argument& e) {
            if (! silent) std::cerr << "expected command line argument" << std::endl;
            showHelp = true;
        }

        if (showHelp) {
            help(options);
            return 1;
        }

        std::string libraryFileName = "libpito_";
        libraryFileName.append(argv[1]).append(PITO_SHARED_LIB_FILE_EXTENSION);

        if (! jail::preload.empty()) {
            if ('/' != *(jail::preload.end() - 1)) jail::preload.append("/");
            jail::preload.append(libraryFileName);
            if (access(jail::preload.c_str(), R_OK)) searchForLibrary(libraryFileName);
        }
        else searchForLibrary(libraryFileName);

        if (jail::preload.empty()) {
            if (! silent) std::cerr << "library " << libraryFileName << " could not be found at"
                                    " install location or in $" PITO_LD_LIBRARY_PATH << std::endl;
            return 1;
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

        jail::enforce_environment();

        // TODO: set argv[2] based on path and use execv
        execvp(argv[2], argv + 2);
    }
}

}

int main(int argc, char *argv[]) {
    return pito::main(argc, argv);
}
