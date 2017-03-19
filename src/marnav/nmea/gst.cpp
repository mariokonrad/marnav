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

	read(*(first + 0), time_utc);
	read(*(first + 1), total_rms);
	read(*(first + 2), dev_semi_major);
	read(*(first + 3), dev_semi_minor);
	read(*(first + 4), orientation);
	read(*(first + 5), dev_lat);
	read(*(first + 6), dev_lon);
	read(*(first + 7), dev_alt);
}

void gst::append_data_to(std::string & s) const
{
	append(s, format(time_utc, 2));
	append(s, to_string(total_rms));
	append(s, to_string(dev_semi_major));
	append(s, to_string(dev_semi_minor));
	append(s, to_string(orientation));
	append(s, to_string(dev_lat));
	append(s, to_string(dev_lon));
	append(s, to_string(dev_alt));
}
}
}
