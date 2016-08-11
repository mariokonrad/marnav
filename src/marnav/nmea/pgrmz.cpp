#include "pgrmz.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(pgrmz)

constexpr const char * pgrmz::TAG;

pgrmz::pgrmz()
	: sentence(ID, TAG, talker_id::none)
{
}

pgrmz::pgrmz(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	if (std::distance(first, last) != 3)
		throw std::invalid_argument{"invalid number of fields in pgrmz"};

	read(*(first + 0), altitude);
	read(*(first + 1), altitude_unit);
	read(*(first + 2), pos_fix_dim);
}

std::vector<std::string> pgrmz::get_data() const
{
	return {to_string(altitude), to_string(altitude_unit), to_string(pos_fix_dim)};
}

void pgrmz::set_pos_fix_dim(uint32_t t) noexcept
{
	switch (t) {
		case 2:
		case 3:
			pos_fix_dim = t;
			break;
		default:
			break;
	}
}
}
}
