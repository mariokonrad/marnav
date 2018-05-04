#ifndef MARNAV__AIS__DECODE__HPP
#define MARNAV__AIS__DECODE__HPP

#include <vector>
#include <stdexcept>
#include <marnav/ais/message.hpp>

#include <marnav/marnav_export.h>

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

MARNAV_EXPORT std::unique_ptr<message> make_message(const std::vector<std::pair<std::string, uint32_t>> & v);
MARNAV_EXPORT std::vector<std::pair<std::string, uint32_t>> encode_message(const message & msg);

MARNAV_EXPORT uint8_t decode_armoring(char c);
MARNAV_EXPORT char encode_armoring(uint8_t value);
}
}

#endif
