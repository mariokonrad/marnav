#ifndef MARNAV_AIS_MESSAGE_11_HPP
#define MARNAV_AIS_MESSAGE_11_HPP

#include <marnav/ais/message_04.hpp>
#include <marnav/geo/angle.hpp>

namespace marnav::ais
{
/// @brief UTC/Date Response
class message_11 : public message_04
{
	friend class detail::factory;

public:
	constexpr static message_id ID = message_id::utc_and_date_response;

	message_11();
	message_11(const message_11 &) = default;
	message_11 & operator=(const message_11 &) = default;
	message_11(message_11 &&) = default;
	message_11 & operator=(message_11 &&) = default;

protected:
	message_11(const raw & bits);
};
}

#endif
