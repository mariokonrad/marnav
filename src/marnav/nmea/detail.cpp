#include "detail.hpp"
#include <marnav/nmea/split.hpp>

namespace marnav
{
namespace nmea
{
/// @cond DEV
namespace detail
{
/// Performs checks on the specified raw NMEA sentence and extracts
/// information for further processing.
///
/// This is separated into this function in order to prevent bloat
/// of the template function create_sentence.
///
/// @param[in] s The raw NMEA sentence.
/// @param[in] ignore_checksum Option to ignore the checksum.
/// @return A tuple containing:
/// - The `talker` extracted from the raw NMEA sentence.
/// - The `tag` extracted from the raw NMEA sentence.
/// - Extracted `fields` from the raw NMEA sentence.
///
std::tuple<std::string, std::string, std::vector<std::string>> extract_sentence_information(
	const std::string & s, bool ignore_checksum)
{
	detail::check_raw_sentence(s);

	// extract all fields, skip start token
	std::vector<std::string> fields = detail::parse_fields(s);
	if (fields.size() < 2) // at least address and checksum must be present
		throw std::invalid_argument{"malformed sentence in nmea/make_sentence"};

	if (!ignore_checksum)
		detail::ensure_checksum(s, fields.back());

	// extract address and posibly talker_id and tag.
	// check for vendor extension is necessary because the address field of this extensions
	// to not follow the pattern talker_id/tag
	std::string talker;
	std::string tag;
	std::tie(talker, tag) = detail::parse_address(fields.front());

	return std::make_tuple(talker, tag, fields);
}
}
/// @endcond
}
}
