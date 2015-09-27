#ifndef __NMEA__NMEA__HPP__
#define __NMEA__NMEA__HPP__

#include <stdexcept>
#include <marnav/nmea/sentence.hpp>

namespace marnav
{
namespace nmea
{

/// Exception for cases where the checksum is wrong.
///
/// This exception carries the actual as well as the expected
/// checksum and will provide this information in the explanation.
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

/// Exception to be thrown if a NMEA sentence is not known/supported.
class unknown_sentence : public std::logic_error
{
public:
	using logic_error::logic_error;
};

std::unique_ptr<sentence> make_sentence(const std::string & s, bool ignore_checksum = false);

std::vector<std::string> get_supported_sentences_str();
std::vector<sentence_id> get_supported_sentences_id();
std::string to_string(sentence_id id);
sentence_id tag_to_id(const std::string & tag);
}
}

#endif
