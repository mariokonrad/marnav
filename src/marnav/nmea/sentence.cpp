#include "sentence.hpp"
#include <algorithm>
#include <marnav/nmea/checksum.hpp>

namespace marnav
{
namespace nmea
{

sentence::sentence(sentence_id id, const std::string & tag, const std::string & talker)
	: id_(id)
	, tag_(tag)
	, talker_(talker)
{
}

/// Overwrites the default talker for a sentence.
void sentence::set_talker(const std::string & talker)
{
	if (talker.size() != 2)
		return;
	talker_ = talker;
}

sentence_id sentence::id() const { return id_; }

std::string sentence::tag() const { return tag_; }

std::string sentence::talker() const { return talker_; }

std::string to_string(const sentence & s)
{
	std::string result;
	result.reserve(sentence::max_length);
	result += s.get_start_token();
	result += s.talker();
	result += s.tag();
	for (auto const & data : s.get_data()) {
		result += ",";
		result += data;
	}
	result += s.get_end_token();

	char buf[8];
	snprintf(buf, sizeof(buf), "%02X", checksum(result.begin() + 1, result.end() - 1));

	return result + buf;
}
}
}
