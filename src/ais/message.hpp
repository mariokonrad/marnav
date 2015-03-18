#ifndef __AIS__MESSAGE__HPP__
#define __AIS__MESSAGE__HPP__

#include <functional>
#include <memory>
#include <utils/bitset.hpp>

namespace ais
{

enum class message_id : uint8_t {
	NONE = 0,
	position_report_class_a = 1,
	position_report_class_a_assigned_schedule = 2,
	position_report_class_a_response_to_interrogation = 3,
	base_station_report = 4,
	static_and_voyage_related_data = 5,
	binary_addressed_message = 6,
	binary_acknowledge = 7,
	binary_broadcast_message = 8,
	standard_sar_aircraft_position_report = 9,
	utc_and_date_inquiry = 10,
	utc_and_date_response = 11,
	addressed_safety_related_message = 12,
	safety_related_acknowledgement_ = 13,
	safety_related_broadcast_message = 14,
	interrogation = 15,
	assignment_mode_command = 16,
	dgnss_binary_broadcast_message = 17,
	standard_class_b_cs_position_report = 18,
	extended_class_b_equipment_position_report = 19,
	data_link_management = 20,
	aid_to_navigation_report = 21,
	channel_management = 22,
	group_assignment_command = 23,
	static_data_report = 24,
	single_slot_binary_message = 25,
	multiple_slot_binary_message_with_communications_state = 26,
	position_report_for_long_range_applications = 27,
};

using raw = utils::bitset<uint8_t>;

class message
{
public:
	using parse_function = std::function<std::unique_ptr<message>(const raw&)>;
};

}

#endif
