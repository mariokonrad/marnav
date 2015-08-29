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

std::unique_ptr<sentence> gst::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument, std::runtime_error)
{
	if (fields.size() != 8)
		throw std::invalid_argument{"invalid number of fields in gst::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<gst>();
	result->set_talker(talker);
	gst & detail = static_cast<gst &>(*result);

	read(fields[0], detail.time_utc);
	read(fields[1], detail.total_rms);
	read(fields[2], detail.dev_semi_major);
	read(fields[3], detail.dev_semi_minor);
	read(fields[4], detail.orientation);
	read(fields[5], detail.dev_lat);
	read(fields[6], detail.dev_lon);
	read(fields[7], detail.dev_alt);

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
