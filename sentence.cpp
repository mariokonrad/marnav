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

}

