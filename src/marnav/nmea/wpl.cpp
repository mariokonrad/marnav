#include <marnav/nmea/wpl.hpp>
#include "convert.hpp"
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
constexpr sentence_id wpl::ID;
constexpr const char * wpl::TAG;

wpl::wpl()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

wpl::wpl(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 5)
		throw std::invalid_argument{"invalid number of fields in wpl"};

	read(*(first + 0), lat_);
	read(*(first + 1), lat_hem_);
	read(*(first + 2), lon_);
	read(*(first + 3), lon_hem_);
	read(*(first + 4), waypoint_id_);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	lat_ = correct_hemisphere(lat_, lat_hem_);
	lon_ = correct_hemisphere(lon_, lon_hem_);
}

std::optional<geo::longitude> wpl::get_lon() const
{
	return (lon_ && lon_hem_) ? lon_ : std::optional<geo::longitude>{};
}

std::optional<geo::latitude> wpl::get_lat() const
{
	return (lat_ && lat_hem_) ? lat_ : std::optional<geo::latitude>{};
}

void wpl::set_lat(const geo::latitude & t)
{
	lat_ = t;
	lat_hem_ = convert_hemisphere(t);
}

void wpl::set_lon(const geo::longitude & t)
{
	lon_ = t;
	lon_hem_ = convert_hemisphere(t);
}

void wpl::append_data_to(std::string & s, const version &) const
{
	append(s, to_string(lat_));
	append(s, to_string(lat_hem_));
	append(s, to_string(lon_));
	append(s, to_string(lon_hem_));
	append(s, to_string(waypoint_id_));
}
}
}
