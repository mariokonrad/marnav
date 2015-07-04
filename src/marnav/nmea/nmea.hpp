#ifndef __NMEA__NMEA__HPP__
#define __NMEA__NMEA__HPP__

#include <stdexcept>
#include "sentence.hpp"

namespace marnav
{
namespace nmea
{

class checksum_error : public std::exception
{
public:
	checksum_error(uint8_t expected, uint8_t actual);

	virtual const char * what() const noexcept override { return text.c_str(); }

public:
	const uint8_t expected;
	const uint8_t actual;
	std::string text;
};

std::unique_ptr<sentence> make_sentence(const std::string & s) throw(
	std::invalid_argument, checksum_error);

std::vector<std::string> get_supported_sentences_str();
std::vector<sentence_id> get_supported_sentences_id();
const char * id_to_tag(sentence_id id) throw(std::invalid_argument);
sentence_id tag_to_id(const std::string & tag) throw(std::invalid_argument);
}
}

#endif
