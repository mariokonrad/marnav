#include <marnav/nmea/time.hpp>
#include <stdexcept>

namespace marnav
{
namespace nmea
{

/// @cond DEV
namespace
{
template <class T>
static T parse_time(const std::string & str)
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
		return T{h, m, s, ms};
	} catch (std::invalid_argument &) {
		throw std::invalid_argument{"invalid format, 'HHMMSS[.mmm]' expected"};
	}
}
}
/// @endcond

void trait_time::check(uint32_t h, uint32_t m, uint32_t s, uint32_t ms)
{
	if (h > 23)
		throw std::invalid_argument{"invalid hour in nmea::time"};
	if (m > 59)
		throw std::invalid_argument{"invalid minute in nmea::time"};
	if (s > 59)
		throw std::invalid_argument{"invalid second in nmea::time"};
	if (ms > 999)
		throw std::invalid_argument{"invalid milliseconds in nmea::time"};
}

void trait_duration::check(uint32_t h, uint32_t m, uint32_t s, uint32_t ms)
{
	if (h > 99)
		throw std::invalid_argument{"invalid hour in nmea::duration"};
	if (m > 59)
		throw std::invalid_argument{"invalid minute in nmea::duration"};
	if (s > 59)
		throw std::invalid_argument{"invalid second in nmea::duration"};
	if (ms > 999)
		throw std::invalid_argument{"invalid milliseconds in nmea::duration"};
}

/// Parses the time information within the specified string (start and end of string).
/// If the string is empty, the result will be initialized to zero.
/// The time to be parsed must  be in the form: "HHMMSS.mmm" (milliseconds are optional).
///  - HH  : zero leading hour of the day (00..23)
///  - MM  : zero leading minute of the hour (00..59)
///  - SS  : zero leading second of the minute (00..59)
///  - mmm : milliseconds (000..999)
///
/// @param[in] str The string to parse.
/// @return The parsed time.
/// @exception std::invalid_argument Thrown if the string is malformed.
time time::parse(const std::string & str)
{
	return parse_time<time>(str);
}

/// Returns a string representation in the form 'hhmmss', or ir the specified time has
/// milliseconds other than 0, is provides the form 'hhmmss.sss`.
std::string to_string(const time & t)
{
	char buf[32];
	if (t.milliseconds()) {
		snprintf(buf, sizeof(buf), "%02u%02u%02u.%03u", t.hour(), t.minutes(), t.seconds(),
			t.milliseconds());
	} else {
		snprintf(buf, sizeof(buf), "%02u%02u%02u", t.hour(), t.minutes(), t.seconds());
	}
	return buf;
}

/// Returns the data as formatted string.
///
/// @param[in] t The data to format.
/// @param[in] width Number of digits for sub-seconds. Since sub-seconds
///   are represented as milliseconds in nmea::time, this value can be between 1 and 3.
///   If the value is \c 0, the function \c to_string will be used. Values greater
///   than 3 are equivalent to 3.
std::string format(const nmea::time & t, unsigned int width)
{
	if (width == 0)
		return to_string(t);
	if (width > 3)
		width = 3;

	char fmt[32];
	snprintf(fmt, sizeof(fmt), "%%02u%%02u%%02u.%%0%uu", width);
	uint32_t div = 1;
	for (unsigned int i = 0; i < width; ++i)
		div *= 10;
	char buf[64];
	snprintf(buf, sizeof(buf), fmt, t.hour(), t.minutes(), t.seconds(), t.milliseconds() / div);
	return buf;
}

namespace
{
static constexpr uint32_t to_hours(std::chrono::milliseconds & d) noexcept
{
	return std::chrono::duration_cast<std::chrono::hours>(d).count();
}

static constexpr uint32_t to_minutes(std::chrono::milliseconds d) noexcept
{
	return (std::chrono::duration_cast<std::chrono::minutes>(d)
		% std::chrono::duration_cast<std::chrono::minutes>(std::chrono::hours{1}).count())
		.count();
}

static constexpr uint32_t to_seconds(std::chrono::milliseconds d) noexcept
{
	return (std::chrono::duration_cast<std::chrono::seconds>(d)
		% std::chrono::duration_cast<std::chrono::seconds>(std::chrono::minutes{1}).count())
		.count();
}

static constexpr uint32_t to_milliseconds(std::chrono::milliseconds d) noexcept
{
	return (std::chrono::duration_cast<std::chrono::milliseconds>(d)
		% std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::seconds{1})
			  .count())
		.count();
}
}

/// Initialization through conversion from std::chrono.
///
/// Implicit conversion from std::chrono::duration.
duration::duration(std::chrono::milliseconds d)
	: time_base(to_hours(d), to_minutes(d), to_seconds(d), to_milliseconds(d))
{
}

std::chrono::milliseconds duration::chrono() const
{
	return std::chrono::hours(hour()) + std::chrono::minutes(minutes())
		+ std::chrono::seconds(seconds()) + std::chrono::milliseconds(milliseconds());
}

/// Parses the duration information within the specified string (start and end of string).
/// If the string is empty, the result will be initialized to zero.
/// The duration to be parsed must  be in the form: "HHMMSS.mmm" (milliseconds are optional).
///  - HH  : zero leading hour of the day (00..99)
///  - MM  : zero leading minute of the hour (00..59)
///  - SS  : zero leading second of the minute (00..59)
///  - mmm : milliseconds (000..999)
///
/// @param[in] str The string to parse.
/// @return The parsed duration
/// @exception std::invalid_argument Thrown if the string is malformed.
duration duration::parse(const std::string & str)
{
	return parse_time<duration>(str);
}

/// Returns a string representation in the form 'hhmmss', does not render fractions of seconds.
std::string to_string(const duration & d)
{
	char buf[7];
	snprintf(buf, sizeof(buf), "%02u%02u%02u", d.hour(), d.minutes(), d.seconds());
	return buf;
}
}
}
