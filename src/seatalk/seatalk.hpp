#ifndef __SEATALK__SEATALK__HPP__
#define __SEATALK__SEATALK__HPP__

#include "message.hpp"

namespace seatalk
{
std::unique_ptr<message> make_message(const raw& data) throw(std::invalid_argument);
raw encode_message(const message& msg) throw(std::invalid_argument);
}

#endif
