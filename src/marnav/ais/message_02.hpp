#ifndef MARNAV__AIS__MESSAGE_02__HPP
#define MARNAV__AIS__MESSAGE_02__HPP

#include <marnav/ais/message_01.hpp>

#include <marnav/marnav_export.h>

namespace marnav
{
namespace ais
{
/// @brief Position Report Class A (assigned schedule)
class MARNAV_EXPORT message_02 : public message_01
{
	friend class detail::factory;

public:
	constexpr static const message_id ID
		= message_id::position_report_class_a_assigned_schedule;

	message_02();
	message_02(const message_02 &) = default;
	message_02 & operator=(const message_02 &) = default;
	message_02(message_02 &&) = default;
	message_02 & operator=(message_02 &&) = default;

protected:
	message_02(const raw & bits);
};
}
}

#endif
