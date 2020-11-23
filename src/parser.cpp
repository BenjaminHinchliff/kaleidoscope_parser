#include "config.hpp"
#include "parser_def.hpp"

namespace kaleidoscope {
namespace parser {
BOOST_SPIRIT_INSTANTIATE(expr_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(prototype_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(top_function_type, iterator_type, context_type);
}
} // namespace menthol