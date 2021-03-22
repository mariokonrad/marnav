#include <marnav/nmea/pgrme.hpp>
#include <marnav/nmea/io.hpp>
#include "checks.hpp"

namespace marnav
{
namespace nmea
{
constexpr sentence_id pgrme::ID;
constexpr const char * pgrme::TAG;

pgrme::pgrme()
	: sentence(ID, TAG, talker::none)
{
}

pgrme::pgrme(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in pgrme"};

	unit::distance horizontal_position_error_unit;
	unit::distance vertical_position_error_unit;
	unit::distance overall_spherical_equiv_position_error_unit;

	read(*(first + 0), horizontal_position_error_);
	read(*(first + 1), horizontal_position_error_unit);
	read(*(first + 2), vertical_position_error_);
	read(*(first + 3), vertical_position_error_unit);
	read(*(first + 4), overall_spherical_equiv_position_error_);
	read(*(first + 5), overall_spherical_equiv_position_error_unit);

	check_value(horizontal_position_error_unit, {unit::distance::meter},
		"horizontal_position_error_unit");
	check_value(
		vertical_position_error_unit, {unit::distance::meter}, "vertical_position_error_unit");
	check_value(overall_spherical_equiv_position_error_unit, {unit::distance::meter},
		"overall_spherical_equiv_position_error_unit");
}

std::optional<units::length> pgrme::get_horizontal_position_error() const
{
	if (!horizontal_position_error_)
		return {};
	return {*horizontal_position_error_};
}

std::optional<units::length> pgrme::get_vertical_position_error() const
{
	if (!vertical_position_error_)
		return {};
	return {*vertical_position_error_};
}

std::optional<units::length> pgrme::get_overall_spherical_equiv_position_error() const
{
	if (!overall_spherical_equiv_position_error_)
		return {};
	return {*overall_spherical_equiv_position_error_};
}

void pgrme::append_data_to(std::string & s) const
{
	append(s, to_string(horizontal_position_error_));
	append(s, to_string(unit::distance::meter));
	append(s, to_string(vertical_position_error_));
	append(s, to_string(unit::distance::meter));
	append(s, to_string(overall_spherical_equiv_position_error_));
	append(s, to_string(unit::distance::meter));
}
}
}
