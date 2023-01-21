#ifndef MARNAV_AIS_BINARY_001_11_HPP
#define MARNAV_AIS_BINARY_001_11_HPP

#include <marnav/ais/binary_data.hpp>
#include <marnav/geo/position.hpp>
#include <optional>

namespace marnav::ais
{
/// @brief Meteorological and Hydrological Data (IMO236).
///
class binary_001_11 final : public binary_data
{
public:
	/// This offset is the size of the header of the binary message 08,
	/// which carries the binary information of this class.
	/// For convenience (see bitset value mapping below), the offsets
	/// are the same as the documentation for easier reading and understanding.
	/// It is also less error prone. This means however, the offset
	/// must be computed, which is a minor nuisance, especially since
	/// the header of the message 08 must not be included in this header.
	constexpr static uint32_t MSG08_HEAD = 56;

	constexpr static uint32_t SIZE_BITS = 352 - MSG08_HEAD;

	constexpr static uint32_t lat_not_available = 0x7fffff;
	constexpr static uint32_t lon_not_available = 0xffffff;
	constexpr static uint32_t day_not_available = 31;
	constexpr static uint32_t hour_not_available = 31;
	constexpr static uint32_t minute_not_available = 63;
	constexpr static uint32_t wind_speed_avg_not_available = 127;
	constexpr static uint32_t wind_gust_not_available = 127;
	constexpr static uint32_t wind_direction_not_available = 511;
	constexpr static uint32_t wind_gust_direction_not_available = 511;
	constexpr static uint32_t temperature_not_available = 2047;
	constexpr static uint32_t humidity_not_available = 127;
	constexpr static uint32_t dew_point_not_available = 1023;
	constexpr static uint32_t pressure_not_available = 511;
	constexpr static uint32_t visibility_not_available = 255;
	constexpr static uint32_t water_level_not_available = 511;
	constexpr static uint32_t current_speed_not_available = 255;
	constexpr static uint32_t current_direction_not_available = 511;
	constexpr static uint32_t current_depth_not_available = 31;
	constexpr static uint32_t wave_height_not_available = 255;
	constexpr static uint32_t wave_period_not_available = 63;
	constexpr static uint32_t wave_direction_not_available = 511;
	constexpr static uint32_t sea_state_not_available = 15;
	constexpr static uint32_t water_temperature_not_available = 1023;
	constexpr static uint32_t salinity_not_available = 511;

	enum class trend : uint8_t {
		steady = 0,
		decreasing = 1,
		increasing = 2,
		not_available = 3
	};

	enum class ice : uint8_t { no = 0, yes = 1, not_available = 3 };

	enum class precipitation : uint8_t {
		rain = 1,
		thunderstorm = 2,
		freezing_rain = 3,
		mixed_ice = 4,
		snow = 5,
		not_available = 7
	};

