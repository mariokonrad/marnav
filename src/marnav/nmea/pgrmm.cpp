#include "pgrmm.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(pgrmm)

constexpr const char * pgrmm::TAG;

pgrmm::pgrmm()
	: sentence(ID, TAG, talker_id::none)
{
}

pgrmm::pgrmm(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 1)
		throw std::invalid_argument{"invalid number of fields in pgrmm"};

	read(*(first + 0), map_datum);
}

std::vector<std::string> pgrmm::get_data() const
{
	return {to_string(map_datum)};
}

void pgrmm::set_map_datum(const std::string & t) noexcept
{
	// in a regular NMEA sentence, there is only 72 characters for the map datum
	if (t.size() <= 72) {
		map_datum = t;
	} else {
		map_datum = t.substr(0, 72);
	}
}
}
}
