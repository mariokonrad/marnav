#include "tpc.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(tpc)

constexpr const char * tpc::TAG;

tpc::tpc()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

tpc::tpc(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in tpc"};

	read(*(first + 0), distance_centerline);
	read(*(first + 1), distance_centerline_unit);
	read(*(first + 2), distance_transducer);
	read(*(first + 3), distance_transducer_unit);
	read(*(first + 4), depth);
	read(*(first + 5), depth_unit);
}

std::vector<std::string> tpc::get_data() const
{
	return {to_string(distance_centerline), to_string(distance_centerline_unit),
		to_string(distance_transducer), to_string(distance_transducer_unit), to_string(depth),
		to_string(depth_unit)};
}
}
}
