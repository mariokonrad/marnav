#ifndef __NMEA__TIME__HPP__
#define __NMEA__TIME__HPP__

#include <string>
#include <stdexcept>

namespace marnav
{
namespace nmea
{

class time
{
public:
	time(const time &) = default;

	explicit time(uint32_t h = 0, uint32_t m = 0, uint32_t s = 0, uint32_t ms = 0) throw(
		std::invalid_argument);

	/// Returns the hour component.
	inline uint32_t hour() const { return h; }

	/// Returns the minutes component.
	inline uint32_t minutes() const { return m; }

	/// Returns the seconds component.
	inline uint32_t seconds() const { return s; }

	/// Returns the milliseconds component.
	inline uint32_t milliseconds() const { return ms; }

	friend bool operator==(const time & a, const time & b) noexcept;

	/// Parses the time information within the specified string (start and end of string).
	/// If the string is empty, the result will be initialized to zero.
	/// The time to be parsed must  be in the form: "HHMMSS.mmm" (milliseconds are optional).
	///  - HH  : zero leading hour of the day (00..23)
	///  - MM  : zero leading minute of the hour (00..59)
	///  - SS  : zero leading second of the minute (00..59)
	///  - mmm : milliseconds (000..999)
	///
	/// @param[in] s start of string to parse (inclusive)
	/// @param[in] e end of string to parse (exclusive)
	/// @param[out] endptr Points the end of the parsed string.
	/// @return The parsed time
	static time parse(const std::string & str) throw(std::invalid_argument);

private:
	uint32_t h; // hour: 0..23
	uint32_t m; // minute: 0..59
	uint32_t s; // second: 0..59
	uint32_t ms; // millisecond: 0..999
};

bool operator==(const time & a, const time & b) noexcept;
std::string to_string(const time & d);
std::ostream & operator<<(std::ostream & os, const time & t);
std::istream & operator>>(std::istream & is, time & t);

/// @todo Refactoring of code duplication of time and duration
class duration
{
public:
	duration(const duration&) = default;

	explicit duration(uint32_t h = 0, uint32_t m = 0, uint32_t s = 0, uint32_t ms = 0) throw(
		std::invalid_argument);

	/// Returns the hour component.
	inline uint32_t hour() const { return h; }

	/// Returns the minutes component.
	inline uint32_t minutes() const { return m; }

	/// Returns the seconds component.
	inline uint32_t seconds() const { return s; }

	/// Returns the milliseconds component.
	inline uint32_t milliseconds() const { return ms; }

	friend bool operator==(const duration & a, const duration & b) noexcept;

	/// Parses the duration information within the specified string (start and end of string).
	/// If the string is empty, the result will be initialized to zero.
	/// The duratoin to be parsed must  be in the form: "HHMMSS.mmm" (milliseconds are optional).
	///  - HH  : zero leading hour of the day (00..99)
	///  - MM  : zero leading minute of the hour (00..59)
	///  - SS  : zero leading second of the minute (00..59)
	///  - mmm : milliseconds (000..999)
	///
	/// @param[in] s start of string to parse (inclusive)
	/// @param[in] e end of string to parse (exclusive)
	/// @param[out] endptr Points the end of the parsed string.
	/// @return The parsed duration
	static duration parse(const std::string & str) throw(std::invalid_argument);

private:
	uint32_t h; // hour: 0..23
	uint32_t m; // minute: 0..59
	uint32_t s; // second: 0..59
	uint32_t ms; // millisecond: 0..999
};

bool operator==(const duration & a, const duration & b) noexcept;
std::string to_string(const duration & d);
std::ostream & operator<<(std::ostream & os, const duration & t);
std::istream & operator>>(std::istream & is, duration & t);

}
}

#endif
