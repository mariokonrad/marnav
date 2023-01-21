#include <marnav/nmea/bww.hpp>
#include <marnav/nmea/io.hpp>
#include "checks.hpp"

namespace marnav::nmea
{
constexpr sentence_id bww::ID;
constexpr const char * bww::TAG;

bww::bww()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

bww::bww(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in bww"};

	std::optional<reference> bearing_true_ref;
	std::optional<reference> bearing_mag_ref;

	read(*(first + 0), bearing_true_);
	read(*(first + 1), bearing_true_ref);
	read(*(first + 2), bearing_magn_);
	read(*(first + 3), bearing_mag_ref);
	read(*(first + 4), waypoint_to_);
	read(*(first + 5), waypoint_from_);

	check_value(bearing_true_ref, {reference::TRUE}, "");
	check_value(bearing_mag_ref, {reference::MAGNETIC}, "");
}

void bww::set_bearing_true(double t) noexcept
{
	bearing_true_ = t;
}

void bww::set_bearing_mag(double t) noexcept
{
	bearing_magn_ = t;
}

void bww::append_data_to(std::string & s, const version &) const
{
	append(s, to_string(bearing_true_));
	append(s, to_string_if(reference::TRUE, bearing_true_));
	append(s, to_string(bearing_magn_));
	append(s, to_string_if(reference::MAGNETIC, bearing_magn_));
	append(s, to_string(waypoint_to_));
	append(s, to_string(waypoint_from_));
}
}
