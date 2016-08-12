#include "string.hpp"
#include <marnav/utils/mmsi.hpp>

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
		case direction::none:
			break;
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

std::string to_string(mode_indicator t)
{
	switch (t) {
		case mode_indicator::invalid:
			return "V";
		case mode_indicator::autonomous:
			return "A";
		case mode_indicator::differential:
			return "D";
		case mode_indicator::estimated:
			return "E";
		case mode_indicator::manual_input:
			return "M";
		case mode_indicator::simulated:
			return "S";
		case mode_indicator::data_not_valid:
			return "N";
		case mode_indicator::precise:
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

std::string to_string(target_status t)
{
	switch (t) {
		case target_status::lost:
			return "L";
		case target_status::query:
			return "Q";
		case target_status::tracking:
			return "T";
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
}
}
