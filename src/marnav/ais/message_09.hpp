#ifndef MARNAV__AIS__MESSAGE_09__HPP
#define MARNAV__AIS__MESSAGE_09__HPP

#include <marnav/ais/message.hpp>
#include <marnav/geo/angle.hpp>
#include <marnav/utils/mmsi.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace ais
{
/// @brief Standard SAR Aircraft Position Report.
class message_09 : public message
{
	friend class detail::factory;

public:
	constexpr static message_id ID = message_id::standard_sar_aircraft_position_report;
	constexpr static std::size_t SIZE_BITS = 168u;

	constexpr static uint32_t altitude_not_available = 4095;

	message_09();
	message_09(const message_09 &) = default;
	message_09 & operator=(const message_09 &) = default;
	message_09(message_09 &&) = default;
	message_09 & operator=(message_09 &&) = default;

protected:
	message_09(const raw & bits);
	void read_data(const raw & bits);
	virtual raw get_data() const override;

private:
	// clang-format off
	bitset_value<  6,  2, uint32_t     > repeat_indicator = 0;
	bitset_value<  8, 30, uint32_t     > mmsi = 0;
	bitset_value< 38, 12, uint32_t     > altitude = altitude_not_available;
	bitset_value< 50, 10, uint32_t     > speed = sog_not_available; // speed over ground in knots
	bitset_value< 60,  1, bool         > position_accuracy = false;
	bitset_value< 61, 28, uint32_t     > longitude_minutes = longitude_not_available; // in 10000 minutes
	bitset_value< 89, 27, uint32_t     > latitude_minutes = latitude_not_available; // in 10000 minutes
	bitset_value<116, 12, uint32_t     > course = cog_not_available; // in 0.1 degrees
	bitset_value<128,  6, uint32_t     > utc_second = second_not_available;
	bitset_value<134,  8, uint8_t      > reserved = 0;
	bitset_value<142,  1, data_terminal> dte = data_terminal::not_ready;
	bitset_value<146,  1, bool         > assigned = false;
	bitset_value<147,  1, bool         > raim = false;
	bitset_value<148, 20, uint32_t     > radio_status = 0;
	// clang-format on

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi}; }
	uint32_t get_altitude() const noexcept { return altitude; }
	uint32_t get_speed() const noexcept { return speed; }
	bool get_position_accuracy() const noexcept { return position_accuracy; }
	uint32_t get_course() const noexcept { return course; }
	uint32_t get_utc_second() const noexcept { return utc_second; }
	data_terminal get_dte() const noexcept { return dte; }
	bool get_assigned() const noexcept { return assigned; }
	bool get_raim() const noexcept { return raim; }
	uint32_t get_radio_status() const noexcept { return radio_status; }

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi = t; }
	void set_altitude(uint32_t t) noexcept { altitude = t; }
	void set_speed(uint32_t t) noexcept { speed = t; }
	void set_position_accuracy(bool t) noexcept { position_accuracy = t; }
	void set_course(uint32_t t) noexcept { course = t; }
	void set_utc_second(uint32_t t) noexcept { utc_second = t; }
	void set_dte(data_terminal t) noexcept { dte = t; }
	void set_assigned(bool t) noexcept { assigned = t; }
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
