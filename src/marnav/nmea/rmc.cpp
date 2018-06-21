#include "rmc.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/nmea/convert.hpp>

namespace marnav
{
namespace nmea
{
constexpr sentence_id rmc::ID;
constexpr const char * rmc::TAG;

rmc::rmc()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

rmc::rmc(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	// before and after NMEA 2.3
	const auto size = std::distance(first, last);
	if ((size < 11) || (size > 12))
		throw std::invalid_argument{"invalid number of fields in rmc"};

	read(*(first + 0), time_utc_);
	read(*(first + 1), status_);
	read(*(first + 2), lat_);
	read(*(first + 3), lat_hem_);
	read(*(first + 4), lon_);
	read(*(first + 5), lon_hem_);
	read(*(first + 6), sog_);
	read(*(first + 7), heading_);
	read(*(first + 8), date_);
	read(*(first + 9), mag_);
	read(*(first + 10), mag_hem_);

	// NMEA 2.3 or newer
	if (size > 11)
		read(*(first + 11), mode_ind_);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	lat_ = correct_hemisphere(lat_, lat_hem_);
	lon_ = correct_hemisphere(lon_, lon_hem_);
}

utils::optional<geo::longitude> rmc::get_longitude() const
{
	return (lon_ && lon_hem_) ? lon_ : utils::optional<geo::longitude>{};
}

utils::optional<geo::latitude> rmc::get_latitude() const
{
	return (lat_ && lat_hem_) ? lat_ : utils::optional<geo::latitude>{};
}

void rmc::set_lat(const geo::latitude & t)
{
	lat_ = t;
	lat_hem_ = convert_hemisphere(t);
}

void rmc::set_lon(const geo::longitude & t)
{
	lon_ = t;
	lon_hem_ = convert_hemisphere(t);
}

void rmc::set_mag(double t, direction h)
{
	check_value(h, {direction::east, direction::west}, "mag var hemisphere");
	mag_ = t;
	mag_hem_ = h;
}

void rmc::append_data_to(std::string & s) const
{
	append(s, to_string(time_utc_));
	append(s, to_string(status_));
	append(s, to_string(lat_));
	append(s, to_string(lat_hem_));
	append(s, to_string(lon_));
	append(s, to_string(lon_hem_));
	append(s, to_string(sog_));
	append(s, to_string(heading_));
	append(s, to_string(date_));
	append(s, to_string(mag_));
	append(s, to_string(mag_hem_));
	append(s, to_string(mode_ind_));
}
}
}
