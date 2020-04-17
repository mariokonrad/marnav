#include <marnav/nmea/rsd.hpp>
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
constexpr sentence_id rsd::ID;
constexpr const char * rsd::TAG;

rsd::rsd()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
}

rsd::rsd(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 13)
		throw std::invalid_argument{"invalid number of fields in rsd"};

	read(*(first + 0), origin_range_1);
	read(*(first + 1), origin_bearing_1);
	read(*(first + 2), variable_range_marker_1);
	read(*(first + 3), bearing_line_1);
	read(*(first + 4), origin_range_2);
	read(*(first + 5), origin_bearing_2);
	read(*(first + 6), variable_range_marker_2);
	read(*(first + 7), bearing_line_2);
	read(*(first + 8), cursor_range_);
	read(*(first + 9), cursor_bearing_);
	read(*(first + 10), range_scale_);
	read(*(first + 11), range_unit_);
	read(*(first + 12), display_rotation_);
}

void rsd::set_cursor(double range, double bearing) noexcept
{
	cursor_range_ = range;
	cursor_bearing_ = bearing;
}

void rsd::set_range(double scale, char unit) noexcept
{
	range_scale_ = scale;
	range_unit_ = unit;
}

void rsd::set_1(double range, double bearing, double var_range_marker, double bearing_line)
{
	origin_range_1 = range;
	origin_bearing_1 = bearing;
	variable_range_marker_1 = var_range_marker;
	bearing_line_1 = bearing_line;
}

void rsd::set_2(double range, double bearing, double var_range_marker, double bearing_line)
{
	origin_range_2 = range;
	origin_bearing_2 = bearing;
	variable_range_marker_2 = var_range_marker;
	bearing_line_2 = bearing_line;
}

void rsd::append_data_to(std::string & s) const
{
	append(s, to_string(origin_range_1));
	append(s, to_string(origin_bearing_1));
	append(s, to_string(variable_range_marker_1));
	append(s, to_string(bearing_line_1));
	append(s, to_string(origin_range_2));
	append(s, to_string(origin_bearing_2));
	append(s, to_string(variable_range_marker_2));
	append(s, to_string(bearing_line_2));
	append(s, to_string(cursor_range_));
	append(s, to_string(cursor_bearing_));
	append(s, to_string(range_scale_));
	append(s, to_string(range_unit_));
	append(s, to_string(display_rotation_));
}
}
}
