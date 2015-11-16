#include "io.hpp"
#include <sstream>
#include <marnav/nmea/angle.hpp>
#include <marnav/nmea/date.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/utils/mmsi.hpp>
#include <marnav/utils/unused.hpp>

namespace marnav
{
namespace nmea
{

std::string to_string(char data)
{
	char buf[sizeof(int)]; // sizeof(int) is for stack anlignment and protection
	snprintf(buf, sizeof(buf), "%c", data);
	return buf;
}

std::string to_string(uint64_t data) { return std::to_string(data); }

std::string to_string(uint32_t data) { return std::to_string(data); }

std::string to_string(int32_t data) { return std::to_string(data); }

std::string to_string(double data)
{
	char buf[32];
	snprintf(buf, sizeof(buf), "%g", data);
	return buf;
}

std::string to_string(const std::string & data) { return data; }

std::string to_string(side t)
{
	switch (t) {
		case side::left:
			return "L";
		case side::right:
			return "R";
	}
	return ""; // never reached, gcc does not get it, prevents compiler warning
}

std::string to_string(route t)
{
	switch (t) {
		case route::complete:
			return "c";
		case route::working:
			return "w";
	}
	return ""; // never reached, gcc does not get it, prevents compiler warning
}

std::string to_string(selection_mode t)
{
	switch (t) {
		case selection_mode::manual:
			return "M";
		case selection_mode::automatic:
			return "A";
	}
	return ""; // never reached, gcc does not get it, prevents compiler warning
}

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

std::string to_string(direction t)
{
	switch (t) {
		case direction::north:
			return "N";
		case direction::south:
			return "S";
		case direction::east:
			return "E";
		case direction::west:
			return "W";
	}
	return ""; // never reached, gcc does not get it, prevents compiler warning
}

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

std::string to_string(positioning_system_mode_indicator t)
{
	switch (t) {
		case positioning_system_mode_indicator::invalid:
			return "V";
		case positioning_system_mode_indicator::autonomous:
			return "A";
		case positioning_system_mode_indicator::differential:
			return "D";
		case positioning_system_mode_indicator::estimated:
			return "E";
		case positioning_system_mode_indicator::manual_input:
			return "M";
		case positioning_system_mode_indicator::simulated:
			return "S";
		case positioning_system_mode_indicator::data_not_valid:
			return "N";
		case positioning_system_mode_indicator::precise:
			return "P";
	}
	return ""; // never reached, gcc does not get it, prevents compiler warning
}

std::string to_string(status t)
{
	switch (t) {
		case status::ok:
			return "A";
		case status::warning:
			return "V";
	}
	return ""; // never reached, gcc does not get it, prevents compiler warning
}

std::string to_string(quality t)
{
	switch (t) {
		case quality::invalid:
			return "0";
		case quality::gps_fix:
			return "1";
		case quality::dgps_fix:
			return "2";
		case quality::guess:
			return "6";
		case quality::simulation:
			return "8";
	}
	return ""; // never reached, gcc does not get it, prevents compiler warning
}

std::string to_string(unit::distance t)
{
	switch (t) {
		case unit::distance::meter:
			return "M";
		case unit::distance::feet:
			return "f";
		case unit::distance::nm:
			return "N";
		case unit::distance::km:
			return "K";
		case unit::distance::fathom:
			return "F";
	}
	return ""; // never reached, gcc does not get it, prevents compiler warning
}

std::string to_string(unit::velocity t)
{
	switch (t) {
		case unit::velocity::knot:
			return "N";
		case unit::velocity::kmh:
			return "K";
		case unit::velocity::mps:
			return "M";
	}
	return ""; // never reached, gcc does not get it, prevents compiler warning
}

std::string to_string(unit::temperature t)
{
	switch (t) {
		case unit::temperature::celsius:
			return "C";
	}
	return ""; // never reached, gcc does not get it, prevents compiler warning
}

std::string to_string(unit::pressure t)
{
	switch (t) {
		case unit::pressure::bar:
			return "B";
		case unit::pressure::pascal:
			return "P";
	}
	return ""; // never reached, gcc does not get it, prevents compiler warning
}

std::string to_string(const utils::mmsi & t)
{
	char buf[16];
	snprintf(buf, sizeof(buf), "%09u", static_cast<uint32_t>(t));
	return buf;
}

std::string format(int32_t data, unsigned int width, data_format f)
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

std::string format(uint64_t data, unsigned int width, data_format f)
{
	// buffer to hold the resulting string with a static size.
	// this construct prevents VLA, and should be replaced with C++14 dynarray
	char buf[64];
	if (width >= sizeof(buf))
		throw std::invalid_argument{"width too large in nmea::format"};

	char fmt[8];
	switch (f) {
		case data_format::none:
		case data_format::dec:
			snprintf(fmt, sizeof(fmt), "%%0%ulu", width);
			break;
		case data_format::hex:
			snprintf(fmt, sizeof(fmt), "%%0%ulx", width);
			break;
	}
	snprintf(buf, sizeof(buf), fmt, data);
	return buf;
}

std::string format(uint32_t data, unsigned int width, data_format f)
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

std::string format(double data, unsigned int width, data_format f)
{
	utils::unused(f);

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

void read(const std::string & s, geo::latitude & value, data_format fmt)
{
	utils::unused(fmt);

	if (s.empty()) {
		value = geo::latitude{};
		return;
	}

	value = parse_latitude(s);
}

void read(const std::string & s, geo::longitude & value, data_format fmt)
{
	utils::unused(fmt);

	if (s.empty()) {
		value = geo::longitude{};
		return;
	}

	value = parse_longitude(s);
}

void read(const std::string & s, date & value, data_format fmt)
{
	utils::unused(fmt);
	std::istringstream{s} >> value;
}

void read(const std::string & s, time & value, data_format fmt)
{
	utils::unused(fmt);
	std::istringstream{s} >> value;
}

void read(const std::string & s, duration & value, data_format fmt)
{
	utils::unused(fmt);
	std::istringstream{s} >> value;
}

void read(const std::string & s, char & value, data_format fmt)
{
	utils::unused(fmt);
	std::istringstream{s} >> value;
}

void read(const std::string & s, uint64_t & value, data_format fmt)
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

void read(const std::string & s, double & value, data_format fmt)
{
	utils::unused(fmt);
	std::istringstream{s} >> value;
}

void read(const std::string & s, std::string & value, data_format fmt)
{
	utils::unused(fmt);
	value = s;
}

void read(const std::string & s, side & value, data_format fmt)
{
	typename std::underlying_type<side>::type t;
	read(s, t, fmt);
	switch (t) {
		case 'L':
			value = side::left;
			break;
		case 'R':
			value = side::right;
			break;
		default:
			throw std::runtime_error{"invalid data for nmea/side"};
	}
}

void read(const std::string & s, route & value, data_format fmt)
{
	typename std::underlying_type<route>::type t;
	read(s, t, fmt);
	switch (t) {
		case 'c':
			value = route::complete;
			break;
		case 'w':
			value = route::working;
			break;
		default:
			throw std::runtime_error{"invalid data for nmea/route"};
	}
}

void read(const std::string & s, selection_mode & value, data_format fmt)
{
	typename std::underlying_type<selection_mode>::type t;
	read(s, t, fmt);
	switch (t) {
		case 'M':
			value = selection_mode::manual;
			break;
		case 'A':
			value = selection_mode::automatic;
			break;
		default:
			throw std::runtime_error{"invalid data for nmea/selection_mode"};
	}
}

void read(const std::string & s, ais_channel & value, data_format fmt)
{
	typename std::underlying_type<ais_channel>::type t;
	read(s, t, fmt);
	switch (t) {
		case '1':
		case 'A':
			value = ais_channel::A;
			break;
		case '2':
		case 'B':
			value = ais_channel::B;
			break;
		default:
			throw std::runtime_error{"invalid data for nmea/ais_channel"};
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
			throw std::runtime_error{"invalid data for nmea/type_of_point"};
	}
}

void read(const std::string & s, direction & value, data_format fmt)
{
	typename std::underlying_type<direction>::type t;
	read(s, t, fmt);
	switch (t) {
		case 'N':
			value = direction::north;
			break;
		case 'S':
			value = direction::south;
			break;
		case 'E':
			value = direction::east;
			break;
		case 'W':
			value = direction::west;
			break;
		default:
			throw std::runtime_error{"invalid data for nmea/direction"};
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
			throw std::runtime_error{"invalid data for nmea/reference"};
	}
}

void read(const std::string & s, positioning_system_mode_indicator & value, data_format fmt)
{
	typename std::underlying_type<positioning_system_mode_indicator>::type t;
	read(s, t, fmt);
	switch (t) {
		case 'V':
			value = positioning_system_mode_indicator::invalid;
			break;
		case 'A':
			value = positioning_system_mode_indicator::autonomous;
			break;
		case 'D':
			value = positioning_system_mode_indicator::differential;
			break;
		case 'E':
			value = positioning_system_mode_indicator::estimated;
			break;
		case 'M':
			value = positioning_system_mode_indicator::manual_input;
			break;
		case 'S':
			value = positioning_system_mode_indicator::simulated;
			break;
		case 'N':
			value = positioning_system_mode_indicator::data_not_valid;
			break;
		case 'P':
			value = positioning_system_mode_indicator::precise;
			break;
		default:
			throw std::runtime_error{"invalid data for nmea/positioning_system_mode_indicator"};
	}
}

void read(const std::string & s, status & value, data_format fmt)
{
	typename std::underlying_type<status>::type t;
	read(s, t, fmt);
	switch (t) {
		case 'A':
			value = status::ok;
			break;
		case 'V':
			value = status::warning;
			break;
		default:
			throw std::runtime_error{"invalid data for nmea/status"};
	}
}

void read(const std::string & s, quality & value, data_format fmt)
{
	typename std::underlying_type<quality>::type t;
	read(s, t, fmt);
	switch (t) {
		case 0:
			value = quality::invalid;
			break;
		case 1:
			value = quality::gps_fix;
			break;
		case 2:
			value = quality::dgps_fix;
			break;
		case 6:
			value = quality::guess;
			break;
		case 8:
			value = quality::simulation;
			break;
		default:
			throw std::runtime_error{"invalid data for nmea/quality"};
	}
}

void read(const std::string & s, unit::distance & value, data_format fmt)
{
	typename std::underlying_type<unit::distance>::type t;
	read(s, t, fmt);
	switch (t) {
		case 'M':
			value = unit::distance::meter;
			break;
		case 'f':
			value = unit::distance::feet;
			break;
		case 'N':
			value = unit::distance::nm;
			break;
		case 'K':
			value = unit::distance::km;
			break;
		case 'F':
			value = unit::distance::fathom;
			break;
		default:
			throw std::runtime_error{"invalid data for nmea/unit/distance"};
	}
}

void read(const std::string & s, unit::velocity & value, data_format fmt)
{
	typename std::underlying_type<unit::velocity>::type t;
	read(s, t, fmt);
	switch (t) {
		case 'N':
			value = unit::velocity::knot;
			break;
		case 'K':
			value = unit::velocity::kmh;
			break;
		case 'M':
			value = unit::velocity::mps;
			break;
		default:
			throw std::runtime_error{"invalid data for nmea/unit/velocity"};
	}
}

void read(const std::string & s, unit::temperature & value, data_format fmt)
{
	typename std::underlying_type<unit::temperature>::type t;
	read(s, t, fmt);
	switch (t) {
		case 'C':
			value = unit::temperature::celsius;
			break;
		default:
			throw std::runtime_error{"invalid data for nmea/unit/temperature"};
	}
}

void read(const std::string & s, unit::pressure & value, data_format fmt)
{
	typename std::underlying_type<unit::pressure>::type t;
	read(s, t, fmt);
	switch (t) {
		case 'B':
			value = unit::pressure::bar;
			break;
		case 'P':
			value = unit::pressure::pascal;
			break;
		default:
			throw std::runtime_error{"invalid data for nmea/unit/pressure"};
	}
}

void read(const std::string & s, utils::mmsi & value, data_format fmt)
{
	typename utils::mmsi::value_type t;
	read(s, t, fmt);
	value = utils::mmsi{t};
}
}
}
