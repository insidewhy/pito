#include <pito/plugin/sandbox/helper.hpp>
#include <pito/jail/environment.hpp>

#include <chilon/print.hpp>
#include <chilon/iterator_range.hpp>
#include <chilon/parser/joined.hpp>
#include <chilon/parser/char.hpp>
#include <chilon/parser/many.hpp>
#include <chilon/parser/not_char.hpp>

namespace pito { namespace sandbox {

namespace parser = chilon::parser;

context& ctxt = chilon::singleton<context>::instance();

context::context() : mode(WRITE_MODE_PRETEND) {
    auto& jail_ctxt = chilon::singleton<jail::context>::instance();

    for (auto it = jail_ctxt.environment_.begin();
         it != jail_ctxt.environment_.end(); ++it)
    {
        if (it->first == PITO_SANDBOX_DEFAULT) {
            switch (*(it->second.begin())) {
                case 'W':
                    mode = WRITE_MODE_WHITELIST;
                    break;
                case 'B':
                    mode = WRITE_MODE_BLACKLIST;
                    break;
            }
        }
        else if (it->first == PITO_SANDBOX_PATHS) {
            using parser::parse;
            using parser::joined_plus_lexeme;
            using parser::char_;
            using parser::not_char;
            using parser::many_plus;

            range r(chilon::to_range(it->second.c_str()));
            parse< joined_plus_lexeme<
                char_<'\n'>,
                many_plus<not_char<'\n'> > > >::skip(r, paths);
        }
    }
}

} }
