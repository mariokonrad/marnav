#include "binary_001_11.hpp"
#include <cmath>
#include <marnav/ais/angle.hpp>

namespace marnav
{
namespace ais
{
void binary_001_11::read_from(const raw & payload)
{
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
	payload = raw{binary_001_11::SIZE_BITS};
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

utils::optional<geo::position> binary_001_11::get_position() const
{
	if ((lat == lat_not_available) || (lon == lon_not_available))
		return {};
	return {{to_geo_latitude(lat, lat.count, angle_scale::I3),
		to_geo_longitude(lon, lon.count, angle_scale::I3)}};
}

utils::optional<uint32_t> binary_001_11::get_day() const
{
	if (day == day_not_available)
		return {};
	return {day};
}

utils::optional<uint32_t> binary_001_11::get_hour() const
{
	if (hour == hour_not_available)
		return {};
	return {hour};
}

utils::optional<uint32_t> binary_001_11::get_minute() const
{
	if (minute == minute_not_available)
		return {};
	return {minute};
}

utils::optional<uint32_t> binary_001_11::get_wind_speed_avg() const
{
	if (wind_speed_avg == wind_speed_avg_not_available)
		return {};
	return {wind_speed_avg};
}

utils::optional<uint32_t> binary_001_11::get_wind_gust() const
{
	if (wind_gust == wind_gust_not_available)
		return {};
	return {wind_gust};
}

utils::optional<uint32_t> binary_001_11::get_wind_direction() const
{
	if (wind_direction == wind_direction_not_available)
		return {};
	return {wind_direction};
}

utils::optional<uint32_t> binary_001_11::get_wind_gust_direction() const
{
	if (wind_gust_direction == wind_gust_direction_not_available)
		return {};
	return {wind_gust_direction};
}

utils::optional<double> binary_001_11::get_temperature() const
{
	if (temperature == temperature_not_available)
		return {};
	return -60.0 + 0.1 * temperature;
}

utils::optional<uint32_t> binary_001_11::get_humidity() const
{
	if (humidity == humidity_not_available)
		return {};
	return {humidity};
}

utils::optional<double> binary_001_11::get_dew_point() const
{
	if (dew_point == dew_point_not_available)
		return {};
	return -20.0 + 0.1 * dew_point;
}

utils::optional<uint32_t> binary_001_11::get_pressure() const
{
	if (pressure == pressure_not_available)
		return {};
	return {800 + pressure};
}

utils::optional<binary_001_11::trend> binary_001_11::get_pressure_trend() const
{
	if (pressure_trend == trend::not_available)
		return {};
	return {pressure_trend};
}

utils::optional<double> binary_001_11::get_visibility() const
{
	if (visibility == visibility_not_available)
		return {};
	return 0.1 * visibility;
}

utils::optional<double> binary_001_11::get_water_level() const
{
	if (water_level == water_level_not_available)
		return {};
	return -10.0 + 0.1 * water_level;
}

utils::optional<binary_001_11::trend> binary_001_11::get_water_level_trend() const
{
	if (water_level_trend == trend::not_available)
		return {};
	return {water_level_trend};
}

utils::optional<double> binary_001_11::get_surface_current_speed() const
{
	if (surface_current_speed == current_speed_not_available)
		return {};
	return 0.1 * surface_current_speed;
}

utils::optional<uint32_t> binary_001_11::get_surface_current_direction() const
{
	if (surface_current_direction == current_direction_not_available)
		return {};
	return {surface_current_direction};
}

utils::optional<double> binary_001_11::get_current_2_speed() const
{
	if (current_2_speed == current_speed_not_available)
		return {};
	return 0.1 * current_2_speed;
}

utils::optional<uint32_t> binary_001_11::get_current_2_direction() const
{
	if (current_2_direction == current_direction_not_available)
		return {};
	return {current_2_direction};
}

utils::optional<uint32_t> binary_001_11::get_current_2_depth() const
{
	if (current_2_depth == current_depth_not_available)
		return {};
	return {current_2_depth};
}

utils::optional<double> binary_001_11::get_current_3_speed() const
{
	if (current_3_speed == current_speed_not_available)
		return {};
	return 0.1 * current_3_speed;
}

utils::optional<uint32_t> binary_001_11::get_current_3_direction() const
{
	if (current_3_direction == current_direction_not_available)
		return {};
	return {current_3_direction};
}

utils::optional<uint32_t> binary_001_11::get_current_3_depth() const
{
	if (current_3_depth == current_depth_not_available)
		return {};
	return {current_3_depth};
}

utils::optional<double> binary_001_11::get_wave_height() const
{
	if (wave_height == wave_height_not_available)
		return {};
	return 0.1 * wave_height;
}

utils::optional<uint32_t> binary_001_11::get_wave_period() const
{
	if (wave_period == wave_period_not_available)
		return {};
	return {wave_period};
}

utils::optional<uint32_t> binary_001_11::get_wave_direction() const
{
	if (wave_direction == wave_direction_not_available)
		return {};
	return {wave_direction};
}

utils::optional<double> binary_001_11::get_swell_height() const
{
	if (swell_height == wave_height_not_available)
		return {};
	return 0.1 * swell_height;
}

utils::optional<uint32_t> binary_001_11::get_swell_period() const
{
	if (swell_period == wave_period_not_available)
		return {};
	return {swell_period};
}

utils::optional<uint32_t> binary_001_11::get_swell_direction() const
{
	if (swell_direction == wave_direction_not_available)
		return {};
	return {swell_direction};
}

utils::optional<uint32_t> binary_001_11::get_sea_state() const
{
	if (sea_state == sea_state_not_available)
		return {};
	return {sea_state};
}

utils::optional<double> binary_001_11::get_water_temperature() const
{
	if (water_temperature == water_temperature_not_available)
		return {};
	return -10.0 + 0.1 * water_temperature;
}

utils::optional<binary_001_11::precipitation> binary_001_11::get_precipitation() const
{
	if (precipitation_type == precipitation::not_available)
		return {};
	return {precipitation_type};
}

utils::optional<double> binary_001_11::get_salinity() const
{
	if (sailinity == salinity_not_available)
		return {};
	return 0.1 * sailinity;
}

utils::optional<binary_001_11::ice> binary_001_11::get_ice() const
{
	if (ice_info == ice::not_available)
		return {};
	return {ice_info};
}

void binary_001_11::set_position(utils::optional<geo::position> t)
{
	if (!t) {
		lat = lat_not_available;
		lon = lon_not_available;
	} else {
		lat = to_latitude_minutes(t->lat(), lat.count, angle_scale::I3);
		lon = to_longitude_minutes(t->lon(), lon.count, angle_scale::I3);
	}
}

void binary_001_11::set_day(utils::optional<uint32_t> t)
{
	day = !t ? day_not_available : *t;
}

void binary_001_11::set_hour(utils::optional<uint32_t> t)
{
	hour = !t ? hour_not_available : *t;
}

void binary_001_11::set_minute(utils::optional<uint32_t> t)
{
	minute = !t ? minute_not_available : *t;
}

void binary_001_11::set_wind_speed_avg(utils::optional<uint32_t> t)
{
	wind_speed_avg = !t ? wind_speed_avg_not_available : *t;
}

void binary_001_11::set_wind_gust(utils::optional<uint32_t> t)
{
	wind_gust = !t ? wind_gust_not_available : *t;
}

void binary_001_11::set_wind_direction(utils::optional<uint32_t> t)
{
	wind_direction = !t ? wind_direction_not_available : *t;
}

void binary_001_11::set_wind_gust_direction(utils::optional<uint32_t> t)
{
	wind_gust_direction = !t ? wind_gust_direction_not_available : *t;
}

void binary_001_11::set_temperature(utils::optional<double> t)
{
	temperature
		= !t ? temperature_not_available : static_cast<uint32_t>(std::round(*t / 0.1 + 60.0));
}

void binary_001_11::set_humidity(utils::optional<uint32_t> t)
{
	humidity = !t ? humidity_not_available : *t;
}

void binary_001_11::set_dew_point(utils::optional<double> t)
{
	dew_point
		= !t ? dew_point_not_available : static_cast<uint32_t>(std::round(*t / 0.1 + 20.0));
}

void binary_001_11::set_pressure(utils::optional<uint32_t> t)
{
	pressure = !t ? pressure_not_available : *t - 800;
}

void binary_001_11::set_pressure_trend(utils::optional<binary_001_11::trend> t)
{
	pressure_trend = !t ? trend::not_available : *t;
}

void binary_001_11::set_visibility(utils::optional<double> t)
{
	visibility = !t ? visibility_not_available : static_cast<uint32_t>(std::round(*t / 0.1));
}

void binary_001_11::set_water_level(utils::optional<double> t)
{
	water_level
		= !t ? water_level_not_available : static_cast<uint32_t>(std::round(*t / 0.1 + 10.0));
}

void binary_001_11::set_water_level_trend(utils::optional<binary_001_11::trend> t)
{
	water_level_trend = !t ? trend::not_available : *t;
}

void binary_001_11::set_surface_current_speed(utils::optional<double> t)
{
	surface_current_speed
		= !t ? current_speed_not_available : static_cast<uint32_t>(std::round(*t / 0.1));
}

void binary_001_11::set_surface_current_direction(utils::optional<uint32_t> t)
{
	surface_current_direction = !t ? current_direction_not_available : *t;
}

void binary_001_11::set_current_2_speed(utils::optional<double> t)
{
	current_2_speed
		= !t ? current_speed_not_available : static_cast<uint32_t>(std::round(*t / 0.1));
}

void binary_001_11::set_current_2_direction(utils::optional<uint32_t> t)
{
	current_2_direction = !t ? current_direction_not_available : *t;
}

void binary_001_11::set_current_2_depth(utils::optional<uint32_t> t)
{
	current_2_depth = !t ? current_depth_not_available : *t;
}

void binary_001_11::set_current_3_speed(utils::optional<double> t)
{
	current_3_speed
		= !t ? current_speed_not_available : static_cast<uint32_t>(std::round(*t / 0.1));
}

void binary_001_11::set_current_3_direction(utils::optional<uint32_t> t)
{
	current_3_direction = !t ? current_direction_not_available : *t;
}

void binary_001_11::set_current_3_depth(utils::optional<uint32_t> t)
{
	current_3_depth = !t ? current_depth_not_available : *t;
}

void binary_001_11::set_wave_height(utils::optional<double> t)
{
	wave_height = !t ? wave_height_not_available : static_cast<uint32_t>(std::round(*t / 0.1));
}

void binary_001_11::set_wave_period(utils::optional<uint32_t> t)
{
	wave_period = !t ? wave_period_not_available : *t;
}

void binary_001_11::set_wave_direction(utils::optional<uint32_t> t)
{
	wave_direction = !t ? wave_direction_not_available : *t;
}

void binary_001_11::set_swell_height(utils::optional<double> t)
{
	swell_height = !t ? wave_height_not_available : static_cast<uint32_t>(std::round(*t / 0.1));
}

void binary_001_11::set_swell_period(utils::optional<uint32_t> t)
{
	swell_period = !t ? wave_period_not_available : *t;
}

void binary_001_11::set_swell_direction(utils::optional<uint32_t> t)
{
	swell_direction = !t ? wave_direction_not_available : *t;
}

void binary_001_11::set_sea_state(utils::optional<uint32_t> t)
{
	sea_state = !t ? sea_state_not_available : *t;
}

void binary_001_11::set_water_temperature(utils::optional<double> t)
{
	water_temperature = !t ? water_temperature_not_available
						   : static_cast<uint32_t>(std::round(*t / 0.1 + 10.0));
}

void binary_001_11::set_precipitation(utils::optional<binary_001_11::precipitation> t)
{
	precipitation_type = !t ? precipitation::not_available : *t;
}

void binary_001_11::set_salinity(utils::optional<double> t)
{
	sailinity = !t ? salinity_not_available : static_cast<uint32_t>(std::round(*t / 0.1));
}

void binary_001_11::set_ice(utils::optional<binary_001_11::ice> t)
{
	ice_info = !t ? ice::not_available : *t;
}
}
}
