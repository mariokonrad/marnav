#ifndef __AIS__MESSAGE_02__HPP__
#define __AIS__MESSAGE_02__HPP__

#include <marnav/ais/message_01.hpp>

namespace marnav
{
namespace ais
{
MARNAV_AIS_DECLARE_MESSAGE_PARSE_FUNC(message_02)

/// @brief Position Report Class A (assigned schedule)
class message_02 : public message_01
{
	MARNAV_AIS_MESSAGE_FRIENDS(message_02)

public:
	constexpr static const message_id ID
		= message_id::position_report_class_a_assigned_schedule;

	message_02();
	message_02(const message_02 &) = default;
	message_02 & operator=(const message_02 &) = default;

protected:
	message_02(const raw & bits);
};
}
}

#endif
