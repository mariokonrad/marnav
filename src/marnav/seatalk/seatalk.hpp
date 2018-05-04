#ifndef MARNAV__SEATALK__SEATALK__HPP
#define MARNAV__SEATALK__SEATALK__HPP

#include <marnav/seatalk/message.hpp>

#include <marnav/marnav_export.h>

namespace marnav
{
namespace seatalk
{
MARNAV_EXPORT std::unique_ptr<message> make_message(const raw & data);
MARNAV_EXPORT raw encode_message(const message & msg);
MARNAV_EXPORT size_t message_size(message_id id);
}
}

#endif
