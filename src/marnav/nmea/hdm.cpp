#include <marnav/nmea/hdm.hpp>
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
constexpr sentence_id hdm::ID;
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

	read(*(first + 0), heading_);
	read(*(first + 1), heading_mag_);
}

void hdm::set_heading(double t) noexcept
{
	heading_ = t;
	heading_mag_ = reference::MAGNETIC;
}

void hdm::append_data_to(std::string & s) const
{
	append(s, to_string(heading_));
	append(s, to_string(heading_mag_));
}
}
}
