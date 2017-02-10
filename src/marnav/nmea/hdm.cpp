#include "hdm.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * hdm::TAG;

hdm::hdm()
	: sentence(ID, TAG, talker_id::magnetic_compass)
{
}

hdm::hdm(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 2)
		throw std::invalid_argument{"invalid number of fields in hdm"};

	read(*(first + 0), heading);
	read(*(first + 1), heading_mag);
}

void hdm::set_heading(double t) noexcept
{
	heading = t;
	heading_mag = reference::MAGNETIC;
}

std::vector<std::string> hdm::get_data() const
{
	return {to_string(heading), to_string(heading_mag)};
}
}
}
