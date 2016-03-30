#ifndef __AIS__DECODE__HPP__
#define __AIS__DECODE__HPP__

#include <vector>
#include <stdexcept>
#include <marnav/ais/message.hpp>

namespace marnav
{
namespace ais
{
/// Exception to be thrown if an AIS message is not known/supported.
class unknown_message : public std::logic_error
{
public:
	using logic_error::logic_error;
};

std::unique_ptr<message> make_message(const std::vector<std::pair<std::string, int>> & v);
std::vector<std::pair<std::string, int>> encode_message(const message & msg);

uint8_t decode_armoring(char c);
char encode_armoring(uint8_t value);
}
}

#endif
