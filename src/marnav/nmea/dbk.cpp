#include "dbk.hpp"
#include "io.hpp"
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * dbk::TAG;

dbk::dbk()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
}

void dbk::set_depth_feet(double t)
{
	depth_feet = t;
	depth_feet_unit = unit::distance::FEET;
}

void dbk::set_depth_meter(double t)
{
	depth_meter = t;
	depth_meter_unit = unit::distance::METER;
}

void dbk::set_depth_fathom(double t)
{
	depth_fathom = t;
	depth_fathom_unit = unit::distance::FATHOM;
}

std::unique_ptr<sentence> dbk::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 6)
		throw std::invalid_argument{"invalid number of fields in dbk::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<dbk>();
	result->set_talker(talker);
	dbk & detail = static_cast<dbk &>(*result);

	read(fields[0], detail.depth_feet);
	read(fields[1], detail.depth_feet_unit);
	read(fields[2], detail.depth_meter);
	read(fields[3], detail.depth_meter_unit);
	read(fields[4], detail.depth_fathom);
	read(fields[5], detail.depth_fathom_unit);

	return result;
}

std::vector<std::string> dbk::get_data() const
{
	return {to_string(depth_feet), to_string(depth_feet_unit), to_string(depth_meter),
		to_string(depth_meter_unit), to_string(depth_fathom), to_string(depth_fathom_unit)};
}
}
}
