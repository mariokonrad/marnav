#ifndef MARNAV__AIS__MESSAGE__HPP
#define MARNAV__AIS__MESSAGE__HPP

#include <memory>
#include <string>
#include <marnav/ais/binary_data.hpp>

namespace marnav
{
namespace ais
{

/// All known AIS message IDs.
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
	safety_related_acknowledgement = 13,
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

enum class navigation_status : uint8_t {
	under_way_using_engine = 0,
	at_anchor = 1,
	not_under_command = 2,
	restricted_maneuverability = 3,
	constrained_by_her_draught = 4,
	moored = 5,
	aground = 6,
	engaged_in_Fishing = 7,
	under_way_sailing = 8,
	reserved_09 = 9,
	reserved_10 = 10,
	reserved_11 = 11,
	reserved_12 = 12,
	reserved_13 = 13,
	ais_sart_is_active = 14,
	not_defined = 15, // default
};

enum class ship_type : uint8_t {
	not_available = 0,
	// 1..19 reserved for future use
	wing_in_ground = 20,
	wing_in_ground_hazardous_cat_a = 21,
	wing_in_ground_hazardous_cat_b = 22,
	wing_in_ground_hazardous_cat_c = 23,
	wing_in_ground_hazardous_cat_d = 24,
	// 25..29 WIG reserved for future use
	fishing = 30,
	towing = 31,
	towing_large = 32, // exceeds 200m length or 25m breadth
	dredging_or_underwater_ops = 33,
	diving_ops = 34,
	military_ops = 35,
	sailing = 36,
	pleasure_craft = 37,
	// 38..39 reserved
	high_speed_craft = 40,
	high_speed_craft_hazardous_cat_a = 41,
	high_speed_craft_hazardous_cat_b = 42,
	high_speed_craft_hazardous_cat_c = 43,
	high_speed_craft_hazardous_cat_d = 44,
	// 45..48 HSC reserved for future use
	high_speed_craft_no_info = 49,
	pilot_vessel = 50,
	search_and_rescue_vessel = 51,
	tug = 52,
	port_tender = 53,
	anti_pollution_equipment = 54,
	law_enforcement = 55,
	// 56..57 spare, local vessel
	medical_transport = 58,
	noncombatant = 59,
	passenger = 60,
	passenger_hazardous_cat_a = 61,
	passenger_hazardous_cat_b = 62,
	passenger_hazardous_cat_c = 63,
	passenger_hazardous_cat_d = 64,
	// 65..68 Passenger reserved for future use
	passenger_no_info = 69,
	cargo = 70,
	cargo_hazardous_cat_a = 71,
	cargo_hazardous_cat_b = 72,
	cargo_hazardous_cat_c = 73,
	cargo_hazardous_cat_d = 74,
	// 75..78 Cargo reserved for future use
	cargo_no_info = 79,
	tanker = 80,
	tanker_hazardous_cat_a = 81,
	tanker_hazardous_cat_b = 82,
	tanker_hazardous_cat_c = 83,
	tanker_hazardous_cat_d = 84,
	// 85..88 Tanker reserved for future use
	tanker_no_info = 89,
	other = 90,
	other_hazardous_cat_a = 91,
	other_hazardous_cat_b = 92,
	other_hazardous_cat_c = 93,
	other_hazardous_cat_d = 94,
	// 95..98 Other type reserved for future use
	other_no_info = 99,
};

/// Electronic Position Fixing Device
enum class epfd_fix_type : uint8_t {
	undefined = 0,
	gps = 1,
	glonass = 2,
	combined_gps_glonass = 3,
	loran_c = 4,
	chayka = 5,
	integrated_navigation_system = 6,
	surveyed = 7,
	galileo = 8,
};

/// Enumeration of data terminal status.
enum class data_terminal : uint8_t { ready = 0, not_ready = 1 };

enum class virtual_aid : uint32_t { real_aid = 0, virtual_aid = 1 };

enum class off_position_indicator : uint32_t { on_position = 0, off_position = 1 };

/// Enumeration of all aid types
enum class aid_type_id : uint32_t {
	/// 0 : Default, Type of Aid to Navigation not specified
	unspecified = 0,

