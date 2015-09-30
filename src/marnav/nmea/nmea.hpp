#ifndef __NMEA__NMEA__HPP__
#define __NMEA__NMEA__HPP__

#include <marnav/nmea/sentence.hpp>

namespace marnav
{
namespace nmea
{
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
