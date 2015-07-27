#include "xte.hpp"
#include "io.hpp"
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * xte::TAG;

xte::xte()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

std::unique_ptr<sentence> xte::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if ((fields.size() < 5) || (fields.size() > 6))
		throw std::invalid_argument{"invalid number of fields in xte::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<xte>();
	result->set_talker(talker);
	xte & detail = static_cast<xte &>(*result);

	read(fields[0], detail.status1);
	read(fields[1], detail.status2);
	read(fields[2], detail.cross_track_error_magnitude);
	read(fields[3], detail.direction_to_steer);
	read(fields[4], detail.cross_track_units);

	if (fields.size() == 6)
		read(fields[5], detail.mode_indicator);

	return result;
}

std::vector<std::string> xte::get_data() const
{
	return {to_string(status1), to_string(status2), to_string(cross_track_error_magnitude),
		to_string(direction_to_steer), to_string(cross_track_units),
		to_string(mode_indicator)};
}
}
}

