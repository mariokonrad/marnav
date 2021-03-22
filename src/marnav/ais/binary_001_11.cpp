#include <marnav/ais/binary_001_11.hpp>
#include <marnav/ais/angle.hpp>
#include <cmath>

/// @todo binary_001_11: Range checks for setters

namespace marnav
{
namespace ais
{
void binary_001_11::read_from(const raw & payload)
{
	if (payload.size() != SIZE_BITS)
		throw std::invalid_argument{"wrong number of bits in playload of binary_001_11"};

	get(payload, lat);
	get(payload, lon);
	get(payload, day);
	get(payload, hour);
	get(payload, minute);
	get(payload, wind_speed_avg);
	get(payload, wind_gust);
	get(payload, wind_direction);
	get(payload, wind_gust_direction);
	get(payload, temperature);
	get(payload, humidity);
	get(payload, dew_point);
	get(payload, pressure);
	get(payload, pressure_trend);
	get(payload, visibility);
	get(payload, water_level);
	get(payload, water_level_trend);
	get(payload, surface_current_speed);
	get(payload, surface_current_direction);
	get(payload, current_2_speed);
	get(payload, current_2_direction);
	get(payload, current_2_depth);
	get(payload, current_3_speed);
	get(payload, current_3_direction);
	get(payload, current_3_depth);
	get(payload, wave_height);
	get(payload, wave_period);
	get(payload, wave_direction);
	get(payload, swell_height);
	get(payload, swell_period);
	get(payload, swell_direction);
	get(payload, sea_state);
	get(payload, water_temperature);
	get(payload, precipitation_type);
	get(payload, sailinity);
	get(payload, ice_info);
}

void binary_001_11::write_to(raw & payload) const
{
	payload = raw(SIZE_BITS);
	set(payload, lat);
	set(payload, lon);
	set(payload, day);
	set(payload, hour);
	set(payload, minute);
	set(payload, wind_speed_avg);
	set(payload, wind_gust);
	set(payload, wind_direction);
	set(payload, wind_gust_direction);
	set(payload, temperature);
	set(payload, humidity);
	set(payload, dew_point);
	set(payload, pressure);
	set(payload, pressure_trend);
	set(payload, visibility);
	set(payload, water_level);
	set(payload, water_level_trend);
	set(payload, surface_current_speed);
	set(payload, surface_current_direction);
	set(payload, current_2_speed);
	set(payload, current_2_direction);
	set(payload, current_2_depth);
	set(payload, current_3_speed);
	set(payload, current_3_direction);
	set(payload, current_3_depth);
	set(payload, wave_height);
	set(payload, wave_period);
	set(payload, wave_direction);
	set(payload, swell_height);
	set(payload, swell_period);
	set(payload, swell_direction);
	set(payload, sea_state);
	set(payload, water_temperature);
	set(payload, precipitation_type);
	set(payload, sailinity);
	set(payload, ice_info);
}

std::optional<geo::position> binary_001_11::get_position() const
{
	if ((lat == lat_not_available) || (lon == lon_not_available))
		return {};
	return {{to_geo_latitude(lat, lat.count, angle_scale::I3),
		to_geo_longitude(lon, lon.count, angle_scale::I3)}};
}

std::optional<uint32_t> binary_001_11::get_day() const
{
	if (day == day_not_available)
		return {};
	return {day};
}

std::optional<uint32_t> binary_001_11::get_hour() const
{
	if (hour == hour_not_available)
		return {};
	return {hour};
}

std::optional<uint32_t> binary_001_11::get_minute() const
{
	if (minute == minute_not_available)
		return {};
	return {minute};
}

std::optional<uint32_t> binary_001_11::get_wind_speed_avg() const
{
	if (wind_speed_avg == wind_speed_avg_not_available)
		return {};
	return {wind_speed_avg};
}

std::optional<uint32_t> binary_001_11::get_wind_gust() const
{
	if (wind_gust == wind_gust_not_available)
		return {};
	return {wind_gust};
}

std::optional<uint32_t> binary_001_11::get_wind_direction() const
{
	if (wind_direction == wind_direction_not_available)
		return {};
	return {wind_direction};
}

std::optional<uint32_t> binary_001_11::get_wind_gust_direction() const
{
	if (wind_gust_direction == wind_gust_direction_not_available)
		return {};
	return {wind_gust_direction};
}

/// Returns the temperature in degrees Celsius between `-60.0` and `+60.0`.
std::optional<double> binary_001_11::get_temperature() const
{
	if (temperature == temperature_not_available)
		return {};
	return -60.0 + 0.1 * temperature;
}

std::optional<uint32_t> binary_001_11::get_humidity() const
{
	if (humidity == humidity_not_available)
		return {};
	return {humidity};
}

/// Returns in degrees Celsius between `-20.0` and `+50.0`.
std::optional<double> binary_001_11::get_dew_point() const
{
	if (dew_point == dew_point_not_available)
		return {};
	return -20.0 + 0.1 * dew_point;
}

/// Returns the pressure in `hPa` between `800` and `1200`.
std::optional<uint32_t> binary_001_11::get_pressure() const
{
	if (pressure == pressure_not_available)
		return {};
	return {800 + pressure};
}

std::optional<binary_001_11::trend> binary_001_11::get_pressure_trend() const
{
	if (pressure_trend == trend::not_available)
		return {};
	return {pressure_trend};
}

/// Returns the visibility in nautical miles.
std::optional<double> binary_001_11::get_visibility() const
{
	if (visibility == visibility_not_available)
		return {};
	return 0.1 * visibility;
}

/// Returns the water level in meters between `-10.0` and `+30.0`.
std::optional<double> binary_001_11::get_water_level() const
{
	if (water_level == water_level_not_available)
		return {};
	return -10.0 + 0.1 * water_level;
}

std::optional<binary_001_11::trend> binary_001_11::get_water_level_trend() const
{
	if (water_level_trend == trend::not_available)
		return {};
	return {water_level_trend};
}

/// Returns the speed in knots.
std::optional<double> binary_001_11::get_surface_current_speed() const
{
	if (surface_current_speed == current_speed_not_available)
		return {};
	return 0.1 * surface_current_speed;
}

std::optional<uint32_t> binary_001_11::get_surface_current_direction() const
{
	if (surface_current_direction == current_direction_not_available)
		return {};
	return {surface_current_direction};
}

/// Returns the speed in knots.
std::optional<double> binary_001_11::get_current_2_speed() const
{
	if (current_2_speed == current_speed_not_available)
		return {};
	return 0.1 * current_2_speed;
}

std::optional<uint32_t> binary_001_11::get_current_2_direction() const
{
	if (current_2_direction == current_direction_not_available)
		return {};
	return {current_2_direction};
}

std::optional<uint32_t> binary_001_11::get_current_2_depth() const
{
	if (current_2_depth == current_depth_not_available)
		return {};
	return {current_2_depth};
}

/// Returns the speed in knots.
std::optional<double> binary_001_11::get_current_3_speed() const
{
	if (current_3_speed == current_speed_not_available)
		return {};
	return 0.1 * current_3_speed;
}

std::optional<uint32_t> binary_001_11::get_current_3_direction() const
{
	if (current_3_direction == current_direction_not_available)
		return {};
	return {current_3_direction};
}

std::optional<uint32_t> binary_001_11::get_current_3_depth() const
{
	if (current_3_depth == current_depth_not_available)
		return {};
	return {current_3_depth};
}

/// Returns the wave height in meters.
std::optional<double> binary_001_11::get_wave_height() const
{
	if (wave_height == wave_height_not_available)
		return {};
	return 0.1 * wave_height;
}

std::optional<uint32_t> binary_001_11::get_wave_period() const
{
	if (wave_period == wave_period_not_available)
		return {};
	return {wave_period};
}

std::optional<uint32_t> binary_001_11::get_wave_direction() const
{
	if (wave_direction == wave_direction_not_available)
		return {};
	return {wave_direction};
}

/// Returns the swell height in meters.
std::optional<double> binary_001_11::get_swell_height() const
{
	if (swell_height == wave_height_not_available)
		return {};
	return 0.1 * swell_height;
}

std::optional<uint32_t> binary_001_11::get_swell_period() const
{
	if (swell_period == wave_period_not_available)
		return {};
	return {swell_period};
}

std::optional<uint32_t> binary_001_11::get_swell_direction() const
{
	if (swell_direction == wave_direction_not_available)
		return {};
	return {swell_direction};
}

std::optional<uint32_t> binary_001_11::get_sea_state() const
{
	if (sea_state == sea_state_not_available)
		return {};
	return {sea_state};
}

/// Returns the water temperature in degrees Celsius between `-10.0` and `+50.0`.
std::optional<double> binary_001_11::get_water_temperature() const
{
	if (water_temperature == water_temperature_not_available)
		return {};
	return -10.0 + 0.1 * water_temperature;
}

std::optional<binary_001_11::precipitation> binary_001_11::get_precipitation() const
{
	if (precipitation_type == precipitation::not_available)
		return {};
	return {precipitation_type};
}

/// Returns the sailinity in percent.
std::optional<double> binary_001_11::get_salinity() const
{
	if (sailinity == salinity_not_available)
		return {};
	return 0.1 * sailinity;
}

std::optional<binary_001_11::ice> binary_001_11::get_ice() const
{
	if (ice_info == ice::not_available)
		return {};
	return {ice_info};
}

void binary_001_11::set_position(std::optional<geo::position> t)
{
	if (!t) {
		lat = lat_not_available;
		lon = lon_not_available;
	} else {
		lat = to_latitude_minutes(t->lat(), lat.count, angle_scale::I3);
		lon = to_longitude_minutes(t->lon(), lon.count, angle_scale::I3);
	}
}

/// Sets the day. Value must be either empty optional or a value between `1` and `31`.
/// A value out of range is treated the same as an empty optional.
void binary_001_11::set_day(std::optional<uint32_t> t)
{
	day = (!t || *t >= 31) ? day_not_available : *t;
}

/// Sets the hour. Value must be either empty optional or a value between `0` and `23`.
/// A value out of range is treated the same as an empty optional.
void binary_001_11::set_hour(std::optional<uint32_t> t)
{
	hour = (!t || *t >= 24) ? hour_not_available : *t;
}

/// Sets the minute. Value must be either empty optional or a value between `0` and `59`.
/// A value out of range is treated the same as an empty optional.
void binary_001_11::set_minute(std::optional<uint32_t> t)
{
	minute = (!t || *t > 59u) ? minute_not_available : *t;
}

void binary_001_11::set_wind_speed_avg(std::optional<uint32_t> t)
{
	wind_speed_avg = !t ? wind_speed_avg_not_available : *t;
}

void binary_001_11::set_wind_gust(std::optional<uint32_t> t)
{
	wind_gust = !t ? wind_gust_not_available : *t;
}

void binary_001_11::set_wind_direction(std::optional<uint32_t> t)
{
	wind_direction = !t ? wind_direction_not_available : *t;
}

void binary_001_11::set_wind_gust_direction(std::optional<uint32_t> t)
{
	wind_gust_direction = !t ? wind_gust_direction_not_available : *t;
}

void binary_001_11::set_temperature(std::optional<double> t)
{
	temperature
		= !t ? temperature_not_available : static_cast<uint32_t>(std::round(*t / 0.1 + 60.0));
}

void binary_001_11::set_humidity(std::optional<uint32_t> t)
{
	humidity = !t ? humidity_not_available : *t;
}

void binary_001_11::set_dew_point(std::optional<double> t)
{
	dew_point
		= !t ? dew_point_not_available : static_cast<uint32_t>(std::round(*t / 0.1 + 20.0));
}

void binary_001_11::set_pressure(std::optional<uint32_t> t)
{
	pressure = !t ? pressure_not_available : *t - 800;
}

void binary_001_11::set_pressure_trend(std::optional<binary_001_11::trend> t)
{
	pressure_trend = !t ? trend::not_available : *t;
}

void binary_001_11::set_visibility(std::optional<double> t)
{
	visibility = !t ? visibility_not_available : static_cast<uint32_t>(std::round(*t / 0.1));
}

void binary_001_11::set_water_level(std::optional<double> t)
{
	water_level
		= !t ? water_level_not_available : static_cast<uint32_t>(std::round(*t / 0.1 + 10.0));
}

void binary_001_11::set_water_level_trend(std::optional<binary_001_11::trend> t)
{
	water_level_trend = !t ? trend::not_available : *t;
}

void binary_001_11::set_surface_current_speed(std::optional<double> t)
{
	surface_current_speed
		= !t ? current_speed_not_available : static_cast<uint32_t>(std::round(*t / 0.1));
}

void binary_001_11::set_surface_current_direction(std::optional<uint32_t> t)
{
	surface_current_direction = !t ? current_direction_not_available : *t;
}

void binary_001_11::set_current_2_speed(std::optional<double> t)
{
	current_2_speed
		= !t ? current_speed_not_available : static_cast<uint32_t>(std::round(*t / 0.1));
}

void binary_001_11::set_current_2_direction(std::optional<uint32_t> t)
{
	current_2_direction = !t ? current_direction_not_available : *t;
}

void binary_001_11::set_current_2_depth(std::optional<uint32_t> t)
{
	current_2_depth = !t ? current_depth_not_available : *t;
}

void binary_001_11::set_current_3_speed(std::optional<double> t)
{
	current_3_speed
		= !t ? current_speed_not_available : static_cast<uint32_t>(std::round(*t / 0.1));
}

void binary_001_11::set_current_3_direction(std::optional<uint32_t> t)
{
	current_3_direction = !t ? current_direction_not_available : *t;
}

void binary_001_11::set_current_3_depth(std::optional<uint32_t> t)
{
	current_3_depth = !t ? current_depth_not_available : *t;
}

void binary_001_11::set_wave_height(std::optional<double> t)
{
	wave_height = !t ? wave_height_not_available : static_cast<uint32_t>(std::round(*t / 0.1));
}

void binary_001_11::set_wave_period(std::optional<uint32_t> t)
{
	wave_period = !t ? wave_period_not_available : *t;
}

void binary_001_11::set_wave_direction(std::optional<uint32_t> t)
{
	wave_direction = !t ? wave_direction_not_available : *t;
}

void binary_001_11::set_swell_height(std::optional<double> t)
{
	swell_height = !t ? wave_height_not_available : static_cast<uint32_t>(std::round(*t / 0.1));
}

void binary_001_11::set_swell_period(std::optional<uint32_t> t)
{
	swell_period = !t ? wave_period_not_available : *t;
}

void binary_001_11::set_swell_direction(std::optional<uint32_t> t)
{
	swell_direction = !t ? wave_direction_not_available : *t;
}

void binary_001_11::set_sea_state(std::optional<uint32_t> t)
{
	sea_state = !t ? sea_state_not_available : *t;
}

void binary_001_11::set_water_temperature(std::optional<double> t)
{
	water_temperature = !t ? water_temperature_not_available
						   : static_cast<uint32_t>(std::round(*t / 0.1 + 10.0));
}

void binary_001_11::set_precipitation(std::optional<binary_001_11::precipitation> t)
{
	precipitation_type = !t ? precipitation::not_available : *t;
}

void binary_001_11::set_salinity(std::optional<double> t)
{
	sailinity = !t ? salinity_not_available : static_cast<uint32_t>(std::round(*t / 0.1));
}

void binary_001_11::set_ice(std::optional<binary_001_11::ice> t)
{
	ice_info = !t ? ice::not_available : *t;
}
}
}
