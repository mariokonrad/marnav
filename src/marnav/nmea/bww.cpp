#include "bww.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr sentence_id bww::ID;
constexpr const char * bww::TAG;

bww::bww()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

bww::bww(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in bww"};

	read(*(first + 0), bearing_true_);
	read(*(first + 1), bearing_true_ref_);
	read(*(first + 2), bearing_mag_);
	read(*(first + 3), bearing_mag_ref_);
	read(*(first + 4), waypoint_to_);
	read(*(first + 5), waypoint_from_);
}

void bww::set_bearing_true(double t) noexcept
{
	bearing_true_ = t;
	bearing_true_ref_ = reference::TRUE;
}

void bww::set_bearing_mag(double t) noexcept
{
	bearing_mag_ = t;
	bearing_mag_ref_ = reference::MAGNETIC;
}

void bww::append_data_to(std::string & s) const
{
	append(s, to_string(bearing_true_));
	append(s, to_string(bearing_true_ref_));
	append(s, to_string(bearing_mag_));
	append(s, to_string(bearing_mag_ref_));
	append(s, to_string(waypoint_to_));
	append(s, to_string(waypoint_from_));
}
}
}
