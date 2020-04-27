#include <marnav/nmea/bec.hpp>
#include "checks.hpp"
#include "convert.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr sentence_id bec::ID;
constexpr const char * bec::TAG;

bec::bec()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

bec::bec(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 12)
		throw std::invalid_argument{"invalid number of fields in bec"};

	reference bearing_true_ref;
	reference bearing_magn_ref;
	unit::distance distance_unit;

	read(*(first + 0), time_utc_);
	read(*(first + 1), lat_);
	read(*(first + 2), lat_hem_);
	read(*(first + 3), lon_);
	read(*(first + 4), lon_hem_);
	read(*(first + 5), bearing_true_);
	read(*(first + 6), bearing_true_ref);
	read(*(first + 7), bearing_magn_);
	read(*(first + 8), bearing_magn_ref);
	read(*(first + 9), distance_);
	read(*(first + 10), distance_unit);
	read(*(first + 11), waypoint_id_);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	lat_ = correct_hemisphere(lat_, lat_hem_);
	lon_ = correct_hemisphere(lon_, lon_hem_);

	check_value(bearing_true_ref, {reference::TRUE}, "bearing_true_ref");
	check_value(bearing_magn_ref, {reference::MAGNETIC}, "bearing_magn_ref");
	check_value(distance_unit, {unit::distance::nm}, "distance_unit");
}

geo::latitude bec::get_lat() const
{
	return lat_;
}

geo::longitude bec::get_lon() const
{
	return lon_;
}

void bec::set_time_utc(const nmea::time & t)
{
	time_utc_ = t;
}

void bec::set_lat(const geo::latitude & t)
{
	lat_ = t;
	lat_hem_ = convert_hemisphere(t);
}

void bec::set_lon(const geo::longitude & t)
{
	lon_ = t;
	lon_hem_ = convert_hemisphere(t);
}

void bec::set_bearing_true(double t)
{
	bearing_true_ = t;
}

void bec::set_bearing_magn(double t)
{
	bearing_magn_ = t;
}

void bec::set_distance(units::length t)
{
	if (t.value() < 0.0)
		throw std::invalid_argument{"distance less than zero"};
	distance_ = t.get<units::nautical_miles>();
}

void bec::append_data_to(std::string & s) const
{
	append(s, to_string(time_utc_));
	append(s, to_string(lat_));
	append(s, to_string(lat_hem_));
	append(s, to_string(lon_));
	append(s, to_string(lon_hem_));
	append(s, to_string(bearing_true_));
	append(s, to_string(reference::TRUE));
	append(s, to_string(bearing_magn_));
	append(s, to_string(reference::MAGNETIC));
	append(s, to_string(distance_));
	append(s, to_string(unit::distance::nm));
	append(s, to_string(waypoint_id_));
}
}
}
