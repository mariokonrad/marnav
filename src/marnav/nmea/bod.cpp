#include <marnav/nmea/bod.hpp>
#include <marnav/nmea/io.hpp>
#include "checks.hpp"

namespace marnav::nmea
{
constexpr sentence_id bod::ID;
constexpr const char * bod::TAG;

bod::bod()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

bod::bod(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in bod"};

	reference type_true;
	reference type_magn;

	read(*(first + 0), bearing_true_);
	read(*(first + 1), type_true);
	read(*(first + 2), bearing_magn_);
	read(*(first + 3), type_magn);
	read(*(first + 4), waypoint_to_);
	read(*(first + 5), waypoint_from_);

	check_value(type_true, {reference::TRUE}, "bearing true type");
	check_value(type_magn, {reference::MAGNETIC}, "bearing magnetic type");
}

void bod::set_bearing_true(double t) noexcept
{
	bearing_true_ = t;
}

void bod::set_bearing_magn(double t) noexcept
{
	bearing_magn_ = t;
}

void bod::append_data_to(std::string & s, const version &) const
{
	append(s, to_string(bearing_true_));
	append(s, to_string_if(reference::TRUE, bearing_true_));
	append(s, to_string(bearing_magn_));
	append(s, to_string_if(reference::MAGNETIC, bearing_magn_));
	append(s, to_string(waypoint_to_));
	append(s, to_string(waypoint_from_));
}
}
