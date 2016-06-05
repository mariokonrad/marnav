#include "dbt.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(dbt)

constexpr const char * dbt::TAG;

dbt::dbt()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
}

dbt::dbt(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in dbt"};

	read(*(first + 0), depth_feet);
	read(*(first + 1), depth_feet_unit);
	read(*(first + 2), depth_meter);
	read(*(first + 3), depth_meter_unit);
	read(*(first + 4), depth_fathom);
	read(*(first + 5), depth_fathom_unit);
}

void dbt::set_depth_feet(double t) noexcept
{
	depth_feet = t;
	depth_feet_unit = unit::distance::feet;
}

void dbt::set_depth_meter(double t) noexcept
{
	depth_meter = t;
	depth_meter_unit = unit::distance::meter;
}

void dbt::set_depth_fathom(double t) noexcept
{
	depth_fathom = t;
	depth_fathom_unit = unit::distance::fathom;
}

std::vector<std::string> dbt::get_data() const
{
	return {to_string(depth_feet), to_string(depth_feet_unit), to_string(depth_meter),
		to_string(depth_meter_unit), to_string(depth_fathom), to_string(depth_fathom_unit)};
}
}
}
