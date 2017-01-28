#include "sentence.hpp"
#include <algorithm>
#include <marnav/nmea/checksum.hpp>

namespace marnav
{
namespace nmea
{
constexpr int sentence::max_length;

/// This protected constructor is used to construct an object
/// by through its subclasses.
sentence::sentence(sentence_id id, const std::string & tag, talker t)
	: id_(id)
	, tag_(tag)
	, talker_(t)
{
}

/// Creates a raw string from the specified sentence.
///
/// If the sentence contains a tag block, it will be inserted in front
/// of the raw NMEA string.
std::string to_string(const sentence & s)
{
	std::string result;
	const std::string block = s.get_tag_block();
	if (block.size() != 0u) {
		result.reserve(sentence::max_length + block.size() + 2u);
		result += sentence::tag_block_token;
		result += block;
		result += sentence::tag_block_token;
	} else {
		result.reserve(sentence::max_length);
	}
	result += s.get_start_token();
	result += s.get_talker().str();
	result += s.tag();
	for (auto const & data : s.get_data()) {
		result += ",";
		result += data;
	}
	result += s.get_end_token();
	result += checksum_to_string(
		checksum(std::next(std::begin(result)), std::prev(std::end(result))));
	return result;
}
}
}
