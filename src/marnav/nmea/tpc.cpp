#include <marnav/nmea/tpc.hpp>
#include <marnav/nmea/io.hpp>
#include "checks.hpp"

namespace marnav::nmea
{
constexpr sentence_id tpc::ID;
constexpr const char * tpc::TAG;

tpc::tpc()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

tpc::tpc(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in tpc"};

	unit::distance distance_centerline_unit;
	unit::distance distance_transducer_unit;
	unit::distance depth_unit;

	read(*(first + 0), distance_centerline_);
	read(*(first + 1), distance_centerline_unit);
	read(*(first + 2), distance_transducer_);
	read(*(first + 3), distance_transducer_unit);
	read(*(first + 4), depth_);
	read(*(first + 5), depth_unit);

	check_value(distance_centerline_unit, {unit::distance::meter}, "distance_centerline_unit");
	check_value(distance_transducer_unit, {unit::distance::meter}, "distance_transducer_unit");
	check_value(depth_unit, {unit::distance::meter}, "depth_unit");
}

void tpc::append_data_to(std::string & s, const version &) const
{
	append(s, to_string(distance_centerline_));
	append(s, to_string(unit::distance::meter));
	append(s, to_string(distance_transducer_));
	append(s, to_string(unit::distance::meter));
	append(s, to_string(depth_));
	append(s, to_string(unit::distance::meter));
}
}
