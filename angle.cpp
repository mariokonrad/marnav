#include "angle.hpp"
#include <cmath>

namespace nmea
{

angle::angle()
	: value(0.0)
{
}

angle::angle(double value)
	: value(value)
{
}

/// Returns the degrees of this angle. This value is always positive.
uint32_t angle::degrees() const
{
	auto a = fabs(get());
	a = floor(a);
	return static_cast<uint32_t>(a);
}

/// Returns the minutes of this angle. This value is always positive
/// and is between 0 and 59.
uint32_t angle::minutes() const
{
	auto a = fabs(get());
	a -= floor(a);
	a *= 60.0;
	a += EPSILON;
	return static_cast<uint32_t>(a);
}

/// Returns the seconds of this angle.
double angle::seconds() const
{
	auto a = fabs(get());
	a -= floor(a);
	a *= 60.0;
	a += EPSILON;
	a -= floor(a);
	a *= 60.0;
	return a;
}

/// Converts an angle to double, units: degrees.
angle::operator double() const { return value; }

double angle::get() const { return value; }

bool operator==(const angle& a, const angle& b) noexcept
{
	return (&a == &b) || (a.value == b.value);
}

angle angle::parse(const std::string& s) throw(std::invalid_argument)
{
	if (s.empty())
		return angle{0.0};
	std::size_t pos = 0;
	auto tmp = std::stod(s, &pos);
	if (pos != s.size())
		throw std::invalid_argument{"invalid string for conversion to nmea::angle"};

	// adoption of NMEA angle DDDMM.SSS to the one that is used here
	const double deg = (tmp - fmod(tmp, 100.0)) / 100.0;
	const double min = (tmp - (deg * 100.0)) / 60.0;

	if (fabs(min) >= 1.0)
		throw std::invalid_argument{"invalid format for minutes in nmea::angle"};

	return angle{deg + min};
}

latitude::latitude()
	: angle(0.0)
{
}

latitude::latitude(double value)
	: angle(value)
{
	check(get());
}

latitude::latitude(uint32_t d, uint32_t m, uint32_t s, hemisphere hem)
	: angle((static_cast<double>(d) + static_cast<double>(m) / 60.0
			 + static_cast<double>(s) / 3600.0) * ((hem == hemisphere::SOUTH) ? -1.0 : 1.0))
{
	check(get());
}

/// Returns the corresponding hemisphere.
latitude::hemisphere latitude::hem() const
{
	return get() >= 0.0 ? hemisphere::NORTH : hemisphere::SOUTH;
}

void latitude::check(double a) throw(std::invalid_argument)
{
	if ((a < -90.0) || (a > 90.0))
		throw std::invalid_argument{"invalid value for nmea::latitude"};
}

std::string to_string(const latitude& v)
{
	char buf[32];
	snprintf(buf, sizeof(buf), "%02u%02u.%04u", v.degrees(), v.minutes(),
			 static_cast<uint32_t>((v.seconds() / 60) * 10000));
	return buf;
}

latitude latitude::parse(const std::string& s) throw(std::invalid_argument)
{
	auto a = angle::parse(s);
	check(a);
	return latitude{a};
}

std::ostream& operator<<(std::ostream& os, const latitude& p) { return os << to_string(p); }

std::istream& operator>>(std::istream& is, latitude& t)
{
	std::string s;
	is >> s;
	t = latitude::parse(s);
	return is;
}

longitude::longitude()
	: angle(0.0)
{
}

longitude::longitude(double value)
	: angle(value)
{
	check(*this);
}

longitude::longitude(uint32_t d, uint32_t m, uint32_t s, hemisphere hem)
	: angle((static_cast<double>(d) + static_cast<double>(m) / 60.0
			 + static_cast<double>(s) / 3600.0) * ((hem == hemisphere::EAST) ? -1.0 : 1.0))
{
	check(*this);
}

/// Returns the corresponding hemisphere.
longitude::hemisphere longitude::hem() const
{
	return get() >= 0.0 ? hemisphere::WEST : hemisphere::EAST;
}

void longitude::check(double a) throw(std::invalid_argument)
{
	if ((a < -180.0) || (a > 180.0))
		throw std::invalid_argument{"invalid value for nmea::longitude"};
}

longitude longitude::parse(const std::string& s) throw(std::invalid_argument)
{
	auto a = angle::parse(s);
	check(a);
	return longitude{a};
}

std::string to_string(const longitude& v)
{
	char buf[32];
	snprintf(buf, sizeof(buf), "%03u%02u.%04u", v.degrees(), v.minutes(),
			 static_cast<uint32_t>(10000 * v.seconds() / 60));
	return buf;
}

std::ostream& operator<<(std::ostream& os, const longitude& p) { return os << to_string(p); }

std::istream& operator>>(std::istream& is, longitude& t)
{
	std::string s;
	is >> s;
	t = longitude::parse(s);
	return is;
}

}

