#include "detail.hpp"
#include <marnav/nmea/sentence.hpp>
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
/// - The optional tag block.
/// - Extracted `fields` from the raw NMEA sentence.
///
std::tuple<talker, std::string, std::string, std::vector<std::string>>
extract_sentence_information(const std::string & s, bool ignore_checksum)
{
	detail::check_raw_sentence(s);

	// handle tag block
	std::string tag_block;
	std::string::size_type search_pos = 1u; // ignore start token
	if (s[0] == sentence::tag_block_token) {
		const auto i = s.find(sentence::tag_block_token, 1);
		if (i != std::string::npos) {
			search_pos += i + 1u; // next after tag block end token
			tag_block = s.substr(1, i - 1);
		}
	}

	// extract all fields, skip start token
	std::vector<std::string> fields = detail::parse_fields(s, search_pos);
	if (fields.size() < 2) // at least address and checksum must be present
		throw std::invalid_argument{"malformed sentence in nmea/make_sentence"};

	if (!ignore_checksum) {
		// check checksum from next character on, ignoring the start token.
		detail::ensure_checksum(s, fields.back(), search_pos);
	}

	// extract address and posibly talker_id and tag.
	// check for vendor extension is necessary because the address field of this extensions
	// to not follow the pattern talker_id/tag
	talker talk{talker_id::none};
	std::string tag;
	std::tie(talk, tag) = detail::parse_address(fields.front());

	return std::make_tuple(talk, tag, tag_block, fields);
}
}
/// @endcond
}
}
