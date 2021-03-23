#include <marnav/nmea/dbt.hpp>
#include <marnav/nmea/io.hpp>
#include "checks.hpp"

namespace marnav
{
namespace nmea
{
constexpr sentence_id dbt::ID;
constexpr const char * dbt::TAG;

dbt::dbt()
	: sentence(ID, TAG, talker::integrated_instrumentation)
{
}

dbt::dbt(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in dbt"};

	std::optional<unit::distance> depth_feet_unit;
	std::optional<unit::distance> depth_meter_unit;
	std::optional<unit::distance> depth_fathom_unit;

	read(*(first + 0), depth_feet_);
	read(*(first + 1), depth_feet_unit);
	read(*(first + 2), depth_meter_);
	read(*(first + 3), depth_meter_unit);
	read(*(first + 4), depth_fathom_);
	read(*(first + 5), depth_fathom_unit);

	check_value(depth_feet_unit, {unit::distance::feet}, "depth_feet_unit");
	check_value(depth_meter_unit, {unit::distance::meter}, "depth_meter_unit");
	check_value(depth_fathom_unit, {unit::distance::fathom}, "depth_fathom_unit");
}

std::optional<units::length> dbt::get_depth_feet() const
{
	if (!depth_feet_)
		return {};
	return {*depth_feet_};
}

std::optional<units::length> dbt::get_depth_meter() const
{
	if (!depth_meter_)
		return {};
	return {*depth_meter_};
}

std::optional<units::length> dbt::get_depth_fathom() const
{
	if (!depth_fathom_)
		return {};
	return {*depth_fathom_};
}

void dbt::set_depth_feet(units::length t)
{
	if (t.value() < 0.0)
		throw std::invalid_argument{"invalid argument, depth in feet less than zero"};
	depth_feet_ = t.get<units::feet>();
}

void dbt::set_depth_meter(units::length t)
{
	if (t.value() < 0.0)
		throw std::invalid_argument{"invalid argument, depth in meters less than zero"};
	depth_meter_ = t.get<units::meters>();
}

void dbt::set_depth_fathom(units::length t)
{
	if (t.value() < 0.0)
		throw std::invalid_argument{"invalid argument, depth in fathoms less than zero"};
	depth_fathom_ = t.get<units::fathoms>();
}

void dbt::append_data_to(std::string & s) const
{
	append(s, to_string(depth_feet_));
	append(s, to_string_if(unit::distance::feet, depth_feet_));
	append(s, to_string(depth_meter_));
	append(s, to_string_if(unit::distance::meter, depth_meter_));
	append(s, to_string(depth_fathom_));
	append(s, to_string_if(unit::distance::fathom, depth_fathom_));
}
}
}
