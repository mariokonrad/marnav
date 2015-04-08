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
	time();

	time(const time &) = default;

	explicit time(uint32_t h, uint32_t m, uint32_t s, uint32_t ms) throw(std::invalid_argument);

	/// Returns the hour component.
	uint32_t hour() const;

	/// Returns the minutes component.
	uint32_t minutes() const;

	/// Returns the seconds component.
	uint32_t seconds() const;

	/// Returns the milliseconds component.
	uint32_t milliseconds() const;

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
}
}

#endif
