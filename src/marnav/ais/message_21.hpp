#ifndef __AIS__MESSAGE_21__HPP__
#define __AIS__MESSAGE_21__HPP__

#include <marnav/ais/message.hpp>
#include <marnav/geo/angle.hpp>
#include <marnav/utils/mmsi.hpp>

namespace marnav
{
namespace ais
{
MARNAV_AIS_DECLARE_MESSAGE_PARSE_FUNC(message_21)

/// @brief Aid-to-Navigation Report
class message_21 : public message
{
	MARNAV_AIS_MESSAGE_FRIENDS(message_21)

public:
	constexpr static const message_id ID = message_id::aid_to_navigation_report;
	constexpr static const int SIZE_BITS_MIN = 272;
	constexpr static const int SIZE_BITS_MAX = 360;

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

	enum class virtual_aid : uint32_t { real_aid = 0, virtual_aid = 1 };

	enum class off_position_indicator : uint32_t { on_position = 0, off_position = 1 };

	virtual ~message_21() {}

	message_21();
	message_21(const message_21 &) = default;
	message_21 & operator=(const message_21 &) = default;

protected:
	message_21(const raw & bits);
	void read_data(const raw & bits);
	virtual raw get_data() const override;

private:
	// clang-format off
	bitset_value<  6,  2, uint32_t              > repeat_indicator = 0;
	bitset_value<  8, 30, uint32_t              > mmsi = 0;
	bitset_value< 38,  5, aid_type_id           > aid_type = aid_type_id::unspecified;
	bitset_value< 43, 20, std::string           > name;
	bitset_value<163,  1, bool                  > position_accuracy = false;
	bitset_value<164, 28, uint32_t              > longitude_minutes = longitude_not_available; // in 10000 minutes
	bitset_value<192, 27, uint32_t              > latitude_minutes = latitude_not_available; // in 10000 minutes
	bitset_value<219,  9, uint32_t              > to_bow = 0;
	bitset_value<228,  9, uint32_t              > to_stern = 0;
	bitset_value<237,  6, uint32_t              > to_port = 0;
	bitset_value<243,  6, uint32_t              > to_starboard = 0;
	bitset_value<249,  4, epfd_fix_type         > epfd_fix = epfd_fix_type::undefined;
	bitset_value<253,  6, uint32_t              > utc_second = 0;
	bitset_value<259,  1, off_position_indicator> off_position = off_position_indicator::off_position;
	bitset_value<260,  8, uint8_t               > regional = 0;
	bitset_value<268,  1, bool                  > raim = false;
	bitset_value<269,  1, virtual_aid           > virtual_aid_flag = virtual_aid::virtual_aid;
	bitset_value<270,  1, bool                  > assigned = false;
	std::string name_extension;
	// clang-format on

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi}; }
	aid_type_id get_aid_type() const noexcept { return aid_type; }
	std::string get_name() const;
	bool get_position_accuracy() const noexcept { return position_accuracy; }
	uint32_t get_to_bow() const noexcept { return to_bow; }
	uint32_t get_to_stern() const noexcept { return to_stern; }
	uint32_t get_to_port() const noexcept { return to_port; }
	uint32_t get_to_starboard() const noexcept { return to_starboard; }
	epfd_fix_type get_epfd_fix() const noexcept { return epfd_fix; }
	uint32_t get_utc_second() const noexcept { return utc_second; }
	off_position_indicator get_off_position() const noexcept { return off_position; }
	uint8_t get_regional() const noexcept { return regional; }
	bool get_raim() const noexcept { return raim; }
	virtual_aid get_virtual_aid_flag() const noexcept { return virtual_aid_flag; }
	bool get_assigned() const noexcept { return assigned; }
	std::string get_name_extension() const;

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi = t; }
	void set_aid_type(aid_type_id t) noexcept { aid_type = t; }
	void set_name(const std::string & t);
	void set_position_accuracy(bool t) noexcept { position_accuracy = t; }
	void set_to_bow(uint32_t t) noexcept { to_bow = t; }
	void set_to_stern(uint32_t t) noexcept { to_stern = t; }
	void set_to_port(uint32_t t) noexcept { to_port = t; }
	void set_to_starboard(uint32_t t) noexcept { to_starboard = t; }
	void set_epfd_fix(epfd_fix_type t) noexcept { epfd_fix = t; }
	void set_utc_second(uint32_t t) noexcept { utc_second = t; }
	void set_off_position(off_position_indicator t) noexcept { off_position = t; }
	void set_regional(uint8_t t) noexcept { regional = t; }
	void set_raim(bool t) noexcept { raim = t; }
	void set_virtual_aid_flag(virtual_aid t) noexcept { virtual_aid_flag = t; }
	void set_assigned(bool t) noexcept { assigned = t; }
	void set_name_extension(const std::string & t);

	geo::longitude get_longitude() const;
	geo::latitude get_latitude() const;
	void set_longitude(const geo::longitude & t);
	void set_latitude(const geo::latitude & t);
};
}
}

#endif
