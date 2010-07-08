#define PITO_SYSTEM_CALL_BASE  sandbox::system_call
#include <pito/plugin/sandbox/helper.hpp>
#include <pito/jail/c.hpp>
#include <pito/lib/c.hpp>

#include <pito/plugin/init.hpp>

#include <chilon/conf/cmd/command_line.hpp>

namespace cmd_line = chilon::conf::cmd;
using chilon::conf::value;

extern "C" {

int sandbox_init(int offset, int argc, char *argv[]) {
    using cmd_line::options_description;
    options_description options;

    // TODO: add some environment setters
    options.add_options()
        .help("pito sandbox arguments");

    try {
        offset = cmd_line::parser(
            argc, argv, options, offset + 1).until_positional(std::cerr).index();
    }
    catch (cmd_line::invalid_arguments& ) {
        offset = plugin::ERROR;
    }
    catch (cmd_line::help_request& ) {
        offset = plugin::HELP;
    }

    return offset;
}

}
