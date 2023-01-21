#include <marnav/nmea/pgrmm.hpp>
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav::nmea
{
constexpr sentence_id pgrmm::ID;
constexpr const char * pgrmm::TAG;

pgrmm::pgrmm()
	: sentence(ID, TAG, talker::none)
{
}

pgrmm::pgrmm(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 1)
		throw std::invalid_argument{"invalid number of fields in pgrmm"};

	read(*(first + 0), map_datum_);
}

void pgrmm::append_data_to(std::string & s, const version &) const
{
	append(s, to_string(map_datum_));
}

void pgrmm::set_map_datum(const std::string & t) noexcept
{
	// in a regular NMEA sentence, there is only 72 characters for the map datum
	if (t.size() <= 72) {
		map_datum_ = t;
	} else {
		map_datum_ = t.substr(0, 72);
	}
}
}
