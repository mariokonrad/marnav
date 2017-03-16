#include "name.hpp"

namespace marnav
{
namespace ais
{
std::string to_name(message_id t)
{
	switch (t) {
		case message_id::NONE:
			return "<none>";
		case message_id::position_report_class_a:
			return "Position Report Class A";
		case message_id::position_report_class_a_assigned_schedule:
			return "Position Report Class A - Assigned Schedule";
		case message_id::position_report_class_a_response_to_interrogation:
			return "Position Report Class A - Response to Interrogation";
		case message_id::base_station_report:
			return "Base Station Report";
		case message_id::static_and_voyage_related_data:
			return "Static and Voyage related Data";
		case message_id::binary_addressed_message:
			return "Binary Addressed Message";
		case message_id::binary_acknowledge:
			return "Binary Acknowledge";
		case message_id::binary_broadcast_message:
			return "Binary Broadcast Message";
		case message_id::standard_sar_aircraft_position_report:
			return "Standard SAR Aircraft Position Report";
		case message_id::utc_and_date_inquiry:
			return "UTC and Date Inquiry";
		case message_id::utc_and_date_response:
			return "UTC and Date Response";
		case message_id::addressed_safety_related_message:
			return "Addresed Safety related Message";
		case message_id::safety_related_acknowledgement:
			return "Safety related Acknowledgement";
		case message_id::safety_related_broadcast_message:
			return "Safety related Broadcast Message";
		case message_id::interrogation:
			return "Interrogation";
		case message_id::assignment_mode_command:
			return "Assignment Mode Command";
		case message_id::dgnss_binary_broadcast_message:
			return "DGNSS Binary Broadcast Message";
		case message_id::standard_class_b_cs_position_report:
			return "Standard Class B CS Position Report";
		case message_id::extended_class_b_equipment_position_report:
			return "Extended Class B Equipment Position Report";
		case message_id::data_link_management:
			return "Data Link Management";
		case message_id::aid_to_navigation_report:
			return "Aid to Navigation Report";
		case message_id::channel_management:
			return "Channel Management";
		case message_id::group_assignment_command:
			return "Group Assignment Command";
		case message_id::static_data_report:
			return "Static Data Report";
		case message_id::single_slot_binary_message:
			return "Single Slot Binary Message";
		case message_id::multiple_slot_binary_message_with_communications_state:
			return "Multiple slot Binary Message with Communication State";
		case message_id::position_report_for_long_range_applications:
			return "Position Report for long range Applications";
	}
	return "-";
}

/// Returns a printable name (in english) for the specified type.
///
/// @param[in] t Ship type to get the name for.
/// @return The printable name for the ship type.
std::string to_name(ship_type t)
{
	switch (t) {
		case ship_type::not_available:
			return "Not Available";
		case ship_type::wing_in_ground:
			return "Wing in ground";
		case ship_type::wing_in_ground_hazardous_cat_a:
			return "Wing in ground hazardous Cat A";
		case ship_type::wing_in_ground_hazardous_cat_b:
			return "Wing in ground hazardous Cat B";
		case ship_type::wing_in_ground_hazardous_cat_c:
			return "Wing in ground hazardous Cat C";
		case ship_type::wing_in_ground_hazardous_cat_d:
			return "Wing in ground hazardous Cat D";
		case ship_type::fishing:
			return "Fishing";
		case ship_type::towing:
			return "Towing";
		case ship_type::towing_large:
			return "Towing large";
		case ship_type::dredging_or_underwater_ops:
			return "Dredging or underwater ops";
		case ship_type::diving_ops:
			return "Diving ops";
		case ship_type::military_ops:
			return "Military ops";
		case ship_type::sailing:
			return "Sailing";
		case ship_type::pleasure_craft:
			return "Pleasure Craft";
		case ship_type::high_speed_craft:
			return "High speed craft";
		case ship_type::high_speed_craft_hazardous_cat_a:
			return "High speed craft hazardous Cat A";
		case ship_type::high_speed_craft_hazardous_cat_b:
			return "High speed craft hazardous Cat B";
		case ship_type::high_speed_craft_hazardous_cat_c:
			return "High speed craft hazardous Cat C";
		case ship_type::high_speed_craft_hazardous_cat_d:
			return "High speed craft hazardous Cat D";
		case ship_type::high_speed_craft_no_info:
			return "High speed craft no_info";
		case ship_type::pilot_vessel:
			return "Pilot Vessel";
		case ship_type::search_and_rescue_vessel:
			return "Search and Rescue Vessel";
		case ship_type::tug:
			return "Tug";
		case ship_type::port_tender:
			return "Port Tender";
		case ship_type::anti_pollution_equipment:
			return "Anti Pollution Equipment";
		case ship_type::law_enforcement:
			return "Law Enforcement";
		case ship_type::medical_transport:
			return "Medical Transport";
		case ship_type::noncombatant:
			return "Noncombatant";
		case ship_type::passenger:
			return "Passenger";
		case ship_type::passenger_hazardous_cat_a:
			return "Passenger hazardous Cat A";
		case ship_type::passenger_hazardous_cat_b:
			return "Passenger hazardous Cat B";
		case ship_type::passenger_hazardous_cat_c:
			return "Passenger hazardous Cat C";
		case ship_type::passenger_hazardous_cat_d:
			return "Passenger hazardous Cat D";
		case ship_type::passenger_no_info:
			return "Passenger no info";
		case ship_type::cargo:
			return "Cargo";
		case ship_type::cargo_hazardous_cat_a:
			return "Cargo hazardous Cat A";
		case ship_type::cargo_hazardous_cat_b:
			return "Cargo hazardous Cat B";
		case ship_type::cargo_hazardous_cat_c:
			return "Cargo hazardous Cat C";
		case ship_type::cargo_hazardous_cat_d:
			return "Cargo hazardous Cat D";
		case ship_type::cargo_no_info:
			return "Cargo no info";
		case ship_type::tanker:
			return "Tanker";
		case ship_type::tanker_hazardous_cat_a:
			return "Tanker hazardous Cat A";
		case ship_type::tanker_hazardous_cat_b:
			return "Tanker hazardous Cat B";
		case ship_type::tanker_hazardous_cat_c:
			return "Tanker hazardous Cat C";
		case ship_type::tanker_hazardous_cat_d:
			return "Tanker hazardous Cat D";
		case ship_type::tanker_no_info:
			return "Tanker no info";
		case ship_type::other:
			return "Other";
		case ship_type::other_hazardous_cat_a:
			return "Other hazardous Cat A";
		case ship_type::other_hazardous_cat_b:
			return "Other hazardous Cat B";
		case ship_type::other_hazardous_cat_c:
			return "Other hazardous Cat C";
		case ship_type::other_hazardous_cat_d:
			return "Other hazardous Cat D";
		case ship_type::other_no_info:
			return "Other no info";
	}
	return "-";
}

std::string to_name(epfd_fix_type t)
{
	switch (t) {
		case epfd_fix_type::undefined:
			return "undefined";
		case epfd_fix_type::gps:
			return "GPS";
		case epfd_fix_type::glonass:
			return "GLONASS";
		case epfd_fix_type::combined_gps_glonass:
			return "Combined GPS GLONASS";
		case epfd_fix_type::loran_c:
			return "Loran C";
		case epfd_fix_type::chayka:
			return "Chayka";
		case epfd_fix_type::integrated_navigation_system:
			return "Integrated Navigation System";
		case epfd_fix_type::surveyed:
			return "surveyed";
		case epfd_fix_type::galileo:
			return "Galileo";
	}
	return "-";
}

std::string to_name(navigation_status t)
{
	switch (t) {
		case navigation_status::under_way_using_engine:
			return "Under way using Engine";
		case navigation_status::at_anchor:
			return "At Anchor";
		case navigation_status::not_under_command:
			return "Not under Command";
		case navigation_status::restricted_maneuverability:
			return "Restricted Maneuverability";
		case navigation_status::constrained_by_her_draught:
			return "Constrained by her Draught";
		case navigation_status::moored:
			return "Moored";
		case navigation_status::aground:
			return "Aground";
		case navigation_status::engaged_in_Fishing:
			return "Engaged in Fishing";
		case navigation_status::under_way_sailing:
			return "Under way Sailing";
		case navigation_status::reserved_09:
			break;
		case navigation_status::reserved_10:
			break;
		case navigation_status::reserved_11:
			break;
		case navigation_status::reserved_12:
			break;
		case navigation_status::reserved_13:
			break;
		case navigation_status::ais_sart_is_active:
			return "AIS SART is Active";
		case navigation_status::not_defined:
			return "Not Defined";
	}
	return "-";
}

std::string to_name(virtual_aid t)
{
	switch (t) {
		case virtual_aid::real_aid:
			return "Real Aid";
		case virtual_aid::virtual_aid:
			return "Virtual Aid";
	}
	return "-";
}

std::string to_name(off_position_indicator t)
{
	switch (t) {
		case off_position_indicator::on_position:
			return "On Position";
		case off_position_indicator::off_position:
			return "Off Position";
	}
	return "-";
}

std::string to_name(aid_type_id t)
{
	switch (t) {
		case aid_type_id::unspecified:
			return "unspecified";
		case aid_type_id::reference_point:
			return "Reference point";
		case aid_type_id::racon:
			return "RACON (radar transponder marking a navigation hazard)";
		case aid_type_id::fixed_structure:
			return "Fixed structure";
		case aid_type_id::reserved:
			return "Spare, Reserved for future use";
		case aid_type_id::light_no_sectors:
			return "Light, without sectors";
		case aid_type_id::light_sectors:
			return "Light, with sectors";
		case aid_type_id::leading_light_fromt:
			return "Leading Light Front";
		case aid_type_id::leading_light_rear:
			return "Leading Light Rear";
		case aid_type_id::beacon_cardinal_n:
			return "Beacon, Cardinal N";
		case aid_type_id::beacon_cardinal_e:
			return "Beacon, Cardinal E";
		case aid_type_id::beacon_cardinal_s:
			return "Beacon, Cardinal S";
		case aid_type_id::beacon_cardinal_w:
			return "Beacon, Cardinal W";
		case aid_type_id::beacon_port_hand:
			return "Beacon, Port hand";
		case aid_type_id::beacon_starboard_hand:
			return "Beacon, Starboard hand";
		case aid_type_id::beacon_preferred_channel_port_hand:
			return "Beacon, Preferred Channel port hand";
		case aid_type_id::beacon_preferred_channel_starboard_hand:
			return "Beacon, Preferred Channel starboard hand";
		case aid_type_id::beacon_isolated_danger:
			return "Beacon, Isolated danger";
		case aid_type_id::beacon_safe_water:
			return "Beacon, Safe water";
		case aid_type_id::beacon_sepcial_mark:
			return "Beacon, Special mark";
		case aid_type_id::cardinal_n:
			return "Cardinal Mark N";
		case aid_type_id::cardinal_e:
			return "Cardinal Mark E";
		case aid_type_id::cardinal_s:
			return "Cardinal Mark S";
		case aid_type_id::cardinal_w:
			return "Cardinal Mark W";
		case aid_type_id::mark_port_hand:
			return "Port hand Mark";
		case aid_type_id::mark_starboard_hand:
			return "Starboard hand Mark";
		case aid_type_id::preferred_channel_port_hand:
			return "Preferred Channel Port hand";
		case aid_type_id::preferred_channel_starboard_hand:
			return "Preferred Channel Starboard hand";
		case aid_type_id::isolated_danger:
			return "Isolated danger";
		case aid_type_id::safe_water:
			return "Safe Water";
		case aid_type_id::special_mark:
			return "Special Mark";
		case aid_type_id::light_vessel:
			return "Light Vessel / LANBY / Rigs";
	}
	return "-";
}

std::string to_name(maneuver_indicator_id t)
{
	switch (t) {
		case maneuver_indicator_id::not_available:
			return "Not Available";
		case maneuver_indicator_id::normal:
			return "Not Special";
		case maneuver_indicator_id::special:
			return "Special";
	}
	return "-";
}

std::string to_name(data_terminal t)
{
	switch (t) {
		case data_terminal::ready:
			return "ready";
		case data_terminal::not_ready:
			return "not ready";
	}
	return "-";
}
}
}
