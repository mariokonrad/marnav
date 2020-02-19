#include <marnav/nmea/gns.hpp>
#include "convert.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr sentence_id gns::ID;
constexpr const char * gns::TAG;

gns::gns()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

gns::gns(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 12)
		throw std::invalid_argument{"invalid number of fields in gns"};

	read(*(first + 0), time_utc_);
	read(*(first + 1), lat_);
	read(*(first + 2), lat_hem_);
	read(*(first + 3), lon_);
	read(*(first + 4), lon_hem_);
	read(*(first + 5), mode_ind_);
	read(*(first + 6), number_of_satellites_);
	read(*(first + 7), hdrop_);
	read(*(first + 8), antenna_altitude_);
	read(*(first + 9), geodial_separation_);
	read(*(first + 10), age_of_differential_data_);
	read(*(first + 11), differential_ref_station_id_);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	lat_ = correct_hemisphere(lat_, lat_hem_);
	lon_ = correct_hemisphere(lon_, lon_hem_);
}

utils::optional<geo::longitude> gns::get_lon() const
{
	return (lon_ && lon_hem_) ? lon_ : utils::optional<geo::longitude>{};
}

utils::optional<geo::latitude> gns::get_lat() const
{
	return (lat_ && lat_hem_) ? lat_ : utils::optional<geo::latitude>{};
}

void gns::set_lat(const geo::latitude & t)
{
	lat_ = t;
	lat_hem_ = convert_hemisphere(t);
}

void gns::set_lon(const geo::longitude & t)
{
	lon_ = t;
	lon_hem_ = convert_hemisphere(t);
}

void gns::set_mode_indicator(const std::string & t)
{
	if ((t.size() < 2) || (t.size() > 8))
		throw std::invalid_argument{"invalid mode indicator"};
	mode_ind_ = t;
}

utils::optional<units::length> gns::get_antenna_altitude() const
{
	if (!antenna_altitude_)
		return {};
	return {*antenna_altitude_};
}

utils::optional<units::length> gns::get_geodial_separation() const
{
	if (!geodial_separation_)
		return {};
	return {*geodial_separation_};
}

void gns::append_data_to(std::string & s) const
{
	append(s, to_string(time_utc_));
	append(s, to_string(lat_));
	append(s, to_string(lat_hem_));
	append(s, to_string(lon_));
	append(s, to_string(lon_hem_));
	append(s, to_string(mode_ind_));
	append(s, to_string(number_of_satellites_));
	append(s, to_string(hdrop_));
	append(s, to_string(antenna_altitude_));
	append(s, to_string(geodial_separation_));
	append(s, to_string(age_of_differential_data_));
	append(s, to_string(differential_ref_station_id_));
}
}
}
