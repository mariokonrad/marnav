#ifndef __MARNAV__NMEA__TIME__HPP__
#define __MARNAV__NMEA__TIME__HPP__

#include <string>

namespace marnav
{
namespace nmea
{

/// Base class for time related classes.
template <class Traits> class time_base
{
public:
	time_base(const time_base &) = default;
	explicit time_base(uint32_t h = 0, uint32_t m = 0, uint32_t s = 0, uint32_t ms = 0)
		: h(h)
		, m(m)
		, s(s)
		, ms(ms)
	{
		Traits::check(h, m, s, ms);
	}

	/// Returns the hour component.
	uint32_t hour() const { return h; }

	/// Returns the minutes component.
	uint32_t minutes() const { return m; }

	/// Returns the seconds component.
	uint32_t seconds() const { return s; }

	/// Returns the milliseconds component.
	uint32_t milliseconds() const { return ms; }

	template <class T> bool operator==(const time_base<T> & other) noexcept
	{
		return (this == &other)
			|| ((h == other.h) && (m == other.m) && (s == other.s) && (ms == other.ms));
	}

private:
	uint32_t h; // hour: 0..23
	uint32_t m; // minute: 0..59
	uint32_t s; // second: 0..59
	uint32_t ms; // millisecond: 0..999
};

/// Traits to check for the correctness of time.
class trait_time
{
public:
	static void check(uint32_t h, uint32_t m, uint32_t s, uint32_t ms);
};

/// Traits to check for the correctness of duration.
class trait_duration
{
public:
	static void check(uint32_t h, uint32_t m, uint32_t s, uint32_t ms);
};

/// Represents a point in time, suitable for NMEA purposes.
///
/// Ranges of values for parsing:
///  - HH  : zero leading hour of the day (00..23)
///  - MM  : zero leading minute of the hour (00..59)
///  - SS  : zero leading second of the minute (00..59)
///  - mmm : milliseconds (000..999)
class time : public time_base<trait_time>
{
public:
	using time_base::time_base;

	time()
		: time_base(0, 0, 0, 0)
	{
	}

	time(const time &) = default;

	static time parse(const std::string & str);
};

std::string to_string(const time & t);
std::string format(const nmea::time & t, unsigned int width);

/// Represents a duration up to 99 hours/59 minutes/59 seconds, suitable for NMEA purposes.
///
/// Ranges of values for parsing:
///  - HH  : zero leading hour of the day (00..99)
///  - MM  : zero leading minute of the hour (00..59)
///  - SS  : zero leading second of the minute (00..59)
///  - mmm : milliseconds (000..999)
class duration : public time_base<trait_duration>
{
public:
	using time_base::time_base;

	duration()
		: time_base(0, 0, 0, 0)
	{
	}

	duration(const duration &) = default;

	static duration parse(const std::string & str);
};

std::string to_string(const duration & d);
}
}

#endif
