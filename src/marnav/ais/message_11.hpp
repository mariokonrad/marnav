#ifndef __AIS__MESSAGE_11__HPP__
#define __AIS__MESSAGE_11__HPP__

#include <marnav/ais/message_04.hpp>
#include <marnav/geo/angle.hpp>

namespace marnav
{
namespace ais
{

/// @brief UTC/Date Response
class message_11 : public message_04
{
public:
	constexpr static const message_id ID = message_id::utc_and_date_response;

	message_11();
	message_11(const message_11 &) = default;
	message_11 & operator=(const message_11 &) = default;

	static std::unique_ptr<message> parse(const raw & bits) throw(
		std::invalid_argument, std::out_of_range);
};
}
}

#endif