	void read_from(const raw & payload);
	void write_to(raw & payload) const;

private:
	// clang-format off
	bitset_value< 56 - MSG08_HEAD, 24, uint32_t     > lat_ = lat_not_available;
	bitset_value< 80 - MSG08_HEAD, 25, uint32_t     > lon_ = lon_not_available;
	bitset_value<105 - MSG08_HEAD,  5, uint32_t     > day_ = day_not_available; /// @todo Investigation about range and not_available value, because 31 could be a valid day in the range of 1..31
	bitset_value<110 - MSG08_HEAD,  5, uint32_t     > hour_ = hour_not_available;
	bitset_value<115 - MSG08_HEAD,  6, uint32_t     > minute_ = minute_not_available;
	bitset_value<121 - MSG08_HEAD,  7, uint32_t     > wind_speed_avg_ = wind_speed_avg_not_available;
	bitset_value<128 - MSG08_HEAD,  7, uint32_t     > wind_gust_ = wind_gust_not_available;
	bitset_value<135 - MSG08_HEAD,  9, uint32_t     > wind_direction_ = wind_direction_not_available;
	bitset_value<144 - MSG08_HEAD,  9, uint32_t     > wind_gust_direction_ = wind_gust_direction_not_available;
	bitset_value<153 - MSG08_HEAD, 11, uint32_t     > temperature_ = temperature_not_available;
	bitset_value<164 - MSG08_HEAD,  7, uint32_t     > humidity_ = humidity_not_available;
	bitset_value<171 - MSG08_HEAD, 10, uint32_t     > dew_point_ = dew_point_not_available;
	bitset_value<181 - MSG08_HEAD,  9, uint32_t     > pressure_ = pressure_not_available;
	bitset_value<190 - MSG08_HEAD,  2, trend        > pressure_trend_ = trend::not_available;
	bitset_value<192 - MSG08_HEAD,  8, uint32_t     > visibility_ = visibility_not_available;
	bitset_value<200 - MSG08_HEAD,  9, uint32_t     > water_level_ = water_level_not_available;
	bitset_value<209 - MSG08_HEAD,  2, trend        > water_level_trend_ = trend::not_available;
	bitset_value<211 - MSG08_HEAD,  8, uint32_t     > surface_current_speed_ = current_speed_not_available;
	bitset_value<219 - MSG08_HEAD,  9, uint32_t     > surface_current_direction_ = current_direction_not_available;
	bitset_value<228 - MSG08_HEAD,  8, uint32_t     > current_2_speed_ = current_speed_not_available;
	bitset_value<236 - MSG08_HEAD,  9, uint32_t     > current_2_direction_ = current_direction_not_available;
	bitset_value<245 - MSG08_HEAD,  5, uint32_t     > current_2_depth_ = current_depth_not_available;
	bitset_value<250 - MSG08_HEAD,  8, uint32_t     > current_3_speed_ = current_speed_not_available;
	bitset_value<258 - MSG08_HEAD,  9, uint32_t     > current_3_direction_ = current_direction_not_available;
	bitset_value<267 - MSG08_HEAD,  5, uint32_t     > current_3_depth_ = current_depth_not_available;
	bitset_value<272 - MSG08_HEAD,  8, uint32_t     > wave_height_ = wave_height_not_available;
	bitset_value<280 - MSG08_HEAD,  6, uint32_t     > wave_period_ = wave_period_not_available;
	bitset_value<286 - MSG08_HEAD,  9, uint32_t     > wave_direction_ = wave_direction_not_available;
	bitset_value<295 - MSG08_HEAD,  8, uint32_t     > swell_height_ = wave_height_not_available;
	bitset_value<303 - MSG08_HEAD,  6, uint32_t     > swell_period_ = wave_period_not_available;
	bitset_value<309 - MSG08_HEAD,  9, uint32_t     > swell_direction_ = wave_direction_not_available;
	bitset_value<318 - MSG08_HEAD,  4, uint32_t     > sea_state_ = sea_state_not_available;
	bitset_value<322 - MSG08_HEAD, 10, uint32_t     > water_temperature_ = water_temperature_not_available;
	bitset_value<332 - MSG08_HEAD,  3, precipitation> precipitation_type_ = precipitation::not_available;
	bitset_value<335 - MSG08_HEAD,  9, uint32_t     > sailinity_ = salinity_not_available;
	bitset_value<344 - MSG08_HEAD,  2, ice          > ice_info_ = ice::not_available;
	// clang-format on

public:
	std::optional<geo::position> get_position() const;
	std::optional<uint32_t> get_day() const;
	std::optional<uint32_t> get_hour() const;
	std::optional<uint32_t> get_minute() const;
	std::optional<uint32_t> get_wind_speed_avg() const;
	std::optional<uint32_t> get_wind_gust() const;
	std::optional<uint32_t> get_wind_direction() const;
	std::optional<uint32_t> get_wind_gust_direction() const;
	std::optional<double> get_temperature() const;
	std::optional<uint32_t> get_humidity() const;
	std::optional<double> get_dew_point() const;
	std::optional<uint32_t> get_pressure() const;
	std::optional<trend> get_pressure_trend() const;
	std::optional<double> get_visibility() const;
	std::optional<double> get_water_level() const;
	std::optional<trend> get_water_level_trend() const;
	std::optional<double> get_surface_current_speed() const;
	std::optional<uint32_t> get_surface_current_direction() const;
	std::optional<double> get_current_2_speed() const;
	std::optional<uint32_t> get_current_2_direction() const;
	std::optional<uint32_t> get_current_2_depth() const;
	std::optional<double> get_current_3_speed() const;
	std::optional<uint32_t> get_current_3_direction() const;
	std::optional<uint32_t> get_current_3_depth() const;
	std::optional<double> get_wave_height() const;
	std::optional<uint32_t> get_wave_period() const;
	std::optional<uint32_t> get_wave_direction() const;
	std::optional<double> get_swell_height() const;
	std::optional<uint32_t> get_swell_period() const;
	std::optional<uint32_t> get_swell_direction() const;
	std::optional<uint32_t> get_sea_state() const;
	std::optional<double> get_water_temperature() const;
	std::optional<precipitation> get_precipitation() const;
	std::optional<double> get_salinity() const;
	std::optional<ice> get_ice() const;

	void set_position(std::optional<geo::position> t);
	void set_day(std::optional<uint32_t> t);
	void set_hour(std::optional<uint32_t> t);
	void set_minute(std::optional<uint32_t> t);
	void set_wind_speed_avg(std::optional<uint32_t> t);
	void set_wind_gust(std::optional<uint32_t> t);
	void set_wind_direction(std::optional<uint32_t> t);
	void set_wind_gust_direction(std::optional<uint32_t> t);
	void set_temperature(std::optional<double> t);
	void set_humidity(std::optional<uint32_t> t);
	void set_dew_point(std::optional<double> t);
	void set_pressure(std::optional<uint32_t> t);
	void set_pressure_trend(std::optional<trend> t);
	void set_visibility(std::optional<double> t);
	void set_water_level(std::optional<double> t);
	void set_water_level_trend(std::optional<trend> t);
	void set_surface_current_speed(std::optional<double> t);
	void set_surface_current_direction(std::optional<uint32_t> t);
	void set_current_2_speed(std::optional<double> t);
	void set_current_2_direction(std::optional<uint32_t> t);
	void set_current_2_depth(std::optional<uint32_t> t);
	void set_current_3_speed(std::optional<double> t);
	void set_current_3_direction(std::optional<uint32_t> t);
	void set_current_3_depth(std::optional<uint32_t> t);
	void set_wave_height(std::optional<double> t);
	void set_wave_period(std::optional<uint32_t> t);
	void set_wave_direction(std::optional<uint32_t> t);
	void set_swell_height(std::optional<double> t);
	void set_swell_period(std::optional<uint32_t> t);
	void set_swell_direction(std::optional<uint32_t> t);
	void set_sea_state(std::optional<uint32_t> t);
	void set_water_temperature(std::optional<double> t);
	void set_precipitation(std::optional<precipitation> t);
	void set_salinity(std::optional<double> t);
	void set_ice(std::optional<ice> t);
};
}

#endif
