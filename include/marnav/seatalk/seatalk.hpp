#ifndef MARNAV_SEATALK_SEATALK_HPP
#define MARNAV_SEATALK_SEATALK_HPP

#include <marnav/seatalk/message.hpp>

namespace marnav
{
namespace seatalk
{
std::unique_ptr<message> make_message(const raw & data);
raw encode_message(const message & msg);
size_t message_size(message_id id);
}
}

#endif
