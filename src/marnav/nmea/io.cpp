#include <marnav/nmea/io.hpp>
#include <marnav/nmea/angle.hpp>
#include <marnav/nmea/date.hpp>
#include <marnav/nmea/route.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/utils/mmsi.hpp>
#include <marnav/utils/unused.hpp>

#include <algorithm>
#include <iomanip>
#include <limits>
#include <locale>
#include <sstream>
#include <type_traits>

namespace marnav::nmea
{
namespace
{
// Not using snprintf for unsigned integers anymore. Apparently
// it causes propblems on 32bit ARM (toolchain gcc-10) on 64bit
// values.
// This implementation is also faster, although not O(1).
//
// Narrow contract:
// The function assumes the buffer to be large enough to fit
// the data. The caller needs to make sure to also initialize
// the buffer with zeroes.
//
template <std::size_t Base, typename T,
	typename std::enable_if_t<std::is_unsigned_v<T>, void *> = nullptr>
void format_uint(char * buf, std::size_t w, T data) noexcept
{
	static constexpr char tab[] = "0123456789abcdef";
	static_assert(Base <= sizeof(tab));

	std::size_t i = 0u;
	do {
		buf[i] = tab[data % Base];
		++i;
		data /= Base;
	} while (data);
	for (; i < w; ++i)
		buf[i] = '0';
	std::reverse(buf, buf + i);
}
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
	char buf[std::numeric_limits<uint64_t>::digits10 + 1u] = {0};

	if (width >= sizeof(buf))
		throw std::invalid_argument{"width too large in nmea::format"};

	switch (f) {
		case data_format::none:
		case data_format::dec:
			format_uint<10u>(buf, width, data);
			break;
		case data_format::hex:
			format_uint<16u>(buf, width, data);
			break;
	}

	return buf;
}

std::string format(uint32_t data, unsigned int width, data_format f)
{
	char buf[std::numeric_limits<uint32_t>::digits10 + 1u] = {0};

	if (width >= sizeof(buf))
		throw std::invalid_argument{"width too large in nmea::format"};

	switch (f) {
		case data_format::none:
		case data_format::dec:
			format_uint<10u>(buf, width, data);
			break;
		case data_format::hex:
			format_uint<16u>(buf, width, data);
			break;
	}
	return buf;
}

std::string format(double data, unsigned int width, data_format f)
{
	utils::unused(f);

	std::ostringstream os;
	os.imbue(std::locale::classic());
	os << std::setiosflags(std::ios::dec | std::ios::fixed);
	os << std::setprecision(width);
	os << data;
	return os.str();
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
	value = date::parse(s);
}

void read(const std::string & s, time & value, data_format fmt)
{
	utils::unused(fmt);
	value = time::parse(s);
}

void read(const std::string & s, duration & value, data_format fmt)
{
	utils::unused(fmt);
	value = duration::parse(s);
}

void read(const std::string & s, char & value, data_format fmt)
{
	utils::unused(fmt);
	if (s.empty())
		return;
	value = s[0];
}

/// @cond DEV

namespace detail
{
template <typename T>
T sto(const std::string &, std::size_t *, int);

template <>
uint64_t sto(const std::string & s, std::size_t * pos, int base)
{
	return std::stoull(s, pos, base);
}

template <>
uint32_t sto(const std::string & s, std::size_t * pos, int base)
{
	return std::stoul(s, pos, base);
}

template <>
int32_t sto(const std::string & s, std::size_t * pos, int base)
{
	return std::stol(s, pos, base);
}

template <typename T, typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
void read_integer(const std::string & s, T & value, data_format fmt)
{
	if (s.empty())
		return;
	std::size_t pos = 0;
	value = sto<T>(s, &pos, (fmt == data_format::hex) ? 16 : 10);
	if (pos != s.size())
		throw std::runtime_error{"invalid string to convert to number: [" + s + "]"};
}
}

/// @endcond

void read(const std::string & s, uint64_t & value, data_format fmt)
{
	detail::read_integer(s, value, fmt);
}

void read(const std::string & s, uint32_t & value, data_format fmt)
{
	detail::read_integer(s, value, fmt);
}

void read(const std::string & s, uint8_t & value, data_format fmt)
{
	uint32_t tmp = {};
	detail::read_integer(s, tmp, fmt);
	value = tmp;
}

void read(const std::string & s, int32_t & value, data_format fmt)
{
	detail::read_integer(s, value, fmt);
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

void read(const std::string & s, route_mode & value, data_format fmt)
{
	typename std::underlying_type<route_mode>::type t;
	read(s, t, fmt);
	switch (t) {
		case 'c':
			value = route_mode::complete;
			break;
		case 'w':
			value = route_mode::working;
			break;
		default:
			throw std::runtime_error{"invalid data for nmea/route_mode"};
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

void read(const std::string & s, mode_indicator & value, data_format fmt)
{
	typename std::underlying_type<mode_indicator>::type t;
	read(s, t, fmt);
	switch (t) {
		case 'V':
			value = mode_indicator::invalid;
			break;
		case 'A':
			value = mode_indicator::autonomous;
			break;
		case 'D':
			value = mode_indicator::differential;
			break;
		case 'E':
			value = mode_indicator::estimated;
			break;
		case 'M':
			value = mode_indicator::manual_input;
			break;
		case 'S':
			value = mode_indicator::simulated;
			break;
		case 'N':
			value = mode_indicator::data_not_valid;
			break;
		case 'P':
			value = mode_indicator::precise;
			break;
		default:
			throw std::runtime_error{"invalid data for nmea/mode_indicator"};
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

void read(const std::string & s, target_status & value, data_format fmt)
{
	typename std::underlying_type<target_status>::type t;
	read(s, t, fmt);
	switch (t) {
		case 'L':
			value = target_status::lost;
			break;
		case 'Q':
			value = target_status::query;
			break;
		case 'T':
			value = target_status::tracking;
			break;
		default:
			throw std::runtime_error{"invalid data for nmea/target_status"};
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
	typename utils::mmsi::value_type t = utils::mmsi::initial_value;
	read(s, t, fmt);
	value = utils::mmsi{t};
}

void read(const std::string & s, route & value, data_format fmt)
{
	typename route::value_type t;
	read(s, t, fmt);
	value = route{t};
}

void read(const std::string & s, waypoint & value, data_format fmt)
{
	typename waypoint::value_type t;
	read(s, t, fmt);
	value = waypoint{t};
}
}
