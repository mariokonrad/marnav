#include "sentence.hpp"
#include <algorithm>
#include <marnav/nmea/checksum.hpp>

namespace marnav
{
namespace nmea
{
constexpr int sentence::max_length;

sentence::sentence(sentence_id id, const std::string & tag, talker t)
	: id_(id)
	, tag_(tag)
	, talker_(t)
{
}

std::string to_string(const sentence & s)
{
	std::string result;
	result.reserve(sentence::max_length);
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