	/// 1 : Reference point
	reference_point = 1,

	/// 2 : RACON (radar transponder marking a navigation hazard)
	racon = 2,

	/// 3 : Fixed structure off shore, such as oil platforms, wind farms, rigs. (Note: This
	/// code should identify an obstruction that is fitted with an Aid-to-Navigation AIS
	/// station.)
	fixed_structure = 3,

	/// 4 : Spare, Reserved for future use.
	reserved = 4,

	/// 5 : Light, without sectors
	light_no_sectors = 5,

	/// 6 : Light, with sectors
	light_sectors = 6,

	/// 7 : Leading Light Front
	leading_light_fromt = 7,

	/// 8 : Leading Light Rear
	leading_light_rear = 8,

	/// 9 : Beacon, Cardinal N
	beacon_cardinal_n = 9,

	/// 10: Beacon, Cardinal E
	beacon_cardinal_e = 10,

	/// 11: Beacon, Cardinal S
	beacon_cardinal_s = 11,

	/// 12: Beacon, Cardinal W
	beacon_cardinal_w = 12,

	/// 13: Beacon, Port hand
	beacon_port_hand = 13,

	/// 14: Beacon, Starboard hand
	beacon_starboard_hand = 14,

	/// 15: Beacon, Preferred Channel port hand
	beacon_preferred_channel_port_hand = 15,

	///< 16: Beacon, Preferred Channel starboard hand
	beacon_preferred_channel_starboard_hand = 16,

	/// 17: Beacon, Isolated danger
	beacon_isolated_danger = 17,

	/// 18: Beacon, Safe water
	beacon_safe_water = 18,

	/// 19: Beacon, Special mark
	beacon_sepcial_mark = 19,

	/// 20: Cardinal Mark N
	cardinal_n = 20,

	/// 21: Cardinal Mark E
	cardinal_e = 21,

	/// 22: Cardinal Mark S
	cardinal_s = 22,

	/// 23: Cardinal Mark W
	cardinal_w = 23,

	/// 24: Port hand Mark
	mark_port_hand = 24,

	/// 25: Starboard hand Mark
	mark_starboard_hand = 25,

	/// 26: Preferred Channel Port hand
	preferred_channel_port_hand = 26,

	/// 27: Preferred Channel Starboard hand
	preferred_channel_starboard_hand = 27,

	/// 28: Isolated danger
	isolated_danger = 28,

	/// 29: Safe Water
	safe_water = 29,

	/// 30: Special Mark
	special_mark = 30,

	/// 31: Light Vessel / LANBY / Rigs
	light_vessel = 31,

};

enum class maneuver_indicator_id : uint32_t { not_available = 0, normal = 1, special = 2 };

// AIS data is coded in a binary form. This implies a need for special
// value that mark the invalidity of a certain value.
/// @{

/// Value for a longitude that is not specified.
constexpr static const uint32_t longitude_not_available = 0x6791AC0;

/// Value for a latitude that is not specified.
constexpr static const uint32_t latitude_not_available = 0x3412140;

/// Value for a longitude that is not specified, short version.
constexpr static const uint32_t longitude_not_available_short = 0x1a838;

/// Value for a latitude that is not specified, short version.
constexpr static const uint32_t latitude_not_available_short = 0xd548;

/// Value for a speed over ground that is not specified.
constexpr static const uint32_t sog_not_available = 1023;

/// Value for a course over ground that is not specified.
constexpr static const uint32_t cog_not_available = 3600;

/// Value for a heading that is not specified.
constexpr static const uint32_t hdg_not_available = 511;

/// Value to indicate the absense of a timestamp.
constexpr static const uint8_t timestamp_not_available = 60;

/// Value for a year that is not specified.
constexpr static const uint32_t year_not_available = 0;

/// Value for a month that is not specified.
constexpr static const uint32_t month_not_available = 0;

/// Value for a day that is not specified.
constexpr static const uint32_t day_not_available = 0;

/// Value for a hour that is not specified.
constexpr static const uint32_t hour_not_available = 24;

/// Value for a minute that is not specified.
constexpr static const uint32_t minute_not_available = 60;

/// Value for a second that is not specified.
constexpr static const uint32_t second_not_available = 60;

/// @}

/// @brief Base class for all AIS messages.
class message : public binary_data
{
	friend std::vector<std::pair<std::string, uint32_t>> encode_message(const message & msg);

public:
	virtual ~message() = default;
	message() = delete;
	message(const message &) = default;
	message & operator=(const message &) = default;
	message(message &&) = default;
	message & operator=(message &&) = default;

