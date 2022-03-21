#ifndef MARNAV_NMEA_TIME_HPP
#define MARNAV_NMEA_TIME_HPP

#include <chrono>
#include <string>

namespace marnav
{
namespace nmea
{

/// Base class for time related classes.
template <class Traits>
class time_base
{
public:
	time_base(const time_base &) = default;
	time_base & operator=(const time_base &) = default;

	time_base(time_base &&) = default;
	time_base & operator=(time_base &&) = default;

	explicit time_base(uint32_t h = 0, uint32_t m = 0, uint32_t s = 0, uint32_t ms = 0)
		: h_(h)
		, m_(m)
		, s_(s)
		, ms_(ms)
	{
		Traits::check(h_, m_, s_, ms_);
	}

	/// Returns the hour component.
	uint32_t hour() const noexcept { return h_; }

	/// Returns the minutes component.
	uint32_t minutes() const noexcept { return m_; }

	/// Returns the seconds component.
	uint32_t seconds() const noexcept { return s_; }

	/// Returns the milliseconds component.
	uint32_t milliseconds() const noexcept { return ms_; }

	template <class T>
	bool operator==(const time_base<T> & other) const noexcept
	{
		return (this == &other)
			|| ((h_ == other.h_) && (m_ == other.m_) && (s_ == other.s_) && (ms_ == other.ms_));
	}

	template <class T>
	bool operator!=(const time_base<T> & other) const noexcept
	{
		return !(*this == other);
	}

private:
	uint32_t h_ = 0; // hour: 0..23
	uint32_t m_ = 0; // minute: 0..59
	uint32_t s_ = 0; // second: 0..59
	uint32_t ms_ = 0; // millisecond: 0..999
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

	duration(std::chrono::milliseconds d);

	std::chrono::milliseconds chrono() const;

	static duration parse(const std::string & str);
};

std::string to_string(const duration & d);

/// Duration cast from nmea::duration to std::chrono::duration.
///
/// @param[in] d Duration to convert.
/// @return The std::chrono::duration specified by the template parameter.
template <class ToDuration>
constexpr ToDuration duration_cast(const duration & d)
{
	return std::chrono::duration_cast<ToDuration>(d.chrono());
}
}
}

#endif
