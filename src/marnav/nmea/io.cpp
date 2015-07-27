#include "io.hpp"
#include "angle.hpp"
#include "date.hpp"
#include "time.hpp"
#include <sstream>

namespace marnav
{
namespace nmea
{

std::string to_string(char data)
{
	char buf[3];
	snprintf(buf, sizeof(buf), "%c", data);
	return buf;
}

std::string to_string(uint32_t data) { return std::to_string(data); }

std::string to_string(double data)
{
	char buf[32];
	snprintf(buf, sizeof(buf), "%g", data);
	return buf;
}

std::string to_string(const std::string & data) { return data; }

/// @todo Replace the switch with variable templates as soon as C++14 happens
std::string to_string(side t)
{
	switch (t) {
		case side::LEFT:
			return "L";
		case side::RIGHT:
			return "R";
	}
	return ""; // never reached, gcc does not get it, prevents compiler warning
}

/// @todo Replace the switch with variable templates as soon as C++14 happens
std::string to_string(route t)
{
	switch (t) {
		case route::COMPLETE:
			return "c";
		case route::WORKING:
			return "w";
	}
	return ""; // never reached, gcc does not get it, prevents compiler warning
}

/// @todo Replace the switch with variable templates as soon as C++14 happens
std::string to_string(selection_mode t)
{
	switch (t) {
		case selection_mode::MANUAL:
			return "M";
		case selection_mode::AUTOMATIC:
			return "A";
	}
	return ""; // never reached, gcc does not get it, prevents compiler warning
}

/// @todo Replace the switch with variable templates as soon as C++14 happens
std::string to_string(ais_channel t)
{
	switch (t) {
		case ais_channel::A:
			return "A";
		case ais_channel::B:
			return "B";
	}
	return ""; // never reached, gcc does not get it, prevents compiler warning
}

/// @todo Replace the switch with variable templates as soon as C++14 happens
std::string to_string(type_of_point t)
{
	switch (t) {
		case type_of_point::collision:
			return "C";
		case type_of_point::turning_point:
			return "T";
		case type_of_point::reference:
			return "R";
		case type_of_point::wheelover:
			return "W";
	}
	return ""; // never reached, gcc does not get it, prevents compiler warning
}

/// @todo Replace the switch with variable templates as soon as C++14 happens
std::string to_string(direction t)
{
	switch (t) {
		case direction::NORTH:
			return "N";
		case direction::SOUTH:
			return "S";
		case direction::EAST:
			return "E";
		case direction::WEST:
			return "W";
	}
	return ""; // never reached, gcc does not get it, prevents compiler warning
}

/// @todo Replace the switch with variable templates as soon as C++14 happens
std::string to_string(reference t)
{
	switch (t) {
		case reference::TRUE:
			return "T";
		case reference::MAGNETIC:
			return "M";
		case reference::RELATIVE:
			return "R";
	}
	return ""; // never reached, gcc does not get it, prevents compiler warning
}

/// @todo Replace the switch with variable templates as soon as C++14 happens
std::string to_string(positioning_system_mode_indicator t)
{
	switch (t) {
		case positioning_system_mode_indicator::INVALID:
			return "V";
		case positioning_system_mode_indicator::AUTONOMOUS:
			return "A";
		case positioning_system_mode_indicator::DIFFERENTIAL:
			return "D";
		case positioning_system_mode_indicator::ESTIMATED:
			return "E";
		case positioning_system_mode_indicator::MANUAL_INPUT:
			return "M";
		case positioning_system_mode_indicator::SIMULATED:
			return "S";
		case positioning_system_mode_indicator::DATA_NOT_VALID:
			return "N";
		case positioning_system_mode_indicator::PRECISE:
			return "P";
	}
	return ""; // never reached, gcc does not get it, prevents compiler warning
}

/// @todo Replace the switch with variable templates as soon as C++14 happens
std::string to_string(status t)
{
	switch (t) {
		case status::OK:
			return "A";
		case status::WARNING:
			return "V";
	}
	return ""; // never reached, gcc does not get it, prevents compiler warning
}

std::string format(int32_t data, unsigned int width, data_format f) throw(std::invalid_argument)
{
	// buffer to hold the resulting string with a static size.
	// this construct prevents VLA, and should be replaced with C++14 dynarray
	char buf[32];
	if (width >= sizeof(buf))
		throw std::invalid_argument{"width too large in nmea::format"};

	char fmt[8];
	switch (f) {
		case data_format::none:
		case data_format::dec:
			snprintf(fmt, sizeof(fmt), "%%0%ud", width);
			break;
		case data_format::hex:
			snprintf(fmt, sizeof(fmt), "%%0%ux", width);
			break;
	}
	snprintf(buf, sizeof(buf), fmt, data);
	return buf;
}

std::string format(uint32_t data, unsigned int width, data_format f) throw(
	std::invalid_argument)
{
	// buffer to hold the resulting string with a static size.
	// this construct prevents VLA, and should be replaced with C++14 dynarray
	char buf[32];
	if (width >= sizeof(buf))
		throw std::invalid_argument{"width too large in nmea::format"};

	char fmt[8];
	switch (f) {
		case data_format::none:
		case data_format::dec:
			snprintf(fmt, sizeof(fmt), "%%0%uu", width);
			break;
		case data_format::hex:
			snprintf(fmt, sizeof(fmt), "%%0%ux", width);
			break;
	}
	snprintf(buf, sizeof(buf), fmt, data);
	return buf;
}

std::string format(double data, unsigned int width, data_format) throw(std::invalid_argument)
{
	// buffer to hold the resulting string with a static size.
	// this construct prevents VLA, and should be replaced with C++14 dynarray
	char buf[32];
	if (width >= sizeof(buf))
		throw std::invalid_argument{"width too large in nmea::format"};

	char fmt[8];
	snprintf(fmt, sizeof(fmt), "%%.%uf", width);
	snprintf(buf, sizeof(buf), fmt, data);
	return buf;
}

void read(const std::string & s, geo::latitude & value, data_format)
{
	if (s.empty()) {
		value = geo::latitude{};
		return;
	}

	value = parse_latitude(s);
}

void read(const std::string & s, geo::longitude & value, data_format)
{
	if (s.empty()) {
		value = geo::longitude{};
		return;
	}

	value = parse_longitude(s);
}

void read(const std::string & s, date & value, data_format) { std::istringstream{s} >> value; }

void read(const std::string & s, time & value, data_format) { std::istringstream{s} >> value; }

void read(const std::string & s, duration & value, data_format)
{
	std::istringstream{s} >> value;
}

void read(const std::string & s, char & value, data_format) { std::istringstream{s} >> value; }

void read(const std::string & s, uint32_t & value, data_format fmt)
{
	using namespace std;
	switch (fmt) {
		case data_format::none:
		case data_format::dec:
			std::istringstream{s} >> value;
			break;
		case data_format::hex:
			std::istringstream{s} >> std::hex >> value;
			break;
	}
}

void read(const std::string & s, int32_t & value, data_format fmt)
{
	using namespace std;
	switch (fmt) {
		case data_format::none:
		case data_format::dec:
			std::istringstream{s} >> value;
			break;
		case data_format::hex:
			std::istringstream{s} >> std::hex >> value;
			break;
	}
}

void read(const std::string & s, double & value, data_format)
{
	std::istringstream{s} >> value;
}

void read(const std::string & s, std::string & value, data_format) { value = s; }

void read(const std::string & s, side & value, data_format fmt)
{
	typename std::underlying_type<side>::type t;
	read(s, t, fmt);
	switch (t) {
		case 'L':
			value = side::LEFT;
			break;
		case 'R':
			value = side::RIGHT;
			break;
		default:
			value = static_cast<side>(-1); // invalid value on purpose
			break;
	}
}

void read(const std::string & s, route & value, data_format fmt)
{
	typename std::underlying_type<route>::type t;
	read(s, t, fmt);
	switch (t) {
		case 'c':
			value = route::COMPLETE;
			break;
		case 'w':
			value = route::WORKING;
			break;
		default:
			value = static_cast<route>(-1); // invalid value on purpose
			break;
	}
}

void read(const std::string & s, selection_mode & value, data_format fmt)
{
	typename std::underlying_type<selection_mode>::type t;
	read(s, t, fmt);
	switch (t) {
		case 'M':
			value = selection_mode::MANUAL;
			break;
		case 'A':
			value = selection_mode::AUTOMATIC;
			break;
		default:
			value = static_cast<selection_mode>(-1); // invalid value on purpose
			break;
	}
}

void read(const std::string & s, ais_channel & value, data_format fmt)
{
	typename std::underlying_type<ais_channel>::type t;
	read(s, t, fmt);
	switch (t) {
		case 'A':
			value = ais_channel::A;
			break;
		case 'B':
			value = ais_channel::B;
			break;
		default:
			value = static_cast<ais_channel>(-1); // invalid value on purpose
			break;
	}
}

void read(const std::string & s, type_of_point & value, data_format fmt)
{
	typename std::underlying_type<type_of_point>::type t;
	read(s, t, fmt);
	switch (t) {
		case 'C':
			value = type_of_point::collision;
			break;
		case 'T':
			value = type_of_point::turning_point;
			break;
		case 'R':
			value = type_of_point::reference;
			break;
		case 'W':
			value = type_of_point::wheelover;
			break;
		default:
			value = static_cast<type_of_point>(-1); // invalid value on purpose
			break;
	}
}

void read(const std::string & s, direction & value, data_format fmt)
{
	typename std::underlying_type<direction>::type t;
	read(s, t, fmt);
	switch (t) {
		case 'N':
			value = direction::NORTH;
			break;
		case 'S':
			value = direction::SOUTH;
			break;
		case 'E':
			value = direction::EAST;
			break;
		case 'W':
			value = direction::WEST;
			break;
		default:
			value = static_cast<direction>(-1); // invalid value on purpose
			break;
	}
}

void read(const std::string & s, reference & value, data_format fmt)
{
	typename std::underlying_type<reference>::type t;
	read(s, t, fmt);
	switch (t) {
		case 'T':
			value = reference::TRUE;
			break;
		case 'M':
			value = reference::MAGNETIC;
			break;
		case 'R':
			value = reference::RELATIVE;
			break;
		default:
			value = static_cast<reference>(-1); // invalid value on purpose
			break;
	}
}

void read(const std::string & s, positioning_system_mode_indicator & value, data_format fmt)
{
	typename std::underlying_type<positioning_system_mode_indicator>::type t;
	read(s, t, fmt);
	switch (t) {
		case 'V':
			value = positioning_system_mode_indicator::INVALID;
			break;
		case 'A':
			value = positioning_system_mode_indicator::AUTONOMOUS;
			break;
		case 'D':
			value = positioning_system_mode_indicator::DIFFERENTIAL;
			break;
		case 'E':
			value = positioning_system_mode_indicator::ESTIMATED;
			break;
		case 'M':
			value = positioning_system_mode_indicator::MANUAL_INPUT;
			break;
		case 'S':
			value = positioning_system_mode_indicator::SIMULATED;
			break;
		case 'N':
			value = positioning_system_mode_indicator::DATA_NOT_VALID;
			break;
		case 'P':
			value = positioning_system_mode_indicator::PRECISE;
			break;
		default:
			// invalid value on purpose
			value = static_cast<positioning_system_mode_indicator>(-1);
			break;
	}
}

void read(const std::string & s, status & value, data_format fmt)
{
	typename std::underlying_type<status>::type t;
	read(s, t, fmt);
	switch (t) {
		case 'A':
			value = status::OK;
			break;
		case 'V':
			value = status::WARNING;
			break;
		default:
			// invalid value on purpose
			value = static_cast<status>(-1);
			break;
	}
}
}
}
