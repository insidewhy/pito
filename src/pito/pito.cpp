#include <rbutil/conf/cmd/command_line.hpp>
#include <pito/interceptor/application.hpp>
#include <pito/config.hpp>

#include <iostream>

/**
 * @file This is a utility to run a process (it searches $PATH) with
 *       a specified library. e.g. pito log ls -l, sets the LD_PRELOAD
 *       environment up to
 *          LD_PRELOAD=<pito_library_location from config.hpp>/libpito_log.so
 *       And runs ls -l
 */

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
            .help("pito " PITO_PROGRAM_VERSION "\nusage: pito [arguments] "
                  "<wrapper library name> <program> [program arguments]")
            ("s,silent", silent, "don't say anything")
            ("l,library-dir", value(jail::preload), "pito library directory")
            ;

        try {
            int nPositionals = silent ?
                cmd_line::parser(argc, argv, options)().n_positionals() :
                cmd_line::parser(argc, argv, options)(std::cerr).n_positionals();

            if (nPositionals < 2) {
                if (! silent) {
                    if (1 == nPositionals)
                        std::cerr << "missing <program> argument" << std::endl;
                    else
                        std::cerr << "missing <wrapper library name> and <program> arguments" << std::endl;
                    std::cerr << options << std::endl;
                }
                return 1;
            }
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
            if (verbose) std::cerr << "load interceptor library (" << jail::preload << ")" << std::endl;
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
