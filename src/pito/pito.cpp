#include <rbutil/conf/cmd/command_line.hpp>
#include <iostream>

namespace pito {

namespace cmd_line = rb::util::conf::cmd;
using rb::util::conf::value;

bool verbose = false;

inline int main(int argc, char *argv[]) {
    {
        using cmd_line::options_description;
        bool showHelp = false;

        options_description desc;
        desc.add_options()
            ("v,verbose", verbose, "increase verbosity")
            ("h,help", showHelp, "show help")
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

        if (showHelp) {
            // std::cout << desc << std::endl;
            return 1;
        }
    }
}

}

int main(int argc, char *argv[]) {
    return pito::main(argc, argv);
}
