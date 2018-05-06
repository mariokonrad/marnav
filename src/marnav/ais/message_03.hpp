#ifndef MARNAV__AIS__MESSAGE_03__HPP
#define MARNAV__AIS__MESSAGE_03__HPP

#include <marnav/ais/message_01.hpp>

#include <marnav/marnav_export.h>

namespace marnav
{
namespace ais
{
/// @brief Position Report Class A (response to interrogation)
class MARNAV_EXPORT message_03 : public message_01
{
	friend class detail::factory;

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
