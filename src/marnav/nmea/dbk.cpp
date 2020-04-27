#include <marnav/nmea/dbk.hpp>
#include <marnav/nmea/io.hpp>
#include "checks.hpp"

namespace marnav
{
namespace nmea
{
constexpr sentence_id dbk::ID;
constexpr const char * dbk::TAG;

dbk::dbk()
	: sentence(ID, TAG, talker::integrated_instrumentation)
{
}

dbk::dbk(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in dbk"};

	utils::optional<unit::distance> depth_feet_unit;
	utils::optional<unit::distance> depth_meter_unit;
	utils::optional<unit::distance> depth_fathom_unit;

	read(*(first + 0), depth_feet_);
	read(*(first + 1), depth_feet_unit);
	read(*(first + 2), depth_meter_);
	read(*(first + 3), depth_meter_unit);
	read(*(first + 4), depth_fathom_);
	read(*(first + 5), depth_fathom_unit);

	check_value(depth_feet_unit, {unit::distance::feet}, "depth feet unit");
	check_value(depth_meter_unit, {unit::distance::meter}, "depth meter unit");
	check_value(depth_fathom_unit, {unit::distance::fathom}, "depth fathom unit");
}

void dbk::set_depth_feet(units::length t) noexcept
{
	depth_feet_ = t.get<units::feet>();
}

void dbk::set_depth_meter(units::length t) noexcept
{
	depth_meter_ = t.get<units::meters>();
}

void dbk::set_depth_fathom(units::length t) noexcept
{
	depth_fathom_ = t.get<units::fathoms>();
}

utils::optional<units::length> dbk::get_depth_feet() const
{
	if (!depth_feet_)
		return {};
	return {*depth_feet_};
}

utils::optional<units::length> dbk::get_depth_meter() const
{
	if (!depth_meter_)
		return {};
	return {*depth_meter_};
}

utils::optional<units::length> dbk::get_depth_fathom() const
{
	if (!depth_fathom_)
		return {};
	return {*depth_fathom_};
}

void dbk::append_data_to(std::string & s) const
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
