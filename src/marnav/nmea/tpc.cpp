#include "tpc.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * tpc::TAG;

tpc::tpc()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

tpc::tpc(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in tpc"};

	read(*(first + 0), distance_centerline_);
	read(*(first + 1), distance_centerline_unit_);
	read(*(first + 2), distance_transducer_);
	read(*(first + 3), distance_transducer_unit_);
	read(*(first + 4), depth_);
	read(*(first + 5), depth_unit_);
}

void tpc::append_data_to(std::string & s) const
{
	append(s, to_string(distance_centerline_));
	append(s, to_string(distance_centerline_unit_));
	append(s, to_string(distance_transducer_));
	append(s, to_string(distance_transducer_unit_));
	append(s, to_string(depth_));
	append(s, to_string(depth_unit_));
}
}
}
