#define PITO_SYSTEM_CALL_BASE  sandbox::system_call
#include <pito/plugin/sandbox/system_call.hpp>
#include <pito/jail/c.hpp>
#include <pito/lib/c.hpp>

#include <pito/environment.hpp>
#include <pito/plugin/context.hpp>

#include <chilon/conf/cmd/command_line.hpp>
#include <chilon/filesystem/current_directory.hpp>
#include <chilon/print.hpp>
#include <chilon/realpath.hpp>

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

    struct context {
        paths_t paths_;
        char const *default_;

        context(char const * const default__) : default_(default__) {}
    };

    struct argument_reader : chilon::conf::custom_value {
        void operator()(char const * str) const {
            if (*str == '\0') return;

            chilon::realpath_type realpath;
            if (! chilon::realpath(str, realpath)) {
                std::cerr << "can not access path: " << str << std::endl;
                return;
            }

            if ('/' == *realpath && '\0' == *(realpath + 1))
                context_.default_ = prefix_;
            else {
                std::string r(prefix_);
                r.append(realpath);
                context_.paths_.insert(r);
            }

        }

        argument_reader(char const * const prefix, context& ctxt)
          : prefix_(prefix), context_(ctxt) {};

        char const * prefix_;
        context&     context_;
    };

    using cmd_line::options_description;
    bool verbose = false;
    options_description options;

    context ctxt("P");
    argument_reader blacklist("B", ctxt);
    argument_reader whitelist("W", ctxt);
    argument_reader pretendlist("P", ctxt);

    options.add_options()
        ("b,blacklist", blacklist, "disallow writes to this directory")
        ("w,whitelist", whitelist, "allow writes to this directory")
        ("p,pretend", pretendlist, "pretend to allow writes to this directory")
        ("v,verbose", value(verbose), "increase verbosity")
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
        std::cout << "default: " << ctxt.default_ << std::endl;
        for (auto it = ctxt.paths_.begin(); it != ctxt.paths_.end(); ++it) {
            if (*it->begin() == 'B')
                std::cout << "black list: ";
            else if (*it->begin() == 'W')
                std::cout << "white list: ";
            else if (*it->begin() == 'P')
                std::cout << "pretend list: ";

            std::cout << it->c_str() + 1 << std::endl;
        }
    }

    setenv(PITO_SANDBOX_DEFAULT, ctxt.default_);
    setenv_join(PITO_SANDBOX_PATHS, ctxt.paths_);

    return offset;
}

}
