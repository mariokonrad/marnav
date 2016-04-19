#include "split.hpp"
#include <regex>

namespace marnav
{
namespace nmea
{
/// @cond DEV
namespace detail
{
/// Parses the fields from the specified string. Uses ',' and '*' as delimiter.
///
/// The first character is ignored, because it is expected for the specified string
/// to be at the beginning of a NMEA sentence. The start token has to be ignored.
///
/// @param[in] s The string to parse.
/// @return Container with separate fields.
std::vector<std::string> parse_fields(const std::string & s)
{
	if (s.size() < 1)
		return std::vector<std::string>{};
	std::regex field_regex{"(,|\\*)"};
	auto fields_begin = std::sregex_token_iterator{begin(s) + 1, end(s), field_regex, -1};
	auto fields_end = std::sregex_token_iterator();
	return {fields_begin, fields_end};
}
}
/// @endcond
}
}
