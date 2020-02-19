#include <marnav/nmea/pgrmz.hpp>
#include <marnav/nmea/io.hpp>
#include "checks.hpp"

namespace marnav
{
namespace nmea
{
/// @cond DEV
namespace
{
/// Converts data read from the NMEA string to the corresponding
/// enumerator.
///
/// @param[in] value The numerical value to convert.
/// @return The corresponding enumerator.
/// @exception std::invalid_argument The specified value to convert is unknown.
///
static pgrmz::fix_type fix_type_mapping(
	typename std::underlying_type<pgrmz::fix_type>::type value)
{
	switch (value) {
		case '1':
			return pgrmz::fix_type::no_fix;
		case '2':
			return pgrmz::fix_type::d2fix;
		case '3':
			return pgrmz::fix_type::d3fix;
	}
	throw std::invalid_argument{"invaild value for conversion to pgrmz::fix_type"};
}
}
/// @endcond

std::string to_string(pgrmz::fix_type value)
{
	switch (value) {
		case pgrmz::fix_type::no_fix:
			return "1";
		case pgrmz::fix_type::d2fix:
			return "2";
		case pgrmz::fix_type::d3fix:
			return "3";
	}
	throw std::invalid_argument{"invaild value for conversion of pgrmz::fix_type"};
}

constexpr sentence_id pgrmz::ID;
constexpr const char * pgrmz::TAG;

pgrmz::pgrmz()
	: sentence(ID, TAG, talker_id::none)
{
}

pgrmz::pgrmz(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 3)
		throw std::invalid_argument{"invalid number of fields in pgrmz"};

	unit::distance altitude_unit;

	read(*(first + 0), altitude_);
	read(*(first + 1), altitude_unit);
	read(*(first + 2), fix_, fix_type_mapping);

	check_value(altitude_unit, {unit::distance::feet}, "altitude unit");
}

void pgrmz::append_data_to(std::string & s) const
{
	append(s, to_string(altitude_));
	append(s, to_string(unit::distance::feet));
	append(s, to_string(fix_));
}
}
}
