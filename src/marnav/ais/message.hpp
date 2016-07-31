#ifndef __AIS__MESSAGE__HPP__
#define __AIS__MESSAGE__HPP__

#include <memory>
#include <marnav/utils/bitset.hpp>

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

enum class navigation_status : uint8_t {
	under_way_using_engine = 0,
	at_anchor = 1,
	not_under_command = 2,
	restricted_manoeuverability = 3,
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

/// Value to indicate the absense of a maneuver indicator.
constexpr static const uint8_t maneuver_indictor_not_available = 0;

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

/// Type for raw AIS data.
using raw = utils::bitset<uint8_t>;

/// @{

char decode_sixbit_ascii(uint8_t value);
uint8_t encode_sixbit_ascii(char c);

/// @}

/// @brief Base class for all AIS messages.
class message
{
	friend std::vector<std::pair<std::string, uint32_t>> encode_message(const message & msg);

public:
	message() = delete;
	virtual ~message() {}

	message_id type() const { return message_type; }

protected:
	/// Represents data to be read from / written to a bitset.
	/// The offset and number of bits (or sixbits) is encoded in the
	/// template signature.
	///
	/// This template is used to specify the mapping (offset, count) of
	/// a specific datum within the bitset, without the need of repeating
	/// the mapping for read and write operations.
	template <std::size_t Offset, std::size_t Count, typename T> struct bitset_value final {
		static constexpr std::size_t offset = Offset;
		static constexpr std::size_t count = Count;
		using value_type = T;

		bitset_value(T t)
			: value(t)
		{
		}

		bitset_value(const bitset_value &) = default;
		bitset_value & operator=(const bitset_value &) = default;

		bitset_value(bitset_value &&) = default;
		bitset_value & operator=(bitset_value &&) = default;

		operator T() const { return value; }

		bitset_value & operator=(T t)
		{
			value = t;
			return *this;
		}

		T value;
	};

	explicit message(message_id type)
		: message_type(type)
	{
	}

	virtual raw get_data() const = 0;

	/// @{

	static std::string read_string(
		const raw & bits, raw::size_type ofs, raw::size_type count_sixbits);

	static void write_string(
		raw & bits, raw::size_type ofs, raw::size_type count_sixbits, const std::string & s);

	/// @}

	/// @{

	/// Reads data from the AIS message (bitset).
	/// This is the `enum` variant.
	///
	/// @tparam T `bitset_value` type.
	/// @param[in] bits The AIS message to read from.
	/// @param[out] t The data read from the message.
	///
	template <typename T,
		typename std::enable_if<std::is_enum<typename T::value_type>::value, int>::type = 0>
	static void get(const raw & bits, T & t)
	{
		typename std::underlying_type<typename T::value_type>::type tmp;
		bits.get(tmp, T::offset, T::count);
		t.value = static_cast<typename T::value_type>(tmp);
	}

	/// The non `enum` and non `string` variant of `get`.
	/// @see get
	template <typename T, typename std::enable_if<!std::is_enum<typename T::value_type>::value
								  && !std::is_same<typename T::value_type, std::string>::value,
							  int>::type
		= 0>
	static void get(const raw & bits, T & t)
	{
		bits.get(t.value, T::offset, T::count);
	}

	/// The `string` variant of `get`.
	/// @see get
	template <typename T, typename std::enable_if<!std::is_enum<typename T::value_type>::value
								  && std::is_same<typename T::value_type, std::string>::value,
							  int>::type
		= 0>
	static void get(const raw & bits, T & t)
	{
		t.value = read_string(bits, T::offset, T::count);
	}

	/// @}

	/// @{

	/// Writes data to the AIS message (bitset).
	/// This is the `enum` variant.
	///
	/// @tparam T `bitset_value` type.
	/// @param[in] bits The AIS message to write to.
	/// @param[out] t The data to write into the message.
	///
	template <typename T,
		typename std::enable_if<std::is_enum<typename T::value_type>::value, int>::type = 0>
	static void set(raw & bits, const T & t)
	{
		bits.set(
			static_cast<typename std::underlying_type<typename T::value_type>::type>(t.value),
			T::offset, T::count);
	}

	/// The non `enum` and non `string` variant of `set`.
	/// @see set
	template <typename T, typename std::enable_if<!std::is_enum<typename T::value_type>::value
								  && !std::is_same<typename T::value_type, std::string>::value,
							  int>::type
		= 0>
	static void set(raw & bits, const T & t)
	{
		bits.set(t.value, T::offset, T::count);
	}

	/// The `string` variant of `set`.
	/// @see set
	template <typename T, typename std::enable_if<!std::is_enum<typename T::value_type>::value
								  && std::is_same<typename T::value_type, std::string>::value,
							  int>::type
		= 0>
	static void set(raw & bits, const T & t)
	{
		write_string(bits, T::offset, T::count, t.value);
	}

	/// @}

private:
	message_id message_type;
};

/// Helper function to parse a specific sentence.
template <class T> std::unique_ptr<message> message_parse(const raw & bits)
{
	return std::unique_ptr<T>(new T{bits});
}

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
}
/// @endcond

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

/// const variant.
///
/// @see message_cast(message * s)
template <class T> const T * message_cast(const message * s)
{
	return detail::check_cast<T>(s) ? static_cast<const T *>(s) : nullptr;
}

/// std::unique_ptr variant.
///
/// @see message_cast(message * s)
template <class T> T * message_cast(std::unique_ptr<message> & s)
{
	return message_cast<T>(s.get());
}

/// const std::unique_ptr variant.
///
/// @see message_cast(message * s)
template <class T> const T * message_cast(const std::unique_ptr<message> & s)
{
	return message_cast<const T>(s.get());
}

/// @}

/// @cond DEV

#define MARNAV_AIS_MESSAGE_FRIENDS(s)                                    \
	friend std::unique_ptr<message> detail::parse_##s(const raw & bits); \
	template <class T> friend std::unique_ptr<message> message_parse(const raw & bits);

#define MARNAV_AIS_DECLARE_MESSAGE_PARSE_FUNC(s)          \
	namespace detail                                      \
	{                                                     \
	std::unique_ptr<message> parse_##s(const raw & bits); \
	}

#define MARNAV_AIS_DEFINE_MESSAGE_PARSE_FUNC(s)          \
	namespace detail                                     \
	{                                                    \
	std::unique_ptr<message> parse_##s(const raw & bits) \
	{                                                    \
		return std::unique_ptr<s>(new s{bits});          \
	}                                                    \
	}

/// @endcond
}
}

#endif
