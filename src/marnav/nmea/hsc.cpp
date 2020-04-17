#include <marnav/nmea/hsc.hpp>
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
constexpr sentence_id hsc::ID;
constexpr const char * hsc::TAG;

hsc::hsc()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

hsc::hsc(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 4)
		throw std::invalid_argument{"invalid number of fields in hsc"};

	read(*(first + 0), heading_true_);
	read(*(first + 1), heading_true_ref_);
	read(*(first + 2), heading_mag_);
	read(*(first + 3), heading_mag_ref_);
}

void hsc::set_heading_true(double t) noexcept
{
	heading_true_ = t;
	heading_true_ref_ = reference::TRUE;
}

void hsc::set_heading_mag(double t) noexcept
{
	heading_mag_ = t;
	heading_mag_ref_ = reference::MAGNETIC;
}

void hsc::append_data_to(std::string & s) const
{
	append(s, to_string(heading_true_));
	append(s, to_string(heading_true_ref_));
	append(s, to_string(heading_mag_));
	append(s, to_string(heading_mag_ref_));
}
}
}
