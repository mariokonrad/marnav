#ifndef __AIS__MESSAGE_03__HPP__
#define __AIS__MESSAGE_03__HPP__

#include <marnav/ais/message_01.hpp>

namespace marnav
{
namespace ais
{
MARNAV_AIS_DECLARE_MESSAGE_PARSE_FUNC(message_03)

/// @brief Position Report Class A (response to interrogation)
class message_03 : public message_01
{
	MARNAV_AIS_MESSAGE_FRIENDS(message_03)

public:
	constexpr static const message_id ID
		= message_id::position_report_class_a_response_to_interrogation;

	message_03();
	message_03(const message_03 &) = default;
	message_03 & operator=(const message_03 &) = default;
	message_03(message_03 &&) = default;
	message_03 & operator=(message_03 &&) = default;

protected:
	message_03(const raw & bits);
};
}
}

#endif
