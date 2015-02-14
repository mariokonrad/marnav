#include "sentence.hpp"
#include <algorithm>

namespace nmea
{

sentence::sentence(SentenceID id, const std::string& tag, const std::string& talker)
	: id_(id)
{
	std::copy_n(tag.c_str(), 3, this->tag_);
	std::copy_n(talker.c_str(), 2, this->talker_);
	this->tag_[3] = 0;
	this->talker_[2] = 0;
}

SentenceID sentence::id() const { return id_; }

const char* sentence::tag() const { return tag_; }

const char* sentence::talker() const { return talker_; }

std::string to_string(const sentence& s)
{
	std::ostringstream os;
	os << sentence::START_TOKEN;
	os << s.talker();
	os << s.tag();
	s.append_data(os, ",");
	os << sentence::END_TOKEN;
	std::string result = os.str();

	uint8_t checksum = 0x00;
	for_each(result.begin() + 1, result.end() - 1, [&checksum](char c) { checksum ^= c; });
	char buf[3];
	snprintf(buf, sizeof(buf), "%02X", checksum);

	return result + buf;
}

std::ostream& operator<<(std::ostream& os, const optional<double>& data)
{
	if (data) {
		char buf[32];
		snprintf(buf, sizeof(buf), "%.1f", data.value());
		os << buf;
	}
	return os;
}

}

