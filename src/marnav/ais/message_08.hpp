#ifndef __MARNAV__AIS__MESSAGE_08__HPP__
#define __MARNAV__AIS__MESSAGE_08__HPP__

#include <marnav/ais/message.hpp>
#include <marnav/geo/position.hpp>
#include <marnav/utils/mmsi.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace ais
{
MARNAV_AIS_DECLARE_MESSAGE_PARSE_FUNC(message_08)

/// @brief Binary Broadcast Message
class message_08 : public message
{
	MARNAV_AIS_MESSAGE_FRIENDS(message_08)

public:
	class binary_001_11 final
	{
		friend class message_08;

	public:
		constexpr static const int SIZE_BITS = 352 - 56;

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

	private:
		// clang-format off
		bitset_value< 56 - 56, 24, uint32_t     > lat = lat_not_available;
		bitset_value< 80 - 56, 25, uint32_t     > lon = lon_not_available;
		bitset_value<105 - 56,  5, uint32_t     > day = day_not_available;
		bitset_value<110 - 56,  5, uint32_t     > hour = hour_not_available;
		bitset_value<115 - 56,  6, uint32_t     > minute = minute_not_available;
		bitset_value<121 - 56,  7, uint32_t     > wind_speed_avg = wind_speed_avg_not_available;
		bitset_value<128 - 56,  7, uint32_t     > wind_gust = wind_gust_not_available;
		bitset_value<135 - 56,  9, uint32_t     > wind_direction = wind_direction_not_available;
		bitset_value<144 - 56,  9, uint32_t     > wind_gust_direction = wind_gust_direction_not_available;
		bitset_value<153 - 56, 11, uint32_t     > temperature = temperature_not_available;
		bitset_value<164 - 56,  7, uint32_t     > humidity = humidity_not_available;
		bitset_value<171 - 56, 10, uint32_t     > dew_point = dew_point_not_available;
		bitset_value<181 - 56,  9, uint32_t     > pressure = pressure_not_available;
		bitset_value<190 - 56,  2, trend        > pressure_trend = trend::not_available;
		bitset_value<192 - 56,  8, uint32_t     > visibility = visibility_not_available;
		bitset_value<200 - 56,  9, uint32_t     > water_level = water_level_not_available;
		bitset_value<209 - 56,  2, trend        > water_level_trend = trend::not_available;
		bitset_value<211 - 56,  8, uint32_t     > surface_current_speed = current_speed_not_available;
		bitset_value<219 - 56,  9, uint32_t     > surface_current_direction = current_direction_not_available;
		bitset_value<228 - 56,  8, uint32_t     > current_2_speed = current_speed_not_available;
		bitset_value<236 - 56,  9, uint32_t     > current_2_direction = current_direction_not_available;
		bitset_value<245 - 56,  5, uint32_t     > current_2_depth = current_depth_not_available;
		bitset_value<250 - 56,  8, uint32_t     > current_3_speed = current_speed_not_available;
		bitset_value<258 - 56,  9, uint32_t     > current_3_direction = current_direction_not_available;
		bitset_value<267 - 56,  5, uint32_t     > current_3_depth = current_depth_not_available;
		bitset_value<272 - 56,  8, uint32_t     > wave_height = wave_height_not_available;
		bitset_value<280 - 56,  6, uint32_t     > wave_period = wave_period_not_available;
		bitset_value<286 - 56,  9, uint32_t     > wave_direction = wave_direction_not_available;
		bitset_value<295 - 56,  8, uint32_t     > swell_height = wave_height_not_available;
		bitset_value<303 - 56,  6, uint32_t     > swell_period = wave_period_not_available;
		bitset_value<309 - 56,  9, uint32_t     > swell_direction = wave_direction_not_available;
		bitset_value<318 - 56,  4, uint32_t     > sea_state = sea_state_not_available;
		bitset_value<322 - 56, 10, uint32_t     > water_temperature = water_temperature_not_available;
		bitset_value<332 - 56,  3, precipitation> precipitation_type = precipitation::not_available;
		bitset_value<335 - 56,  9, uint32_t     > sailinity = salinity_not_available;
		bitset_value<344 - 56,  2, ice          > ice_info = ice::not_available;
		// clang-format on

	public:
		utils::optional<geo::position> get_position() const;
		utils::optional<uint32_t> get_day() const;
		utils::optional<uint32_t> get_hour() const;
		utils::optional<uint32_t> get_minute() const;
		utils::optional<uint32_t> get_wind_speed_avg() const;
		utils::optional<uint32_t> get_wind_gust() const;
		utils::optional<uint32_t> get_wind_direction() const;
		utils::optional<uint32_t> get_wind_gust_direction() const;
		utils::optional<double> get_temperature() const;
		utils::optional<uint32_t> get_humidity() const;
		utils::optional<double> get_dew_point() const;
		utils::optional<uint32_t> get_pressure() const;
		utils::optional<trend> get_pressure_trend() const;
		utils::optional<double> get_visibility() const;
		utils::optional<double> get_water_level() const;
		utils::optional<trend> get_water_level_trend() const;
		utils::optional<double> get_surface_current_speed() const;
		utils::optional<uint32_t> get_surface_current_direction() const;
		utils::optional<double> get_current_2_speed() const;
		utils::optional<uint32_t> get_current_2_direction() const;
		utils::optional<uint32_t> get_current_2_depth() const;
		utils::optional<double> get_current_3_speed() const;
		utils::optional<uint32_t> get_current_3_direction() const;
		utils::optional<uint32_t> get_current_3_depth() const;
		utils::optional<double> get_wave_height() const;
		utils::optional<uint32_t> get_wave_period() const;
		utils::optional<uint32_t> get_wave_direction() const;
		utils::optional<double> get_swell_height() const;
		utils::optional<uint32_t> get_swell_period() const;
		utils::optional<uint32_t> get_swell_direction() const;
		utils::optional<uint32_t> get_sea_state() const;
		utils::optional<double> get_water_temperature() const;
		utils::optional<precipitation> get_precipitation() const;
		utils::optional<double> get_salinity() const;
		utils::optional<ice> get_ice() const;

		void set_position(utils::optional<geo::position> t);
		void set_day(utils::optional<uint32_t> t);
		void set_hour(utils::optional<uint32_t> t);
		void set_minute(utils::optional<uint32_t> t);
		void set_wind_speed_avg(utils::optional<uint32_t> t);
		void set_wind_gust(utils::optional<uint32_t> t);
		void set_wind_direction(utils::optional<uint32_t> t);
		void set_wind_gust_direction(utils::optional<uint32_t> t);
		void set_temperature(utils::optional<double> t);
		void set_humidity(utils::optional<uint32_t> t);
		void set_dew_point(utils::optional<double> t);
		void set_pressure(utils::optional<uint32_t> t);
		void set_pressure_trend(utils::optional<trend> t);
		void set_visibility(utils::optional<double> t);
		void set_water_level(utils::optional<double> t);
		void set_water_level_trend(utils::optional<trend> t);
		void set_surface_current_speed(utils::optional<double> t);
		void set_surface_current_direction(utils::optional<uint32_t> t);
		void set_current_2_speed(utils::optional<double> t);
		void set_current_2_direction(utils::optional<uint32_t> t);
		void set_current_2_depth(utils::optional<uint32_t> t);
		void set_current_3_speed(utils::optional<double> t);
		void set_current_3_direction(utils::optional<uint32_t> t);
		void set_current_3_depth(utils::optional<uint32_t> t);
		void set_wave_height(utils::optional<double> t);
		void set_wave_period(utils::optional<uint32_t> t);
		void set_wave_direction(utils::optional<uint32_t> t);
		void set_swell_height(utils::optional<double> t);
		void set_swell_period(utils::optional<uint32_t> t);
		void set_swell_direction(utils::optional<uint32_t> t);
		void set_sea_state(utils::optional<uint32_t> t);
		void set_water_temperature(utils::optional<double> t);
		void set_precipitation(utils::optional<precipitation> t);
		void set_salinity(utils::optional<double> t);
		void set_ice(utils::optional<ice> t);
	};

	constexpr static const message_id ID = message_id::binary_broadcast_message;
	constexpr static const int SIZE_BITS_HEAD = 56;
	constexpr static const int SIZE_BITS_MAX = 1008;

	message_08();
	message_08(const message_08 &) = default;
	message_08 & operator=(const message_08 &) = default;
	message_08(message_08 &&) = default;
	message_08 & operator=(message_08 &&) = default;

protected:
	message_08(const raw & bits);
	void read_data(const raw & bits);
	virtual raw get_data() const override;

private:
	// clang-format off
	bitset_value< 6,  2, uint32_t> repeat_indicator = 0;
	bitset_value< 8, 30, uint32_t> mmsi = 0;
	bitset_value<40, 10, uint32_t> dac = 0; ///< Designate Area Cod3
	bitset_value<50,  6, uint32_t> fid = 0; ///< Functional ID
	// clang-format on

	// unfortuanately std::variant is C++17, therefore we need to store
	// the binary payload and parse it later.
	raw payload;

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi}; }
	uint32_t get_dac() const noexcept { return dac; }
	uint32_t get_fid() const noexcept { return fid; }

	// payload
	binary_001_11 get_binary_001_11() const;

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi = t; }
	void set_dac(uint32_t t) noexcept { dac = t; }
	void set_fid(uint32_t t) noexcept { fid = t; }

	// payload
	void set_binary_001_11(const binary_001_11 & m);
};
}
}

#endif
