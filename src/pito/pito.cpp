#include <rbutil/conf/cmd/command_line.hpp>

namespace pito {

namespace cmd_line = rb::util::conf::cmd;
using rb::util::conf::value;

bool verbose = false;

inline int main(int argc, char *argv[]) {
    {
        using cmd_line::options_description;

        options_description desc;
        desc.add_options()
            ("v,verbose", verbose, "increase verbosity")
            ;
    }
}

}

int main(int argc, char *argv[]) {
    return pito::main(argc, argv);
}
