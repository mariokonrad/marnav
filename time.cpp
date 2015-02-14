#include "time.hpp"

namespace nmea
{

time::time()
	: h(0)
	, m(0)
	, s(0)
	, ms(0)
{
}

time::time(uint32_t h, uint32_t m, uint32_t s, uint32_t ms) throw(std::invalid_argument)
	: h(h)
	, m(m)
	, s(s)
	, ms(ms)
{
	// TODO: replace this poor mans time check

	if (h > 23)
		throw std::invalid_argument{"invalid hour in nmea::time"};
	if (m > 59)
		throw std::invalid_argument{"invalid minute in nmea::time"};
	if (s > 59)
		throw std::invalid_argument{"invalid second in nmea::time"};
	if (ms > 999)
		throw std::invalid_argument{"invalid milliseconds in nmea::time"};
}

uint32_t time::hour() const { return h; }

uint32_t time::minutes() const { return m; }

/// Returns the seconds component.
uint32_t time::seconds() const { return s; }

/// Returns the milliseconds component.
uint32_t time::milliseconds() const { return ms; }

std::string to_string(const time& d)
{
	char buf[7];
	snprintf(buf, sizeof(buf), "%02u%02u%02u", d.hour(), d.minutes(), d.seconds());
	return buf;
}

bool operator==(const time& a, const time& b) noexcept
{
	return (&a == &b) || ((a.h == b.h) && (a.m == b.m) && (a.s == b.s) && (a.ms == b.ms));
}

time time::parse(const std::string& str) throw(std::invalid_argument)
{
	try {
		std::size_t pos = 0;
		double t = std::stod(str, &pos);
		if (pos != str.size())
			throw std::invalid_argument{"invalid format for 'double'"};

		const uint32_t h = static_cast<uint32_t>(t / 10000) % 100;
		const uint32_t m = static_cast<uint32_t>(t / 100) % 100;
		const uint32_t s = static_cast<uint32_t>(t) % 100;
		const uint32_t ms = static_cast<uint32_t>(t * 1000) % 1000;
		return time{h, m, s, ms};
	} catch (std::invalid_argument) {
		throw std::invalid_argument{"invalid time format, 'HHMMSS[.mmm]' expected"};
	}
}

std::ostream& operator<<(std::ostream& os, const time& t) { return os << to_string(t); }

std::istream& operator>>(std::istream& is, time& t)
{
	std::string s;
	is >> s;
	t = time::parse(s);
	return is;
}

}