	message_id type() const { return message_type; }

protected:
	explicit message(message_id type)
		: message_type(type)
	{
	}

	virtual raw get_data() const = 0;

private:
	message_id message_type;
};

/// @cond DEV
namespace detail
{
/// Checks if the specified cast is valid, throws `bad_cast` if not.
/// If the pointer is `nullptr`, false returns.
template <class T> bool check_cast(const message * s)
{
	if (!s)
		return false;
	if (s->type() != T::ID)
		throw std::bad_cast{};
	return true;
}

class factory
{
public:
	template <class T,
		typename std::enable_if<std::is_base_of<message, T>::value, int>::type = 0>
	static std::unique_ptr<message> parse(const raw & bits)
	{
		return std::unique_ptr<T>(new T{bits});
	}
};
}
/// @endcond

/// Helper function to parse a specific message, to be used in unit tests.
///
/// @todo This breaks encapsulation.
template <class T, typename std::enable_if<std::is_base_of<message, T>::value, int>::type = 0>
std::unique_ptr<message> message_parse(const raw & bits)
{
	return detail::factory::parse<T>(bits);
}

/// @{

/// Casts the specified message to the message given by the template parameter.
/// The object converted only if it is valid and of the correct type. It is not
/// possible to cast a message into a completley different one.
///
/// @param[in] s The message object to convert.
/// @retval nullptr The specified message is invalid.
/// @return The converted message.
/// @exception std::bad_cast The specified message has the wrong ID.
template <class T> T * message_cast(message * s)
{
	return detail::check_cast<T>(s) ? static_cast<T *>(s) : nullptr;
}

/// Raw pointer const variant.
///
/// @see message_cast(message * s)
template <class T> const T * message_cast(const message * s)
{
	return detail::check_cast<T>(s) ? static_cast<const T *>(s) : nullptr;
}

/// `std::unique_ptr` variant. If the cast is possible, the original `unique_ptr<message>`
/// will be invalidated and a new `unique_ptr<T>` will be returned. This has implications
/// within the calling code.
///
/// @param[in,out] s The message to cast.
/// @return The casted message. If the specified sentence was `nullptr`, the function
///   also returns `nullptr`.
/// @exception bad_cast This exception is thrown if the specified message is
///   not castable into the destination type `T`.
///
template <class T> std::unique_ptr<T> message_cast(std::unique_ptr<message> & s)
{
	return detail::check_cast<T>(s.get()) ? std::unique_ptr<T>(static_cast<T *>(s.release()))
										  : nullptr;
}

/// `unique_ptr` ref ref variant.
///
/// @see message_cast(std::unique_ptr<message> & s)
template <class T> std::unique_ptr<T> message_cast(std::unique_ptr<message> && s)
{
	return detail::check_cast<T>(s.get()) ? std::unique_ptr<T>(static_cast<T *>(s.release()))
										  : nullptr;
}

/// @}
}
}

#endif
