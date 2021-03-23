#include <marnav/nmea/gll.hpp>
#include "checks.hpp"
#include "convert.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr sentence_id gll::ID;
constexpr const char * gll::TAG;

gll::gll()
	: sentence(ID, TAG, talker::global_positioning_system)
	, mode_ind_(mode_indicator::invalid)
{
}

gll::gll(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	// older version has no 'mode_indicator'
	const auto size = std::distance(first, last);
	if ((size < 6) || (size > 7))
		throw std::invalid_argument{
			std::string{"invalid number of fields in gll: expected 6, got "}
			+ std::to_string(size)};

	read(*(first + 0), lat_);
	read(*(first + 1), lat_hem_);
	read(*(first + 2), lon_);
	read(*(first + 3), lon_hem_);
	read(*(first + 4), time_utc_);
	read(*(first + 5), data_valid_);

	if (size > 6)
		read(*(first + 6), mode_ind_);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	lat_ = correct_hemisphere(lat_, lat_hem_);
	lon_ = correct_hemisphere(lon_, lon_hem_);
}

std::optional<geo::longitude> gll::get_lon() const
{
	return (lon_ && lon_hem_) ? lon_ : std::optional<geo::longitude>{};
}

std::optional<geo::latitude> gll::get_lat() const
{
	return (lat_ && lat_hem_) ? lat_ : std::optional<geo::latitude>{};
}

void gll::set_lat(const geo::latitude & t)
{
	lat_ = t;
	lat_hem_ = convert_hemisphere(t);
}

void gll::set_lon(const geo::longitude & t)
{
	lon_ = t;
	lon_hem_ = convert_hemisphere(t);
}

void gll::append_data_to(std::string & s) const
{
	append(s, to_string(lat_));
	append(s, to_string(lat_hem_));
	append(s, to_string(lon_));
	append(s, to_string(lon_hem_));
	append(s, to_string(time_utc_));
	append(s, to_string(data_valid_));
	append(s, to_string(mode_ind_));
}
}
}
