#include "pgrmz.hpp"
#include <marnav/nmea/io.hpp>

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

	read(*(first + 0), altitude);
	read(*(first + 1), altitude_unit);
	read(*(first + 2), fix, fix_type_mapping);
}

std::vector<std::string> pgrmz::get_data() const
{
	return {to_string(altitude), to_string(altitude_unit), to_string(fix)};
}
}
}
