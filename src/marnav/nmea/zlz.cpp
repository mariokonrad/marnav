#include <marnav/nmea/zlz.hpp>
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
constexpr sentence_id zlz::ID;
constexpr const char * zlz::TAG;

zlz::zlz()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

zlz::zlz(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 3)
		throw std::invalid_argument{"invalid number of fields in zlz"};

	read(*(first + 0), time_utc_);
	read(*(first + 1), time_local_);
	read(*(first + 2), local_zone_description_);
}

void zlz::append_data_to(std::string & s) const
{
	append(s, to_string(time_utc_));
	append(s, to_string(time_local_));
	append(s, format(local_zone_description_, (local_zone_description_ < 0) ? 3 : 2));
}

void zlz::set_local_zone_description(int32_t t)
{
	if ((t < -12) || (t > 12))
		throw std::invalid_argument{"zone descriptor out of range -12..+12"};
	local_zone_description_ = t;
}
}
}
