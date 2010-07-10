#define PITO_SYSTEM_CALL_BASE  sandbox::system_call
#include <pito/plugin/sandbox/helper.hpp>
#include <pito/jail/c.hpp>
#include <pito/lib/c.hpp>

#include <pito/environment.hpp>
#include <pito/plugin/init.hpp>

#include <chilon/conf/cmd/command_line.hpp>
#include <chilon/print.hpp>

#include <vector>
#include <cstring>

namespace cmd_line = chilon::conf::cmd;
using chilon::conf::value;

extern "C" {

bool remove_root_entry(std::vector<char const *>& v) {
    for (auto it = v.begin(); it != v.end(); ++it) {
        if (! std::strcmp(*it, "/")) {
            v.erase(it);
            return true;
        }
    }
    return false;
}

int sandbox_init(int offset, int argc, char *argv[]) {
    using cmd_line::options_description;
    bool verbose = false;
    options_description options;

    std::vector<char const *> blacklist;
    std::vector<char const *> whitelist;
    std::vector<char const *> pretendlist;

    options.add_options()
        ("b,blacklist", value(blacklist), "disallow writes to this directory")
        ("w,whitelist", value(whitelist), "allow writes to this directory")
        ("p,pretend", value(pretendlist), "pretend to allow writes to this directory")
        ("v,verbose", value(verbose), "inrease verbosity")
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

    // P for pretend
    char const *defaultlist = "P";

    if (remove_root_entry(whitelist))
        defaultlist = "W";
    else if (remove_root_entry(blacklist))
        defaultlist = "B";
    else
       remove_root_entry(pretendlist);

    setenv("PITO_SANDBOX_DEFAULT", defaultlist);
    setenv_join("PITO_SANDBOX_WHITELIST", whitelist);
    setenv_join("PITO_SANDBOX_BLACKLIST", blacklist);
    setenv_join("PITO_SANDBOX_PRETENDLIST", pretendlist);

    if (verbose) {
        chilon::println("default: ", defaultlist);
        chilon::println("whitelist: ", whitelist);
        chilon::println("blacklist: ", blacklist);
        chilon::println("pretendlist: ", pretendlist);
    }

    return offset;
}

}
