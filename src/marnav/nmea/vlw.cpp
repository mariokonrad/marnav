#include <marnav/nmea/vlw.hpp>
#include <marnav/nmea/io.hpp>
#include "checks.hpp"

namespace marnav
{
namespace nmea
{
constexpr sentence_id vlw::ID;
constexpr const char * vlw::TAG;

vlw::vlw()
	: sentence(ID, TAG, talker::integrated_instrumentation)
{
}

vlw::vlw(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 4)
		throw std::invalid_argument{"invalid number of fields in vlw"};

	std::optional<unit::distance> distance_cum_unit;
	std::optional<unit::distance> distance_reset_unit;

	read(*(first + 0), distance_cum_);
	read(*(first + 1), distance_cum_unit);
	read(*(first + 2), distance_reset_);
	read(*(first + 3), distance_reset_unit);

	check_value(distance_cum_unit, {unit::distance::nm}, "distance_cum_unit");
	check_value(distance_reset_unit, {unit::distance::nm}, "distance_reset_unit");
}

void vlw::set_distance_cum_nm(units::length t) noexcept
{
	distance_cum_ = t.get<units::nautical_miles>();
}

void vlw::set_distance_reset_nm(units::length t) noexcept
{
	distance_reset_ = t.get<units::nautical_miles>();
}

std::optional<units::length> vlw::get_distance_cum() const
{
	if (!distance_cum_)
		return {};
	return {*distance_cum_};
}

std::optional<units::length> vlw::get_distance_reset() const
{
	if (!distance_reset_)
		return {};
	return {*distance_reset_};
}

void vlw::append_data_to(std::string & s) const
{
	append(s, to_string(distance_cum_));
	append(s, to_string_if(unit::distance::nm, distance_cum_));
	append(s, to_string(distance_reset_));
	append(s, to_string_if(unit::distance::nm, distance_reset_));
}
}
}
