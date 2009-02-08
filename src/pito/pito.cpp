#include <rbutil/conf/cmd/command_line.hpp>
#include <pito/interceptor/application.hpp>
#include <pito/interceptor/jail/environment.hpp>

#include <pito/config.hpp>

#include <unistd.h>
#include <iostream>

#define PITO_PROGRAM_VERSION "0.9.1"

namespace pito {

namespace jail = interceptor::jail;
namespace cmd_line = rb::util::conf::cmd;
using rb::util::conf::value;

bool verbose = false;

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
            .help("h,help", "pito " PITO_PROGRAM_VERSION
                  "\nusage: pito [arguments] <wrapper library name> <program> [program arguments]")
            ("s,silent", silent, "don't say anything")
            ("l,library-dir", value(jail::preload), "pito library directory")
            ;

        if (argc < 3) {
            if (! silent) {
                if (argc == 2)
                    std::cout << "missing <program> argument, see --help" << std::endl;
                else
                    std::cout << "missing <wrapper library name> and <program> arguments, see --help" << std::endl;
            }
            return 1;
        }

        try {
            if (silent) cmd_line::parser(argc, argv, options)();
            else cmd_line::parser(argc, argv, options)(std::cerr);
        }
        catch (cmd_line::invalid_arguments& ) {
            return 1;
        }

        std::string libraryFileName = "libpito_";
        libraryFileName.append(argv[1]);

        interceptor::search_for_preload_library(libraryFileName, jail::preload, jail::preload);

        if (jail::preload.empty()) {
            if (! silent) std::cerr << "library " << libraryFileName << " could not be found at"
                                    " install location or in $" PITO_LD_LIBRARY_PATH << std::endl;
        } 
        else {
            if (verbose)
                std::cerr << "load interceptor library (" << jail::preload << ")" << std::endl;
            jail::enforce_environment();
            // consider setting argv[2] based on path and use execv
            execvp(argv[2], argv + 2);
        }
        return 1;
    }
}

}

int main(int argc, char *argv[]) {
    return pito::main(argc, argv);
}
