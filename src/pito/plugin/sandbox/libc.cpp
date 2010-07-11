#define PITO_SYSTEM_CALL_BASE  sandbox::system_call
#include <pito/plugin/sandbox/helper.hpp>
#include <pito/jail/c.hpp>
#include <pito/lib/c.hpp>

#include <pito/environment.hpp>
#include <pito/plugin/init.hpp>

#include <chilon/conf/cmd/command_line.hpp>
#include <chilon/filesystem/current_directory.hpp>
#include <chilon/print.hpp>

#include <set>
#include <sstream>
#include <cstring>

namespace cmd_line = chilon::conf::cmd;
using chilon::conf::value;

extern "C" {

int sandbox_init(int offset, int argc, char *argv[]) {
    using chilon::filesystem::current_directory;

    struct entry_size_lessthan {
        bool operator()(std::string const& lhs, std::string const& rhs) {
            return
                lhs.size() > rhs.size() ||
                (lhs.size() == rhs.size() &&
                    std::lexicographical_compare(
                     lhs.begin() + 1, lhs.end(), rhs.begin() + 1, rhs.end()));
        }
    };

    typedef std::set<std::string, entry_size_lessthan> paths_t;

    struct argument_reader : chilon::conf::custom_value {
        void operator()(char const * str) const {
            if (*str == '\0') return;

            std::string r(prefix_);
            if (*str != '/') {
                r.append(cwd_.path());
                r.append("/");
            }
            else if (*(str + 1) == '\0') {
                default_ = prefix_;
                return;
            }

            r.append(str);
            paths_.insert(r);
        }

        argument_reader(
            paths_t& paths, char const * prefix,
            char const *& default__, current_directory const& cwd)
          : paths_(paths), prefix_(prefix), default_(default__), cwd_(cwd) {}

        paths_t&                 paths_;
        char const  *            prefix_;
        char const *&            default_;
        current_directory const& cwd_;
    };

    using cmd_line::options_description;
    bool verbose = false;
    options_description options;
    char const *default_ = "P";

    current_directory cwd;
    paths_t paths;
    argument_reader blacklist(paths, "B", default_, cwd);
    argument_reader whitelist(paths, "W", default_, cwd);
    argument_reader pretendlist(paths, "P", default_, cwd);

    options.add_options()
        ("b,blacklist", blacklist, "disallow writes to this directory")
        ("w,whitelist", whitelist, "allow writes to this directory")
        ("p,pretend", pretendlist, "pretend to allow writes to this directory")
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

    std::stringstream stream;

    if (verbose) {
        std::cout << "default: " << default_ << std::endl;
        for (auto it = paths.begin(); it != paths.end(); ++it) {
            if (*it->begin() == 'B')
                std::cout << "black list: ";
            else if (*it->begin() == 'W')
                std::cout << "white list: ";
            else if (*it->begin() == 'P')
                std::cout << "pretend list: ";

            std::cout << it->c_str() + 1 << std::endl;
        }
    }

    setenv(PITO_SANDBOX_DEFAULT, default_);
    setenv_join(PITO_SANDBOX_PATHS, paths);

    return offset;
}

}
