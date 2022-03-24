#include <marnav/nmea/tll.hpp>
#include "convert.hpp"
#include <marnav/nmea/angle.hpp>
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
constexpr sentence_id tll::ID;
constexpr const char * tll::TAG;

tll::tll()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

tll::tll(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 9)
		throw std::invalid_argument{"invalid number of fields in tll"};

	read(*(first + 0), number_);
	read(*(first + 1), lat_);
	read(*(first + 2), lat_hem_);
	read(*(first + 3), lon_);
	read(*(first + 4), lon_hem_);
	read(*(first + 5), name_);
	read(*(first + 6), time_utc_);
	read(*(first + 7), status_);
	read(*(first + 8), reference_target_);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	lat_ = correct_hemisphere(lat_, lat_hem_);
	lon_ = correct_hemisphere(lon_, lon_hem_);
}

geo::longitude tll::get_lon() const
{
	return lon_;
}

geo::latitude tll::get_lat() const
{
	return lat_;
}

void tll::set_lat(const geo::latitude & t)
{
	lat_ = t;
	lat_hem_ = convert_hemisphere(t);
}

void tll::set_lon(const geo::longitude & t)
{
	lon_ = t;
	lon_hem_ = convert_hemisphere(t);
}

void tll::append_data_to(std::string & s, const version &) const
{
	append(s, format(number_, 2));
	append(s, to_string(lat_));
	append(s, to_string(lat_hem_));
	append(s, to_string(lon_));
	append(s, to_string(lon_hem_));
	append(s, to_string(name_));
	append(s, to_string(time_utc_));
	append(s, to_string(status_));
	append(s, to_string(reference_target_));
}
}
}
