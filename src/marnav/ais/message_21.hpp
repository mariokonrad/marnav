#ifndef __AIS__MESSAGE_21__HPP__
#define __AIS__MESSAGE_21__HPP__

#include <marnav/ais/message.hpp>
#include <marnav/geo/angle.hpp>
#include <marnav/utils/mmsi.hpp>

namespace marnav
{
namespace ais
{

/// @brief Aid-to-Navigation Report
class message_21 : public message
{
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

	message_21();
	message_21(const message_21 &) = default;
	message_21 & operator=(const message_21 &) = default;

	virtual raw get_data() const throw(std::out_of_range) override;

	static std::unique_ptr<message> parse(const raw & bits) throw(
		std::invalid_argument, std::out_of_range);

protected:
	void read_data(const raw & bits) throw(std::out_of_range);

private:
	unsigned int repeat_indicator;
	uint32_t mmsi;
	aid_type_id aid_type;
	std::string name;
	bool position_accuracy;
	uint32_t longitude_minutes; // in 10000 minutes
	uint32_t latitude_minutes; // in 10000 minutes
	uint32_t to_bow;
	uint32_t to_stern;
	uint32_t to_port;
	uint32_t to_starboard;
	epfd_fix_type epfd_fix;
	uint32_t utc_second;
	off_position_indicator off_position;
	uint8_t regional;
	bool raim;
	virtual_aid virtual_aid_flag;
	bool assigned;
	std::string name_extension;

public:
	unsigned int get_repeat_indicator() const { return repeat_indicator; }
	utils::mmsi get_mmsi() const { return utils::mmsi{mmsi}; }
	aid_type_id get_aid_type() const { return aid_type; }
	std::string get_name() const { return name; }
	bool get_position_accuracy() const { return position_accuracy; }
	uint32_t get_to_bow() const { return to_bow; }
	uint32_t get_to_stern() const { return to_stern; }
	uint32_t get_to_port() const { return to_port; }
	uint32_t get_to_starboard() const { return to_starboard; }
	epfd_fix_type get_epfd_fix() const { return epfd_fix; }
	uint32_t get_utc_second() const { return utc_second; }
	off_position_indicator get_off_position() const { return off_position; }
	uint8_t get_regional() const { return regional; }
	bool get_raim() const { return raim; }
	virtual_aid get_virtual_aid_flag() const { return virtual_aid_flag; }
	bool get_assigned() const { return assigned; }
	std::string get_name_extension() const { return name_extension; }

	void set_repeat_indicator(unsigned int t) { repeat_indicator = t; }
	void set_mmsi(const utils::mmsi & t) { mmsi = t; }
	void set_aid_type(aid_type_id t) { aid_type = t; }
	void set_name(const std::string & t);
	void set_position_accuracy(bool t) { position_accuracy = t; }
	void set_to_bow(uint32_t t) { to_bow = t; }
	void set_to_stern(uint32_t t) { to_stern = t; }
	void set_to_port(uint32_t t) { to_port = t; }
	void set_to_starboard(uint32_t t) { to_starboard = t; }
	void set_epfd_fix(epfd_fix_type t) { epfd_fix = t; }
	void set_utc_second(uint32_t t) { utc_second = t; }
	void set_off_position(off_position_indicator t) { off_position = t; }
	void set_regional(uint8_t t) { regional = t; }
	void set_raim(bool t) { raim = t; }
	void set_virtual_aid_flag(virtual_aid t) { virtual_aid_flag = t; }
	void set_assigned(bool t) { assigned = t; }
	void set_name_extension(const std::string & t);

	geo::longitude get_longitude() const;
	geo::latitude get_latitude() const;
	void set_longitude(const geo::longitude & t);
	void set_latitude(const geo::latitude & t);
};
}
}

#endif
