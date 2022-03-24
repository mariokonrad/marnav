#include <marnav/nmea/bwr.hpp>
#include "convert.hpp"
#include "checks.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr sentence_id bwr::ID;
constexpr const char * bwr::TAG;

bwr::bwr()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

bwr::bwr(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	const auto n = std::distance(first, last);
	if ((n < 12) || (n > 13))
		throw std::invalid_argument{"invalid number of fields in bwr"};

	std::optional<reference> bearing_true_ref;
	std::optional<reference> bearing_magn_ref;
	std::optional<unit::distance> distance_unit;

	read(*(first + 0), time_utc_);
	read(*(first + 1), lat_);
	read(*(first + 2), lat_hem_);
	read(*(first + 3), lon_);
	read(*(first + 4), lon_hem_);
	read(*(first + 5), bearing_true_);
	read(*(first + 6), bearing_true_ref);
	read(*(first + 7), bearing_mag_);
	read(*(first + 8), bearing_magn_ref);
	read(*(first + 9), distance_);
	read(*(first + 10), distance_unit);
	read(*(first + 11), waypoint_id_);

	if (n > 12)
		read(*(first + 12), mode_ind_);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	lat_ = correct_hemisphere(lat_, lat_hem_);
	lon_ = correct_hemisphere(lon_, lon_hem_);

	check_value(bearing_true_ref, {reference::TRUE}, "bearing true ref");
	check_value(bearing_magn_ref, {reference::MAGNETIC}, "bearing magnetic ref");
	check_value(distance_unit, {unit::distance::nm}, "distance unit");
}

std::optional<geo::longitude> bwr::get_lon() const
{
	return (lon_ && lon_hem_) ? lon_ : std::optional<geo::longitude>{};
}

std::optional<geo::latitude> bwr::get_lat() const
{
	return (lat_ && lat_hem_) ? lat_ : std::optional<geo::latitude>{};
}

void bwr::set_lat(const geo::latitude & t)
{
	lat_ = t;
	lat_hem_ = convert_hemisphere(t);
}

void bwr::set_lon(const geo::longitude & t)
{
	lon_ = t;
	lon_hem_ = convert_hemisphere(t);
}

void bwr::set_bearing_true(double t) noexcept
{
	bearing_true_ = t;
}

void bwr::set_bearing_mag(double t) noexcept
{
	bearing_mag_ = t;
}

void bwr::set_distance(units::length t)
{
	if (t.value() < 0.0)
		throw std::invalid_argument{"distance less than zero"};
	distance_ = t.get<units::nautical_miles>();
}

std::optional<units::length> bwr::get_distance() const
{
	if (!distance_)
		return {};
	return {*distance_};
}

void bwr::append_data_to(std::string & s, const version &) const
{
	append(s, to_string(time_utc_));
	append(s, to_string(lat_));
	append(s, to_string(lat_hem_));
	append(s, to_string(lon_));
	append(s, to_string(lon_hem_));
	append(s, to_string(bearing_true_));
	append(s, to_string_if(reference::TRUE, bearing_true_));
	append(s, to_string(bearing_mag_));
	append(s, to_string_if(reference::MAGNETIC, bearing_mag_));
	append(s, to_string(distance_));
	append(s, to_string_if(unit::distance::nm, distance_));
	append(s, to_string(waypoint_id_));
	append(s, to_string(mode_ind_));
}
}
}
