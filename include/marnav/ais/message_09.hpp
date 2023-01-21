#ifndef MARNAV_AIS_MESSAGE_09_HPP
#define MARNAV_AIS_MESSAGE_09_HPP

#include <marnav/ais/message.hpp>
#include <marnav/geo/angle.hpp>
#include <marnav/units/units.hpp>
#include <marnav/utils/mmsi.hpp>
#include <optional>

namespace marnav::ais
{
/// @brief Standard SAR Aircraft Position Report.
class message_09 : public message
{
	friend class detail::factory;

public:
	constexpr static message_id ID = message_id::standard_sar_aircraft_position_report;
	constexpr static std::size_t SIZE_BITS = 168u;

	constexpr static uint32_t altitude_not_available = 4095;
	constexpr static uint32_t altitude_max = 4094;

	message_09();
	message_09(const message_09 &) = default;
	message_09 & operator=(const message_09 &) = default;
	message_09(message_09 &&) = default;
	message_09 & operator=(message_09 &&) = default;

protected:
	message_09(const raw & bits);
	void read_data(const raw & bits);
	raw get_data() const override;

private:
	// clang-format off
	bitset_value<  6,  2, uint32_t     > repeat_indicator_ = 0;
	bitset_value<  8, 30, uint32_t     > mmsi_ = 0;
	bitset_value< 38, 12, uint32_t     > altitude_ = altitude_not_available;
	bitset_value< 50, 10, uint32_t     > speed_ = sog_not_available; // speed over ground in knots
	bitset_value< 60,  1, bool         > position_accuracy_ = false;
	bitset_value< 61, 28, uint32_t     > longitude_minutes_ = longitude_not_available; // in 10000 minutes
	bitset_value< 89, 27, uint32_t     > latitude_minutes_ = latitude_not_available; // in 10000 minutes
	bitset_value<116, 12, uint32_t     > course_ = cog_not_available; // in 0.1 degrees
	bitset_value<128,  6, uint32_t     > utc_second_ = second_not_available;
	bitset_value<134,  8, uint8_t      > reserved_ = 0;
	bitset_value<142,  1, data_terminal> dte_ = data_terminal::not_ready;
	bitset_value<146,  1, bool         > assigned_ = false;
	bitset_value<147,  1, bool         > raim_ = false;
	bitset_value<148, 20, uint32_t     > radio_status_ = 0;
	// clang-format on

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator_; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi_}; }
	std::optional<units::meters> get_altitude() const noexcept;
	std::optional<units::knots> get_speed() const noexcept;
	bool get_position_accuracy() const noexcept { return position_accuracy_; }
	uint32_t get_course() const noexcept { return course_; }
	uint32_t get_utc_second() const noexcept { return utc_second_; }
	data_terminal get_dte() const noexcept { return dte_; }
	bool get_assigned() const noexcept { return assigned_; }
	bool get_raim() const noexcept { return raim_; }
	uint32_t get_radio_status() const noexcept { return radio_status_; }

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator_ = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi_ = t; }

	void set_altitude_unavailable();
	void set_altitude(units::length t);

	void set_speed_unavailable();
	void set_speed(units::velocity t);

	void set_position_accuracy(bool t) noexcept { position_accuracy_ = t; }
	void set_course(uint32_t t) noexcept { course_ = t; }
	void set_utc_second(uint32_t t) noexcept { utc_second_ = t; }
	void set_dte(data_terminal t) noexcept { dte_ = t; }
	void set_assigned(bool t) noexcept { assigned_ = t; }
	void set_raim(bool t) noexcept { raim_ = t; }
	void set_radio_status(uint32_t t) noexcept { radio_status_ = t; }

	std::optional<geo::longitude> get_lon() const;
	std::optional<geo::latitude> get_lat() const;
	void set_lon_unavailable();
	void set_lat_unavailable();
	void set_lon(const geo::longitude & t);
	void set_lat(const geo::latitude & t);
};
}

#endif
