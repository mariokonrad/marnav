#ifndef __NMEA__DATE__HPP__
#define __NMEA__DATE__HPP__

#include <string>
#include <stdexcept>

namespace nmea
{

class date
{
public:
	date();

	explicit date(uint32_t y, uint32_t m, uint32_t d) throw(std::invalid_argument);

	/// Returns the year component.
	uint32_t year() const;

	/// Returns the month component.
	uint32_t month() const;

	/// Returns the day component.
	uint32_t day() const;

	friend bool operator==(const date& a, const date& b) noexcept;

	/// Parses the date within the specified string.
	/// The date to be parsed must be in the form: "DDMMYY"
	static date parse(const std::string& str) throw(std::invalid_argument);

private:
	uint32_t y; // year
	uint32_t m; // month: 1..12
	uint32_t d; // day: 1..31
};

bool operator==(const date& a, const date& b) noexcept;
std::string to_string(const date& d);
std::ostream& operator<<(std::ostream& os, const date& d);
std::istream& operator>>(std::istream& is, date& d);

}

#endif
