#include <marnav/nmea/gbs.hpp>
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav::nmea
{
constexpr sentence_id gbs::ID;
constexpr const char * gbs::TAG;

gbs::gbs()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

gbs::gbs(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 8)
		throw std::invalid_argument{"invalid number of fields in gbs"};

	read(*(first + 0), time_utc_);
	read(*(first + 1), err_lat_);
	read(*(first + 2), err_lon_);
	read(*(first + 3), err_alt_);
	read(*(first + 4), satellite_);
	read(*(first + 5), probability_);
	read(*(first + 6), bias_);
	read(*(first + 7), bias_dev_);
}

void gbs::append_data_to(std::string & s, const version &) const
{
	append(s, format(time_utc_, 2));
	append(s, to_string(err_lat_));
	append(s, to_string(err_lon_));
	append(s, to_string(err_alt_));
	append(s, format(satellite_, 3));
	append(s, to_string(probability_));
	append(s, to_string(bias_));
	append(s, to_string(bias_dev_));
}
}
