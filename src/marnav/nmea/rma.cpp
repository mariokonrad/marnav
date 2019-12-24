#include <marnav/nmea/rma.hpp>
#include "checks.hpp"
#include "convert.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr sentence_id rma::ID;
constexpr const char * rma::TAG;

rma::rma()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

rma::rma(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 11)
		throw std::invalid_argument{"invalid number of fields in rma"};

	read(*(first + 0), blink_warning_);
	read(*(first + 1), lat_);
	read(*(first + 2), lat_hem_);
	read(*(first + 3), lon_);
	read(*(first + 4), lon_hem_);
	read(*(first + 5), time_diff_a_);
	read(*(first + 6), time_diff_b_);
	read(*(first + 7), sog_);
	read(*(first + 8), track_);
	read(*(first + 9), magnetic_var_);
	read(*(first + 10), magnetic_var_hem_);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	lat_ = correct_hemisphere(lat_, lat_hem_);
	lon_ = correct_hemisphere(lon_, lon_hem_);
}

utils::optional<geo::longitude> rma::get_lon() const
{
	return (lon_ && lon_hem_) ? lon_ : utils::optional<geo::longitude>{};
}

utils::optional<geo::latitude> rma::get_lat() const
{
	return (lat_ && lat_hem_) ? lat_ : utils::optional<geo::latitude>{};
}

void rma::set_lat(const geo::latitude & t)
{
	lat_ = t;
	lat_hem_ = convert_hemisphere(t);
}

void rma::set_lon(const geo::longitude & t)
{
	lon_ = t;
	lon_hem_ = convert_hemisphere(t);
}

void rma::set_magnetic_var(double t, direction h)
{
	check_value(h, {direction::east, direction::west}, "mag var hemisphere");
	magnetic_var_ = t;
	magnetic_var_hem_ = h;
}

void rma::append_data_to(std::string & s) const
{
	append(s, to_string(blink_warning_));
	append(s, to_string(lat_));
	append(s, to_string(lat_hem_));
	append(s, to_string(lon_));
	append(s, to_string(lon_hem_));
	append(s, to_string(time_diff_a_));
	append(s, to_string(time_diff_b_));
	append(s, to_string(sog_));
	append(s, to_string(track_));
	append(s, to_string(magnetic_var_));
	append(s, to_string(magnetic_var_hem_));
}
}
}
