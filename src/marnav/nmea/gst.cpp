#include "gst.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * gst::TAG;

gst::gst()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

gst::gst(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 8)
		throw std::invalid_argument{"invalid number of fields in gst"};

	read(*(first + 0), time_utc_);
	read(*(first + 1), total_rms_);
	read(*(first + 2), dev_semi_major_);
	read(*(first + 3), dev_semi_minor_);
	read(*(first + 4), orientation_);
	read(*(first + 5), dev_lat_);
	read(*(first + 6), dev_lon_);
	read(*(first + 7), dev_alt_);
}

void gst::append_data_to(std::string & s) const
{
	append(s, format(time_utc_, 2));
	append(s, to_string(total_rms_));
	append(s, to_string(dev_semi_major_));
	append(s, to_string(dev_semi_minor_));
	append(s, to_string(orientation_));
	append(s, to_string(dev_lat_));
	append(s, to_string(dev_lon_));
	append(s, to_string(dev_alt_));
}
}
}
