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
/// @param[in] start_pos The position witin the string to start the parsing of the
///   fields.
/// @return Container with separate fields.
std::vector<std::string> parse_fields(
	const std::string & s, const std::string::size_type start_pos)
{
	if (s.size() < 1)
		return std::vector<std::string>{};

	static constexpr const char * DELIMITERS = ",*";
	std::vector<std::string> result;
	result.reserve(14); // number of fields in RMC, fairly common case
	for (std::string::size_type p = start_pos;; ++p) {
		const auto last = p;
		p = s.find_first_of(DELIMITERS, last);
		result.push_back(s.substr(last, p - last));
		if (p == std::string::npos) // test before increment
			break;
	}
	return result;
}
}
/// @endcond
}
}
