#include "pgrme.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * pgrme::TAG;

pgrme::pgrme()
	: sentence(ID, TAG, talker_id::none)
	, horizontal_position_error_unit(unit::distance::meter)
	, vertical_position_error_unit(unit::distance::meter)
	, overall_spherical_equiv_position_error_unit(unit::distance::meter)
{
}

std::unique_ptr<sentence> pgrme::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in pgrme::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<pgrme>();
	result->set_talker(talker);
	pgrme & detail = static_cast<pgrme &>(*result);

	read(*(first + 0), detail.horizontal_position_error);
	read(*(first + 1), detail.horizontal_position_error_unit);
	read(*(first + 2), detail.vertical_position_error);
	read(*(first + 3), detail.vertical_position_error_unit);
	read(*(first + 4), detail.overall_spherical_equiv_position_error);
	read(*(first + 5), detail.overall_spherical_equiv_position_error_unit);

	return result;
}

std::vector<std::string> pgrme::get_data() const
{
	return {to_string(horizontal_position_error), to_string(horizontal_position_error_unit),
		to_string(vertical_position_error), to_string(vertical_position_error_unit),
		to_string(overall_spherical_equiv_position_error),
		to_string(overall_spherical_equiv_position_error_unit)};
}
}
}
