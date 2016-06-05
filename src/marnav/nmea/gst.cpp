#include "gst.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(gst)

constexpr const char * gst::TAG;

gst::gst()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

gst::gst(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
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

std::vector<std::string> gst::get_data() const
{
	return {format(time_utc, 2), to_string(total_rms), to_string(dev_semi_major),
		to_string(dev_semi_minor), to_string(orientation), to_string(dev_lat),
		to_string(dev_lon), to_string(dev_alt)};
}
}
}
