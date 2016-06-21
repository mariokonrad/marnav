#include "tll.hpp"
#include <marnav/nmea/angle.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/nmea/convert.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(tll)

constexpr const char * tll::TAG;

tll::tll()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

tll::tll(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	if (std::distance(first, last) != 9)
		throw std::invalid_argument{"invalid number of fields in tll"};

	read(*(first + 0), target_number);
	read(*(first + 1), lat);
	read(*(first + 2), lat_hem);
	read(*(first + 3), lon);
	read(*(first + 4), lon_hem);
	read(*(first + 5), target_name);
	read(*(first + 6), time_utc);
	read(*(first + 7), target_status);
	read(*(first + 8), reference_target);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	lat = correct_hemisphere(lat, lat_hem);
	lon = correct_hemisphere(lon, lon_hem);
}

geo::longitude tll::get_longitude() const { return lon; }

geo::latitude tll::get_latitude() const { return lat; }

void tll::set_lat(const geo::latitude & t)
{
	lat = t;
	lat_hem = convert_hemisphere(t);
}

void tll::set_lon(const geo::longitude & t)
{
	lon = t;
	lon_hem = convert_hemisphere(t);
}

std::vector<std::string> tll::get_data() const
{
	return {format(target_number, 2), to_string(lat), to_string(lat_hem), to_string(lon),
		to_string(lon_hem), to_string(target_name), to_string(time_utc),
		to_string(target_status), to_string(reference_target)};
}
}
}
