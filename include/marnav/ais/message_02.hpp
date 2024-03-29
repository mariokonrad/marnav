#ifndef MARNAV_AIS_MESSAGE_02_HPP
#define MARNAV_AIS_MESSAGE_02_HPP

#include <marnav/ais/message_01.hpp>

namespace marnav::ais
{
/// @brief Position Report Class A (assigned schedule)
class message_02 : public message_01
{
	friend class detail::factory;

public:
	constexpr static message_id ID = message_id::position_report_class_a_assigned_schedule;

	message_02();
	message_02(const message_02 &) = default;
	message_02 & operator=(const message_02 &) = default;
	message_02(message_02 &&) = default;
	message_02 & operator=(message_02 &&) = default;

protected:
	message_02(const raw & bits);
};
}

#endif
