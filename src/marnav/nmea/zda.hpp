#ifndef __NMEA__ZDA__HPP__
#define __NMEA__ZDA__HPP__

#include "sentence.hpp"
#include <marnav/nmea/time.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief ZDA - Time & Date - UTC, day, month, year and local time zone
///
/// @code
///        1         2  3  4    5  6
///        |         |  |  |    |  |
/// $--ZDA,hhmmss.ss,xx,xx,xxxx,xx,xx*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. UTC time (hours, minutes, seconds, may have fractional subsecond)
/// 2. Day, 01 to 31
/// 3. Month, 01 to 12
/// 4. Year (4 digits)
/// 5. Local zone description, 00 to +- 13 hours
/// 6. Local zone minutes description, apply same sign as local hours
///
/// Example: <tt>$GPZDA,160012.71,11,03,2004,-1,00*7D</tt>
///
class zda : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::ZDA;
	constexpr static const char * TAG = "ZDA";

	zda();
	zda(const zda &) = default;
	zda & operator=(const zda &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<nmea::time> time_utc;
	utils::optional<uint32_t> day;
	utils::optional<uint32_t> month;
	utils::optional<uint32_t> year;
	utils::optional<int32_t> local_zone_hours;
	utils::optional<int32_t> local_zone_minutes;

public:
	NMEA_GETTER(time_utc)
	NMEA_GETTER(day)
	NMEA_GETTER(month)
	NMEA_GETTER(year)
	NMEA_GETTER(local_zone_hours)
	NMEA_GETTER(local_zone_minutes)

	void set_time_utc(const nmea::time & t) { time_utc = t; }
	void set_date(uint32_t y, uint32_t m, uint32_t d)
	{
		year = y;
		month = m;
		day = d;
	}
	void set_local_zone(int32_t h, int32_t m)
	{
		local_zone_hours = h;
		local_zone_minutes = m;
	}
};
}
}

#endif
