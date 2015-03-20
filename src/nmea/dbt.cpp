#include "dbt.hpp"
#include <utils/unique.hpp>
#include "io.hpp"

namespace nmea
{

dbt::dbt()
	: sentence(ID, "DBT", talker_id::integrated_instrumentation)
{
}

void dbt::set_depth_feet(double t)
{
	depth_feet = t;
	depth_unit_feet = unit::FEET;
}

void dbt::set_depth_meter(double t)
{
	depth_meter = t;
	depth_unit_meter = unit::METER;
}

void dbt::set_depth_fathom(double t)
{
	depth_fathom = t;
	depth_unit_fathom = unit::FATHOM;
}

std::unique_ptr<sentence>
dbt::parse(const std::string& talker,
		   const std::vector<std::string>& fields) throw(std::invalid_argument)
{
	if (fields.size() != 6)
		throw std::invalid_argument{"invalid number of fields in dbt::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<dbt>();
	result->set_talker(talker);
	dbt& detail = static_cast<dbt&>(*result);

	read(fields[0], detail.depth_feet);
	read(fields[1], detail.depth_unit_feet);
	read(fields[2], detail.depth_meter);
	read(fields[3], detail.depth_unit_meter);
	read(fields[4], detail.depth_fathom);
	read(fields[5], detail.depth_unit_fathom);

	return result;
}

std::vector<std::string> dbt::get_data() const
{
	return {to_string(depth_feet),		 to_string(depth_unit_feet), to_string(depth_meter),
			to_string(depth_unit_meter), to_string(depth_fathom),	to_string(depth_unit_fathom)};
}
}
