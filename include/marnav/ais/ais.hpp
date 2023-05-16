#ifndef MARNAV_AIS_DECODE_HPP
#define MARNAV_AIS_DECODE_HPP

#include <marnav/ais/message.hpp>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace marnav::ais
{
/// Exception to be thrown if an AIS message is not known/supported.
class unknown_message : public std::logic_error
{
public:
	using logic_error::logic_error;
};

std::unique_ptr<message> make_message(const std::vector<std::pair<std::string, uint32_t>> & v);
std::vector<std::pair<std::string, uint32_t>> encode_message(const message & msg);

uint8_t decode_armoring(char c);
char encode_armoring(uint8_t value);
}

#endif
