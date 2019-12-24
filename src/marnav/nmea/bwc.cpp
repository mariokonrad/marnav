#include <marnav/nmea/bwc.hpp>
#include "convert.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr sentence_id bwc::ID;
constexpr const char * bwc::TAG;

bwc::bwc()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

bwc::bwc(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	const auto size = std::distance(first, last);
	if ((size != 12) && (size != 13))
		throw std::invalid_argument{"invalid number of fields in bwc"};

	read(*(first + 0), time_utc_);
	read(*(first + 1), lat_);
	read(*(first + 2), lat_hem_);
	read(*(first + 3), lon_);
	read(*(first + 4), lon_hem_);
	read(*(first + 5), bearing_true_);
	read(*(first + 6), bearing_true_ref_);
	read(*(first + 7), bearing_mag_);
	read(*(first + 8), bearing_mag_ref_);
	read(*(first + 9), distance_);
	read(*(first + 10), distance_unit_);
	read(*(first + 11), waypoint_id_);

	if (size == 13)
		read(*(first + 12), mode_ind_);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	lat_ = correct_hemisphere(lat_, lat_hem_);
	lon_ = correct_hemisphere(lon_, lon_hem_);
}

utils::optional<geo::longitude> bwc::get_lon() const
{
	return (lon_ && lon_hem_) ? lon_ : utils::optional<geo::longitude>{};
}

utils::optional<geo::latitude> bwc::get_lat() const
{
	return (lat_ && lat_hem_) ? lat_ : utils::optional<geo::latitude>{};
}

void bwc::set_lat(const geo::latitude & t)
{
	lat_ = t;
	lat_hem_ = convert_hemisphere(t);
}

void bwc::set_lon(const geo::longitude & t)
{
	lon_ = t;
	lon_hem_ = convert_hemisphere(t);
}

void bwc::set_bearing_true(double t) noexcept
{
	bearing_true_ = t;
	bearing_true_ref_ = reference::TRUE;
}

void bwc::set_bearing_mag(double t) noexcept
{
	bearing_mag_ = t;
	bearing_mag_ref_ = reference::MAGNETIC;
}

void bwc::set_distance(double t) noexcept
{
	distance_ = t;
	distance_unit_ = unit::distance::nm;
}

void bwc::append_data_to(std::string & s) const
{
	append(s, to_string(time_utc_));
	append(s, to_string(lat_));
	append(s, to_string(lat_hem_));
	append(s, to_string(lon_));
	append(s, to_string(lon_hem_));
	append(s, to_string(bearing_true_));
	append(s, to_string(bearing_true_ref_));
	append(s, to_string(bearing_mag_));
	append(s, to_string(bearing_mag_ref_));
	append(s, to_string(distance_));
	append(s, to_string(distance_unit_));
	append(s, to_string(waypoint_id_));
	append(s, to_string(mode_ind_));
}
}
}
