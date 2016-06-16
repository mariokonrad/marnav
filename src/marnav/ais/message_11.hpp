#ifndef __AIS__MESSAGE_11__HPP__
#define __AIS__MESSAGE_11__HPP__

#include <marnav/ais/message_04.hpp>
#include <marnav/geo/angle.hpp>

namespace marnav
{
namespace ais
{
MARNAV_AIS_DECLARE_MESSAGE_PARSE_FUNC(message_11)

/// @brief UTC/Date Response
class message_11 : public message_04
{
	MARNAV_AIS_MESSAGE_FRIENDS(message_11)

public:
	constexpr static const message_id ID = message_id::utc_and_date_response;

	message_11();
	message_11(const message_11 &) = default;
	message_11 & operator=(const message_11 &) = default;

protected:
	message_11(const raw & bits);
};
}
}

#endif
