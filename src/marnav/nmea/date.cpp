#include <marnav/nmea/date.hpp>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
uint32_t to_numeric(month m) noexcept
{
	return static_cast<uint32_t>(m);
}

month to_month(uint32_t m) noexcept
{
	return static_cast<month>(m);
}

date::date()
	: y_(0)
	, m_(month::january)
	, d_(1)
{
}

date::date(uint32_t y, month m, uint32_t d)
	: y_(y)
	, m_(m)
	, d_(d)
{
	if (!check())
		throw std::invalid_argument{"invalid date"};
}

bool date::check() const noexcept
{
	if (d_ == 0)
		return false;

	switch (m_) {
		case month::january:
		case month::march:
		case month::may:
		case month::july:
		case month::august:
		case month::october:
		case month::december:
			return d_ <= 31;

		case month::april:
		case month::june:
		case month::september:
		case month::november:
			return d_ <= 30;

		case month::february:
			if (is_leap_year(y_))
				return d_ <= 29;
			return d_ <= 28;
	}

	return false; // never reached, bad for coverage, supresses compiler warning
}

/// Returns the year component.
uint32_t date::year() const noexcept
{
	return y_;
}

/// Returns the month component.
month date::mon() const noexcept
{
	return m_;
}

/// Returns the day component.
uint32_t date::day() const noexcept
{
	return d_;
}

bool operator==(const date & a, const date & b) noexcept
{
	return (&a == &b) || ((a.y_ == b.y_) && (a.m_ == b.m_) && (a.d_ == b.d_));
}

bool operator!=(const date & a, const date & b) noexcept
{
	return !(a == b);
}

std::string to_string(const date & d)
{
	char buf[7];
	snprintf(buf, sizeof(buf), "%02u%02u%02u", d.day(), static_cast<unsigned int>(d.mon()),
		d.year());
	return buf;
}

date date::parse(const std::string & str)
{
	try {
		std::size_t pos = 0;
		uint32_t t = std::stoul(str, &pos);
		if (pos != str.size())
			throw std::invalid_argument{"invalid format for date"};
		return date{t % 100, static_cast<month>((t / 100) % 100), (t / 10000) % 100};
	} catch (std::invalid_argument &) {
		throw std::invalid_argument{"invalid date format, 'DDMMYY' expected"};
	}
}
}
}
