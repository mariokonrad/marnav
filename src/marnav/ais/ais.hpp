#ifndef __AIS__DECODE__HPP__
#define __AIS__DECODE__HPP__

#include "message.hpp"
#include <vector>
#include <stdexcept>

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

std::unique_ptr<message> make_message(const std::vector<std::pair<std::string, int>> & v) throw(
	unknown_message, std::invalid_argument);

std::vector<std::pair<std::string, int>> encode_message(const message & msg) throw(
	std::invalid_argument);
}
}

#endif
