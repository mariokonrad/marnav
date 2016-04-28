#include "tpc.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * tpc::TAG;

tpc::tpc()
	: sentence(ID, TAG, talker_id::global_positioning_system)
	, distance_centerline(0.0)
	, distance_centerline_unit(unit::distance::meter)
	, distance_transducer(0.0)
	, distance_transducer_unit(unit::distance::meter)
	, depth(0.0)
	, depth_unit(unit::distance::meter)
{
}

std::unique_ptr<sentence> tpc::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in tpc::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<tpc>();
	result->set_talker(talker);
	tpc & detail = static_cast<tpc &>(*result);

	read(*(first + 0), detail.distance_centerline);
	read(*(first + 1), detail.distance_centerline_unit);
	read(*(first + 2), detail.distance_transducer);
	read(*(first + 3), detail.distance_transducer_unit);
	read(*(first + 4), detail.depth);
	read(*(first + 5), detail.depth_unit);

	return result;
}

std::vector<std::string> tpc::get_data() const
{
	return {to_string(distance_centerline), to_string(distance_centerline_unit),
		to_string(distance_transducer), to_string(distance_transducer_unit), to_string(depth),
		to_string(depth_unit)};
}
}
}
