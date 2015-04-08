#include "date.hpp"

namespace marnav
{
namespace nmea
{

date::date()
	: y(0)
	, m(1)
	, d(1)
{
}

date::date(uint32_t y, uint32_t m, uint32_t d) throw(std::invalid_argument)
	: y(y)
	, m(m)
	, d(d)
{
	if (!check())
		throw std::invalid_argument{"invalid date"};
}

bool date::check() const noexcept
{
	if (d == 0)
		return false;

	switch (m) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return d <= 31;

		case 4:
		case 6:
		case 9:
		case 11:
			return d <= 30;

		case 2:
			if (is_leap_year(y))
				return d <= 29;
			return d <= 28;

		default:
			return false;
	}
}

/// Returns the year component.
uint32_t date::year() const noexcept { return y; }

/// Returns the month component.
uint32_t date::month() const noexcept { return m; }

/// Returns the day component.
uint32_t date::day() const noexcept { return d; }

bool operator==(const date & a, const date & b) noexcept
{
	return (&a == &b) || ((a.y == b.y) && (a.m == b.m) && (a.d == b.d));
}

std::string to_string(const date & d)
{
	char buf[7];
	snprintf(buf, sizeof(buf), "%02u%02u%02u", d.day(), d.month(), d.year());
	return buf;
}

date date::parse(const std::string & str) throw(std::invalid_argument)
{
	try {
		std::size_t pos = 0;
		uint32_t t = std::stoul(str, &pos);
		if (pos != str.size())
			throw std::invalid_argument{"invalid format for date"};
		return date{t % 100, (t / 100) % 100, (t / 10000) % 100};
	} catch (std::invalid_argument) {
		throw std::invalid_argument{"invalid date format, 'DDMMYY' expected"};
	}
}

std::ostream & operator<<(std::ostream & os, const date & d) { return os << to_string(d); }

std::istream & operator>>(std::istream & is, date & d)
{
	std::string s;
	is >> s;
	d = date::parse(s);
	return is;
}
}
}
