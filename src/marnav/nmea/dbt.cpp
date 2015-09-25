#include "dbt.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * dbt::TAG;

dbt::dbt()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
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

std::unique_ptr<sentence> dbt::parse(
	const std::string & talker, const std::vector<std::string> & fields)
{
	if (fields.size() != 6)
		throw std::invalid_argument{"invalid number of fields in dbt::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<dbt>();
	result->set_talker(talker);
	dbt & detail = static_cast<dbt &>(*result);

	read(fields[0], detail.depth_feet);
	read(fields[1], detail.depth_feet_unit);
	read(fields[2], detail.depth_meter);
	read(fields[3], detail.depth_meter_unit);
	read(fields[4], detail.depth_fathom);
	read(fields[5], detail.depth_fathom_unit);

	return result;
}

std::vector<std::string> dbt::get_data() const
{
	return {to_string(depth_feet), to_string(depth_feet_unit), to_string(depth_meter),
		to_string(depth_meter_unit), to_string(depth_fathom), to_string(depth_fathom_unit)};
}
}
}
