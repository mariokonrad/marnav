#ifndef __AIS__MESSAGE_01__HPP__
#define __AIS__MESSAGE_01__HPP__

#include <marnav/ais/message.hpp>
#include <marnav/geo/angle.hpp>
#include <marnav/utils/mmsi.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace ais
{
MARNAV_AIS_DECLARE_MESSAGE_PARSE_FUNC(message_01)

/// @brief Position Report Class A
class message_01 : public message
{
	MARNAV_AIS_MESSAGE_FRIENDS(message_01)

public:
	constexpr static const message_id ID = message_id::position_report_class_a;
	constexpr static const int SIZE_BITS = 168;

	virtual ~message_01() {}

	message_01();
	message_01(const message_01 &) = default;
	message_01 & operator=(const message_01 &) = default;

protected:
	message_01(message_id id);
	message_01(const raw & bits);
	void read_data(const raw & bits);
	virtual raw get_data() const override;

private:
	// clang-format off
	bitset_value<  6,  2, uint32_t         > repeat_indicator = 0;
	bitset_value<  8, 30, uint32_t         > mmsi = 0;
	bitset_value< 38,  4, navigation_status> nav_status = navigation_status::not_defined;
	bitset_value< 42,  8, int32_t          > rot = rot_not_available; // rate of turn, raw format
	bitset_value< 50, 10, uint32_t         > sog = sog_not_available; // in 0.1 knots
	bitset_value< 60,  1, bool             > position_accuracy = false;
	bitset_value< 61, 28, uint32_t         > longitude_minutes = longitude_not_available; // in 10000 minutes
	bitset_value< 89, 27, uint32_t         > latitude_minutes = latitude_not_available; // in 10000 minutes
	bitset_value<116, 12, uint32_t         > cog = cog_not_available; // 0.1 deg true north
	bitset_value<128,  9, uint32_t         > hdg = hdg_not_available; // true heading in deg
	bitset_value<136,  6, uint32_t         > timestamp = timestamp_not_available;
	bitset_value<143,  2, uint32_t         > maneuver_indicator = maneuver_indictor_not_available;
	bitset_value<148,  1, bool             > raim = false;
	bitset_value<149, 19, uint32_t         > radio_status = 0;
	// clang-format on

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi}; }
	navigation_status get_nav_status() const noexcept { return nav_status; }
	int32_t get_rot() const noexcept { return rot; }
	uint32_t get_sog() const noexcept { return sog; }
	bool get_position_accuracy() const noexcept { return position_accuracy; }
	uint32_t get_cog() const noexcept { return cog; }
	uint32_t get_hdg() const noexcept { return hdg; }
	uint32_t get_timestamp() const noexcept { return timestamp; }
	uint32_t get_maneuver_indicator() const noexcept { return maneuver_indicator; }
	bool get_raim() const noexcept { return raim; }
	uint32_t get_radio_status() const noexcept { return radio_status; }

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi = t; }
	void set_nav_status(navigation_status t) noexcept { nav_status = t; }
	void set_rot(int32_t t) noexcept { rot = t; }
	void set_sog(uint32_t t) noexcept { sog = t; }
	void set_position_accuracy(bool t) noexcept { position_accuracy = t; }
	void set_cog(uint32_t t) noexcept { cog = t; }
	void set_hdg(uint32_t t) noexcept { hdg = t; }
	void set_timestamp(uint32_t t) noexcept { timestamp = t; }
	void set_maneuver_indicator(uint32_t t) noexcept { maneuver_indicator = t; }
	void set_raim(bool t) noexcept { raim = t; }
	void set_radio_status(uint32_t t) noexcept { radio_status = t; }

	utils::optional<geo::longitude> get_longitude() const;
	utils::optional<geo::latitude> get_latitude() const;
	void set_longitude(const utils::optional<geo::longitude> & t);
	void set_latitude(const utils::optional<geo::latitude> & t);
};
}
}

#endif
