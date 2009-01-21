#include <rbutil/conf/cmd/command_line.hpp>
#include <iostream>
#include "config.hpp"

namespace pito {

namespace cmd_line = rb::util::conf::cmd;
using rb::util::conf::value;

bool verbose = false;

inline int main(int argc, char *argv[]) {
    {
        using cmd_line::options_description;
        bool showHelp = false;
        std::string libraryDir;

        options_description desc;
        desc.add_options()
            ("v,verbose", verbose, "increase verbosity")
            ("h,help", showHelp, "show help")
            ("l,library-dir", value(libraryDir).default_value(_LIB_DIR_), "pito library directory")
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

        if (verbose) {
            std::cout << "load interceptor library (" << libraryDir << "libpito_" << argv[1] << _SHARED_LIB_FILE_EXTENSION_ ")" << std::endl;
        }
    }
}

}

int main(int argc, char *argv[]) {
    return pito::main(argc, argv);
}
