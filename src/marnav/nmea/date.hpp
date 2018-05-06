#ifndef MARNAV__NMEA__DATE__HPP
#define MARNAV__NMEA__DATE__HPP

#include <string>

#include <marnav/marnav_export.h>

namespace marnav
{
namespace nmea
{

/// Enumeration of all months of a year.
enum class MARNAV_EXPORT month : uint32_t {
	january = 1,
	february,
	march,
	april,
	may,
	june,
	july,
	august,
	september,
	october,
	november,
	december
};

/// This class represents a date, suitable to be used in NMEA sentences.
///
class MARNAV_EXPORT date
{
public:
	date();
	date(uint32_t y, month m, uint32_t d);

	/// Returns the year component.
	uint32_t year() const noexcept;

	/// Returns the month component.
	month mon() const noexcept;

	/// Returns the day component.
	uint32_t day() const noexcept;

	friend MARNAV_EXPORT bool operator==(const date & a, const date & b) noexcept;

	/// Parses the date within the specified string.
	/// The date to be parsed must be in the form: "DDMMYY"
	static date parse(const std::string & str);

	/// Returns true if the specified year is a leap year. This function
	/// does not work for dates before 17?? (only for julian calendar).
	///
	/// Every fourth year is a leap year except for every 100 years,
	/// except every 400 years.
	static constexpr bool is_leap_year(uint32_t year) noexcept
	{
		return ((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0));
	}

private:
	bool check() const noexcept;

	uint32_t y_; // year
	month m_;
	uint32_t d_; // day: 1..31
};

MARNAV_EXPORT bool operator==(const date & a, const date & b) noexcept;
MARNAV_EXPORT std::string to_string(const date & d);
}
}

#endif
