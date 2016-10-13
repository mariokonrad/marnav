#include "pgrme.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(pgrme)

constexpr const char * pgrme::TAG;

pgrme::pgrme()
	: sentence(ID, TAG, talker_id::none)
{
}

pgrme::pgrme(
	talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in pgrme"};

	read(*(first + 0), horizontal_position_error);
	read(*(first + 1), horizontal_position_error_unit);
	read(*(first + 2), vertical_position_error);
	read(*(first + 3), vertical_position_error_unit);
	read(*(first + 4), overall_spherical_equiv_position_error);
	read(*(first + 5), overall_spherical_equiv_position_error_unit);
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
