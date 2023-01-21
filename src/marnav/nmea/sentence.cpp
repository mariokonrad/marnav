#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/checksum.hpp>
#include <algorithm>

namespace marnav::nmea
{
constexpr int sentence::max_length;
constexpr char sentence::start_token;
constexpr char sentence::start_token_ais;
constexpr char sentence::end_token;
constexpr char sentence::field_delimiter;
constexpr char sentence::tag_block_token;

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
std::string to_string(const sentence & s, const version & v)
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
	result += to_string(s.get_talker());
	result += s.tag();
	s.append_data_to(result, v);
	result += s.get_end_token();
	result += checksum_to_string(
		checksum(std::next(std::begin(result)), std::prev(std::end(result))));
	return result;
}

void sentence::append(std::string & s, const std::string & t)
{
	s += field_delimiter;
	s += t;
}

void sentence::append(std::string & s, const char t)
{
	s += field_delimiter;
	s += t;
}
}
