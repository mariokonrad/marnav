#include "split.hpp"

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

	static const char * DELIMITERS = ",*";
	std::vector<std::string> result;
	std::string::size_type last = 1;
	std::string::size_type p = s.find_first_of(DELIMITERS, last);
	while (last != std::string::npos) {
		result.push_back(s.substr(last, p - last));
		if (p == std::string::npos)
			break;
		last = p + 1;
		p = s.find_first_of(DELIMITERS, last);
	}
	return result;
}
}
/// @endcond
}
}
