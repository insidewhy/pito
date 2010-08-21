#include <chilon/conf/cmd/command_line.hpp>
#include <chilon/print.hpp>
#include <pito/application.hpp>
#include <pito/config.hpp>
#include <pito/plugin/context.hpp>

#include <dlfcn.h>

#include <iostream>

/**
 * @file This is a utility to run a process from the system path with
 *       a specified preload library. e.g.
 *       % pito log ls -R
 *       This is equivalent to executing the following command:
 *          LD_PRELOAD=<pito install location>/libpito_log.so ls -R
 *
 *       % pito -l/usr/local/mylibdir log ls -R
 *          LD_PRELOAD=/usr/local/mylibdir/libpito_log.so ls -R
 */

#define PITO_PROGRAM_VERSION "0.9.9"

namespace pito {

namespace cmd_line = chilon::conf::cmd;
using chilon::conf::value;

namespace color = chilon::color;

bool verbose = false;

inline int main(int argc, char *argv[]) {
    {
        using cmd_line::options_description;
        options_description options;

        std::string preload;
        bool silent = false;
        options.add_options()
            ("v,verbose", verbose, "increase verbosity")
            .help("pito " PITO_PROGRAM_VERSION "\nusage: pito [arguments] "
                  "<wrapper library name> [wrapper arguments] <program> [program arguments]")
            ("s,silent", silent, "remain silent")
            ("l,library-dir", value(preload), "pito library directory")
            ;

        int arg_index;
        try {
            arg_index =
                cmd_line::parser(
                    argc, argv, options).until_positional(std::cerr).index();

            if (2 > argc - arg_index) {
                if (! silent) {
                    if (1 == argc - arg_index)
                        chilon::println(std::cerr, "missing <program> argument");
                    else
                        chilon::println(std::cerr,
                            "missing <wrapper library name> and <program> arguments");
                    std::cerr << options << std::endl;
                }
                return 1;
            }
        }
        catch (cmd_line::invalid_arguments& ) {
            return 1;
        }
        catch (cmd_line::help_request& ) {
            return 1;
        }

        std::string libPath = "libpito_";
        libPath.append(argv[arg_index]);

        search_for_preload_library(libPath, preload, preload);

        if (preload.empty()) {
            if (! silent)
                chilon::println(std::cerr,
                    "library ", libPath,
                    " could not be found at install location or in $"
                    PITO_LD_LIBRARY_PATH);

        }
        else {
            if (verbose)
                chilon::println(std::cerr,
                    "load interceptor library (", preload, ")");

            // the dlopen will trigger the preload initialisation so set
            // the environment for it here
            setenv("LD_PRELOAD", preload.c_str(), 1);

            // TODO: make preload absolute
            auto lib = dlopen(preload.c_str(), RTLD_LAZY);

            if (! lib) {
                if (! silent)
                    chilon::println(
                        std::cerr, "could not dlopen library");
                return 1;
            }

            auto lib_name = std::string(argv[arg_index]) + "_init";
            auto init = dlsym(lib, lib_name.c_str());
            if (init) {
                if (verbose)
                    chilon::println(std::cerr, "init interceptor library (", preload, ")");

                typedef int (*init_ptr)(int, int, char *[]);
                arg_index =
                    reinterpret_cast<init_ptr>(init)(arg_index, argc, argv);
            }
            else ++arg_index;

            if (arg_index < argc) {
                if (arg_index < 0) {
                    if (plugin::HELP != arg_index && ! silent)
                        chilon::println(
                            std::cerr, "invalid plugin arguments");
                }
                else {
                    execvp(argv[arg_index], argv + arg_index);
                    if (! silent)
                        chilon::println(std::cerr,
                            "could not exec program: ", argv[arg_index]);
                }
            }
        }
        return 1;
    }
}

}

int main(int argc, char *argv[]) {
    return pito::main(argc, argv);
}
