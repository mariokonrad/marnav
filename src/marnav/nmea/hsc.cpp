#include "hsc.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(hsc)

constexpr const char * hsc::TAG;

hsc::hsc()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

hsc::hsc(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	if (std::distance(first, last) != 4)
		throw std::invalid_argument{"invalid number of fields in hsc"};

	read(*(first + 0), heading_true);
	read(*(first + 1), heading_true_ref);
	read(*(first + 2), heading_mag);
	read(*(first + 3), heading_mag_ref);
}

void hsc::set_heading_true(double t) noexcept
{
	heading_true = t;
	heading_true_ref = reference::TRUE;
}

void hsc::set_heading_mag(double t) noexcept
{
	heading_mag = t;
	heading_mag_ref = reference::MAGNETIC;
}

std::vector<std::string> hsc::get_data() const
{
	return {to_string(heading_true), to_string(heading_true_ref), to_string(heading_mag),
		to_string(heading_mag_ref)};
}
}
}
