#include <marnav/nmea/gga.hpp>
#include "checks.hpp"
#include "convert.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav::nmea
{
constexpr sentence_id gga::ID;
constexpr const char * gga::TAG;

gga::gga()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

gga::gga(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 14)
		throw std::invalid_argument{"invalid number of fields in gga"};

	std::optional<unit::distance> altitude_unit;
	std::optional<unit::distance> geodial_separation_unit;

	read(*(first + 0), time_);
	read(*(first + 1), lat_);
	read(*(first + 2), lat_hem_);
	read(*(first + 3), lon_);
	read(*(first + 4), lon_hem_);
	read(*(first + 5), quality_indicator_);
	read(*(first + 6), n_satellites_);
	read(*(first + 7), hor_dilution_);
	read(*(first + 8), altitude_);
	read(*(first + 9), altitude_unit);
	read(*(first + 10), geodial_separation_);
	read(*(first + 11), geodial_separation_unit);
	read(*(first + 12), dgps_age_);
	read(*(first + 13), dgps_ref_);

	check_value(altitude_unit, {unit::distance::meter}, "altitude unit");
	check_value(geodial_separation_unit, {unit::distance::meter}, "geodial separation unit");

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	lat_ = correct_hemisphere(lat_, lat_hem_);
	lon_ = correct_hemisphere(lon_, lon_hem_);
}

std::optional<geo::longitude> gga::get_lon() const
{
	return (lon_ && lon_hem_) ? lon_ : std::optional<geo::longitude>{};
}

std::optional<geo::latitude> gga::get_lat() const
{
	return (lat_ && lat_hem_) ? lat_ : std::optional<geo::latitude>{};
}

void gga::set_lat(const geo::latitude & t)
{
	lat_ = t;
	lat_hem_ = convert_hemisphere(t);
}

void gga::set_lon(const geo::longitude & t)
{
	lon_ = t;
	lon_hem_ = convert_hemisphere(t);
}

std::optional<units::length> gga::get_altitude() const
{
	if (!altitude_)
		return {};
	return {*altitude_};
}

std::optional<units::length> gga::get_geodial_separation() const
{
	if (!geodial_separation_)
		return {};
	return {*geodial_separation_};
}

void gga::append_data_to(std::string & s, const version &) const
{
	append(s, to_string(time_));
	append(s, to_string(lat_));
	append(s, to_string(lat_hem_));
	append(s, to_string(lon_));
	append(s, to_string(lon_hem_));
	append(s, to_string(quality_indicator_));
	append(s, to_string(n_satellites_));
	append(s, to_string(hor_dilution_));
	append(s, to_string(altitude_));
	append(s, to_string_if(unit::distance::meter, altitude_));
	append(s, to_string(geodial_separation_));
	append(s, to_string_if(unit::distance::meter, geodial_separation_));
	append(s, to_string(dgps_age_));
	append(s, to_string(dgps_ref_));
}
}
