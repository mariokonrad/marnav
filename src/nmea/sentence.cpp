#include "sentence.hpp"
#include <algorithm>

namespace nmea
{

sentence::sentence(sentence_id id, const std::string& tag, const std::string& talker)
	: id_(id)
{
	std::copy_n(tag.c_str(), 3, this->tag_);
	this->tag_[3] = 0;

	std::fill_n(talker_, sizeof(talker_), 0);
	set_talker(talker);
}

/// Overwrites the default talker for a sentence.
void sentence::set_talker(const std::string& talker)
{
	if (talker.size() != 2)
		return;

	std::copy_n(talker.c_str(), 2, this->talker_);
	this->talker_[2] = 0;
}

sentence_id sentence::id() const { return id_; }

const char* sentence::tag() const { return tag_; }

const char* sentence::talker() const { return talker_; }

std::string to_string(const sentence& s)
{
	std::string result;
	result += sentence::START_TOKEN;
	result += s.talker();
	result += s.tag();
	for (auto const& data : s.get_data()) {
		result += ",";
		result += data;
	}
	result += sentence::END_TOKEN;

	uint8_t checksum = 0x00;
	for_each(result.begin() + 1, result.end() - 1, [&checksum](char c) { checksum ^= c; });
	char buf[8];
	snprintf(buf, sizeof(buf), "%02X", checksum);

	return result + buf;
}

}

