#include "gst.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * gst::TAG;

gst::gst()
	: sentence(ID, TAG, talker_id::global_positioning_system)
	, total_rms(0.0)
	, dev_semi_major(0.0)
	, dev_semi_minor(0.0)
	, orientation(0.0)
	, dev_lat(0.0)
	, dev_lon(0.0)
	, dev_alt(0.0)
{
}

std::unique_ptr<sentence> gst::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 8)
		throw std::invalid_argument{"invalid number of fields in gst::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<gst>();
	result->set_talker(talker);
	gst & detail = static_cast<gst &>(*result);

	read(*(first + 0), detail.time_utc);
	read(*(first + 1), detail.total_rms);
	read(*(first + 2), detail.dev_semi_major);
	read(*(first + 3), detail.dev_semi_minor);
	read(*(first + 4), detail.orientation);
	read(*(first + 5), detail.dev_lat);
	read(*(first + 6), detail.dev_lon);
	read(*(first + 7), detail.dev_alt);

	return result;
}

std::vector<std::string> gst::get_data() const
{
	return {format(time_utc, 2), to_string(total_rms), to_string(dev_semi_major),
		to_string(dev_semi_minor), to_string(orientation), to_string(dev_lat),
		to_string(dev_lon), to_string(dev_alt)};
}
}
}
