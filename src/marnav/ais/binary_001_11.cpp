#include <marnav/ais/binary_001_11.hpp>
#include <marnav/ais/angle.hpp>
#include <cmath>

namespace marnav::ais
{
void binary_001_11::read_from(const raw & payload)
{
	if (payload.size() != SIZE_BITS)
		throw std::invalid_argument{"wrong number of bits in playload of binary_001_11"};

	get(payload, lat_);
	get(payload, lon_);
	get(payload, day_);
	get(payload, hour_);
	get(payload, minute_);
	get(payload, wind_speed_avg_);
	get(payload, wind_gust_);
	get(payload, wind_direction_);
	get(payload, wind_gust_direction_);
	get(payload, temperature_);
	get(payload, humidity_);
	get(payload, dew_point_);
	get(payload, pressure_);
	get(payload, pressure_trend_);
	get(payload, visibility_);
	get(payload, water_level_);
	get(payload, water_level_trend_);
	get(payload, surface_current_speed_);
	get(payload, surface_current_direction_);
	get(payload, current_2_speed_);
	get(payload, current_2_direction_);
	get(payload, current_2_depth_);
	get(payload, current_3_speed_);
	get(payload, current_3_direction_);
	get(payload, current_3_depth_);
	get(payload, wave_height_);
	get(payload, wave_period_);
	get(payload, wave_direction_);
	get(payload, swell_height_);
	get(payload, swell_period_);
	get(payload, swell_direction_);
	get(payload, sea_state_);
	get(payload, water_temperature_);
	get(payload, precipitation_type_);
	get(payload, sailinity_);
	get(payload, ice_info_);
}

void binary_001_11::write_to(raw & payload) const
{
	payload = raw(SIZE_BITS);
	set(payload, lat_);
	set(payload, lon_);
	set(payload, day_);
	set(payload, hour_);
	set(payload, minute_);
	set(payload, wind_speed_avg_);
	set(payload, wind_gust_);
	set(payload, wind_direction_);
	set(payload, wind_gust_direction_);
	set(payload, temperature_);
	set(payload, humidity_);
	set(payload, dew_point_);
	set(payload, pressure_);
	set(payload, pressure_trend_);
	set(payload, visibility_);
	set(payload, water_level_);
	set(payload, water_level_trend_);
	set(payload, surface_current_speed_);
	set(payload, surface_current_direction_);
	set(payload, current_2_speed_);
	set(payload, current_2_direction_);
	set(payload, current_2_depth_);
	set(payload, current_3_speed_);
	set(payload, current_3_direction_);
	set(payload, current_3_depth_);
	set(payload, wave_height_);
	set(payload, wave_period_);
	set(payload, wave_direction_);
	set(payload, swell_height_);
	set(payload, swell_period_);
	set(payload, swell_direction_);
	set(payload, sea_state_);
	set(payload, water_temperature_);
	set(payload, precipitation_type_);
	set(payload, sailinity_);
	set(payload, ice_info_);
}

std::optional<geo::position> binary_001_11::get_position() const
{
	if ((lat_ == lat_not_available) || (lon_ == lon_not_available))
		return {};
	return {{to_geo_latitude(lat_, lat_.count, angle_scale::I3),
		to_geo_longitude(lon_, lon_.count, angle_scale::I3)}};
}

std::optional<uint32_t> binary_001_11::get_day() const
{
	if (day_ == day_not_available)
		return {};
	return {day_};
}

std::optional<uint32_t> binary_001_11::get_hour() const
{
	if (hour_ == hour_not_available)
		return {};
	return {hour_};
}

std::optional<uint32_t> binary_001_11::get_minute() const
{
	if (minute_ == minute_not_available)
		return {};
	return {minute_};
}

std::optional<uint32_t> binary_001_11::get_wind_speed_avg() const
{
	if (wind_speed_avg_ == wind_speed_avg_not_available)
		return {};
	return {wind_speed_avg_};
}

std::optional<uint32_t> binary_001_11::get_wind_gust() const
{
	if (wind_gust_ == wind_gust_not_available)
		return {};
	return {wind_gust_};
}

std::optional<uint32_t> binary_001_11::get_wind_direction() const
{
	if (wind_direction_ == wind_direction_not_available)
		return {};
	return {wind_direction_};
}

std::optional<uint32_t> binary_001_11::get_wind_gust_direction() const
{
	if (wind_gust_direction_ == wind_gust_direction_not_available)
		return {};
	return {wind_gust_direction_};
}

/// Returns the temperature in degrees Celsius between `-60.0` and `+60.0`.
std::optional<double> binary_001_11::get_temperature() const
{
	if (temperature_ == temperature_not_available)
		return {};
	return -60.0 + 0.1 * temperature_;
}

std::optional<uint32_t> binary_001_11::get_humidity() const
{
	if (humidity_ == humidity_not_available)
		return {};
	return {humidity_};
}

/// Returns in degrees Celsius between `-20.0` and `+50.0`.
std::optional<double> binary_001_11::get_dew_point() const
{
	if (dew_point_ == dew_point_not_available)
		return {};
	return -20.0 + 0.1 * dew_point_;
}

/// Returns the pressure in `hPa` between `800` and `1200`.
std::optional<uint32_t> binary_001_11::get_pressure() const
{
	if (pressure_ == pressure_not_available)
		return {};
	return {800 + pressure_};
}

std::optional<binary_001_11::trend> binary_001_11::get_pressure_trend() const
{
	if (pressure_trend_ == trend::not_available)
		return {};
	return {pressure_trend_};
}

/// Returns the visibility in nautical miles.
std::optional<double> binary_001_11::get_visibility() const
{
	if (visibility_ == visibility_not_available)
		return {};
	return 0.1 * visibility_;
}

/// Returns the water level in meters between `-10.0` and `+30.0`.
std::optional<double> binary_001_11::get_water_level() const
{
	if (water_level_ == water_level_not_available)
		return {};
	return -10.0 + 0.1 * water_level_;
}

std::optional<binary_001_11::trend> binary_001_11::get_water_level_trend() const
{
	if (water_level_trend_ == trend::not_available)
		return {};
	return {water_level_trend_};
}

/// Returns the speed in knots.
std::optional<double> binary_001_11::get_surface_current_speed() const
{
	if (surface_current_speed_ == current_speed_not_available)
		return {};
	return 0.1 * surface_current_speed_;
}

std::optional<uint32_t> binary_001_11::get_surface_current_direction() const
{
	if (surface_current_direction_ == current_direction_not_available)
		return {};
	return {surface_current_direction_};
}

/// Returns the speed in knots.
std::optional<double> binary_001_11::get_current_2_speed() const
{
	if (current_2_speed_ == current_speed_not_available)
		return {};
	return 0.1 * current_2_speed_;
}

std::optional<uint32_t> binary_001_11::get_current_2_direction() const
{
	if (current_2_direction_ == current_direction_not_available)
		return {};
	return {current_2_direction_};
}

std::optional<uint32_t> binary_001_11::get_current_2_depth() const
{
	if (current_2_depth_ == current_depth_not_available)
		return {};
	return {current_2_depth_};
}

/// Returns the speed in knots.
std::optional<double> binary_001_11::get_current_3_speed() const
{
	if (current_3_speed_ == current_speed_not_available)
		return {};
	return 0.1 * current_3_speed_;
}

std::optional<uint32_t> binary_001_11::get_current_3_direction() const
{
	if (current_3_direction_ == current_direction_not_available)
		return {};
	return {current_3_direction_};
}

std::optional<uint32_t> binary_001_11::get_current_3_depth() const
{
	if (current_3_depth_ == current_depth_not_available)
		return {};
	return {current_3_depth_};
}

/// Returns the wave height in meters.
std::optional<double> binary_001_11::get_wave_height() const
{
	if (wave_height_ == wave_height_not_available)
		return {};
	return 0.1 * wave_height_;
}

std::optional<uint32_t> binary_001_11::get_wave_period() const
{
	if (wave_period_ == wave_period_not_available)
		return {};
	return {wave_period_};
}

std::optional<uint32_t> binary_001_11::get_wave_direction() const
{
	if (wave_direction_ == wave_direction_not_available)
		return {};
	return {wave_direction_};
}

/// Returns the swell height in meters.
std::optional<double> binary_001_11::get_swell_height() const
{
	if (swell_height_ == wave_height_not_available)
		return {};
	return 0.1 * swell_height_;
}

std::optional<uint32_t> binary_001_11::get_swell_period() const
{
	if (swell_period_ == wave_period_not_available)
		return {};
	return {swell_period_};
}

std::optional<uint32_t> binary_001_11::get_swell_direction() const
{
	if (swell_direction_ == wave_direction_not_available)
		return {};
	return {swell_direction_};
}

std::optional<uint32_t> binary_001_11::get_sea_state() const
{
	if (sea_state_ == sea_state_not_available)
		return {};
	return {sea_state_};
}

/// Returns the water temperature in degrees Celsius between `-10.0` and `+50.0`.
std::optional<double> binary_001_11::get_water_temperature() const
{
	if (water_temperature_ == water_temperature_not_available)
		return {};
	return -10.0 + 0.1 * water_temperature_;
}

std::optional<binary_001_11::precipitation> binary_001_11::get_precipitation() const
{
	if (precipitation_type_ == precipitation::not_available)
		return {};
	return {precipitation_type_};
}

/// Returns the sailinity in percent.
std::optional<double> binary_001_11::get_salinity() const
{
	if (sailinity_ == salinity_not_available)
		return {};
	return 0.1 * sailinity_;
}

std::optional<binary_001_11::ice> binary_001_11::get_ice() const
{
	if (ice_info_ == ice::not_available)
		return {};
	return {ice_info_};
}

void binary_001_11::set_position(std::optional<geo::position> t)
{
	if (!t) {
		lat_ = lat_not_available;
		lon_ = lon_not_available;
	} else {
		lat_ = to_latitude_minutes(t->lat(), lat_.count, angle_scale::I3);
		lon_ = to_longitude_minutes(t->lon(), lon_.count, angle_scale::I3);
	}
}

/// Sets the day. Value must be either empty optional or a value between `1` and `31`.
/// A value out of range is treated the same as an empty optional.
void binary_001_11::set_day(std::optional<uint32_t> t)
{
	day_ = (!t || *t >= 31) ? day_not_available : *t;
}

/// Sets the hour. Value must be either empty optional or a value between `0` and `23`.
/// A value out of range is treated the same as an empty optional.
void binary_001_11::set_hour(std::optional<uint32_t> t)
{
	hour_ = (!t || *t >= 24) ? hour_not_available : *t;
}

/// Sets the minute. Value must be either empty optional or a value between `0` and `59`.
/// A value out of range is treated the same as an empty optional.
void binary_001_11::set_minute(std::optional<uint32_t> t)
{
	minute_ = (!t || *t > 59u) ? minute_not_available : *t;
}

void binary_001_11::set_wind_speed_avg(std::optional<uint32_t> t)
{
	wind_speed_avg_ = !t ? wind_speed_avg_not_available : *t;
}

void binary_001_11::set_wind_gust(std::optional<uint32_t> t)
{
	wind_gust_ = !t ? wind_gust_not_available : *t;
}

void binary_001_11::set_wind_direction(std::optional<uint32_t> t)
{
	wind_direction_ = !t ? wind_direction_not_available : *t;
}

void binary_001_11::set_wind_gust_direction(std::optional<uint32_t> t)
{
	wind_gust_direction_ = !t ? wind_gust_direction_not_available : *t;
}

void binary_001_11::set_temperature(std::optional<double> t)
{
	temperature_
		= !t ? temperature_not_available : static_cast<uint32_t>(std::round(*t / 0.1 + 60.0));
}

void binary_001_11::set_humidity(std::optional<uint32_t> t)
{
	humidity_ = !t ? humidity_not_available : *t;
}

void binary_001_11::set_dew_point(std::optional<double> t)
{
	dew_point_
		= !t ? dew_point_not_available : static_cast<uint32_t>(std::round(*t / 0.1 + 20.0));
}

void binary_001_11::set_pressure(std::optional<uint32_t> t)
{
	pressure_ = !t ? pressure_not_available : *t - 800;
}

void binary_001_11::set_pressure_trend(std::optional<binary_001_11::trend> t)
{
	pressure_trend_ = !t ? trend::not_available : *t;
}

void binary_001_11::set_visibility(std::optional<double> t)
{
	visibility_ = !t ? visibility_not_available : static_cast<uint32_t>(std::round(*t / 0.1));
}

void binary_001_11::set_water_level(std::optional<double> t)
{
	water_level_
		= !t ? water_level_not_available : static_cast<uint32_t>(std::round(*t / 0.1 + 10.0));
}

void binary_001_11::set_water_level_trend(std::optional<binary_001_11::trend> t)
{
	water_level_trend_ = !t ? trend::not_available : *t;
}

void binary_001_11::set_surface_current_speed(std::optional<double> t)
{
	surface_current_speed_
		= !t ? current_speed_not_available : static_cast<uint32_t>(std::round(*t / 0.1));
}

void binary_001_11::set_surface_current_direction(std::optional<uint32_t> t)
{
	surface_current_direction_ = !t ? current_direction_not_available : *t;
}

void binary_001_11::set_current_2_speed(std::optional<double> t)
{
	current_2_speed_
		= !t ? current_speed_not_available : static_cast<uint32_t>(std::round(*t / 0.1));
}

void binary_001_11::set_current_2_direction(std::optional<uint32_t> t)
{
	current_2_direction_ = !t ? current_direction_not_available : *t;
}

void binary_001_11::set_current_2_depth(std::optional<uint32_t> t)
{
	current_2_depth_ = !t ? current_depth_not_available : *t;
}

void binary_001_11::set_current_3_speed(std::optional<double> t)
{
	current_3_speed_
		= !t ? current_speed_not_available : static_cast<uint32_t>(std::round(*t / 0.1));
}

void binary_001_11::set_current_3_direction(std::optional<uint32_t> t)
{
	current_3_direction_ = !t ? current_direction_not_available : *t;
}

void binary_001_11::set_current_3_depth(std::optional<uint32_t> t)
{
	current_3_depth_ = !t ? current_depth_not_available : *t;
}

void binary_001_11::set_wave_height(std::optional<double> t)
{
	wave_height_ = !t ? wave_height_not_available : static_cast<uint32_t>(std::round(*t / 0.1));
}

void binary_001_11::set_wave_period(std::optional<uint32_t> t)
{
	wave_period_ = !t ? wave_period_not_available : *t;
}

void binary_001_11::set_wave_direction(std::optional<uint32_t> t)
{
	wave_direction_ = !t ? wave_direction_not_available : *t;
}

void binary_001_11::set_swell_height(std::optional<double> t)
{
	swell_height_
		= !t ? wave_height_not_available : static_cast<uint32_t>(std::round(*t / 0.1));
}

void binary_001_11::set_swell_period(std::optional<uint32_t> t)
{
	swell_period_ = !t ? wave_period_not_available : *t;
}

void binary_001_11::set_swell_direction(std::optional<uint32_t> t)
{
	swell_direction_ = !t ? wave_direction_not_available : *t;
}

void binary_001_11::set_sea_state(std::optional<uint32_t> t)
{
	sea_state_ = !t ? sea_state_not_available : *t;
}

void binary_001_11::set_water_temperature(std::optional<double> t)
{
	water_temperature_ = !t ? water_temperature_not_available
							: static_cast<uint32_t>(std::round(*t / 0.1 + 10.0));
}

void binary_001_11::set_precipitation(std::optional<binary_001_11::precipitation> t)
{
	precipitation_type_ = !t ? precipitation::not_available : *t;
}

void binary_001_11::set_salinity(std::optional<double> t)
{
	sailinity_ = !t ? salinity_not_available : static_cast<uint32_t>(std::round(*t / 0.1));
}

void binary_001_11::set_ice(std::optional<binary_001_11::ice> t)
{
	ice_info_ = !t ? ice::not_available : *t;
}
}
