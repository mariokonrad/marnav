#ifndef MARNAV_NMEA_NMEA_HPP
#define MARNAV_NMEA_NMEA_HPP

#include <marnav/nmea/sentence_id.hpp>
#include <marnav/nmea/checksum_enum.hpp>
#include <memory>
#include <string>
#include <stdexcept>
#include <vector>

namespace marnav::nmea
{
/// @brief Exception to be thrown if a NMEA sentence is not known/supported.
class unknown_sentence : public std::logic_error
{
public:
	using logic_error::logic_error;
};

class sentence; // forward declaration

std::unique_ptr<sentence> make_sentence(
	const std::string & s, checksum_handling chksum = checksum_handling::check);

sentence_id extract_id(const std::string & s);

std::vector<std::string> get_supported_sentences_str();
std::vector<sentence_id> get_supported_sentences_id();
std::string to_string(sentence_id id);
sentence_id tag_to_id(const std::string & tag);
}

#endif
