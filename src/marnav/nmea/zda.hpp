#ifndef MARNAV__NMEA__ZDA__HPP
#define MARNAV__NMEA__ZDA__HPP

#include <marnav/nmea/sentence.hpp>
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
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::ZDA;
	constexpr static const char * TAG = "ZDA";

	zda();
	zda(const zda &) = default;
	zda & operator=(const zda &) = default;
	zda(zda &&) = default;
	zda & operator=(zda &&) = default;

protected:
	zda(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<nmea::time> time_utc_;
	utils::optional<uint32_t> day_;
	utils::optional<uint32_t> month_;
	utils::optional<uint32_t> year_;
	utils::optional<int32_t> local_zone_hours_;
	utils::optional<int32_t> local_zone_minutes_;

public:
	decltype(time_utc_) get_time_utc() const { return time_utc_; }
	decltype(day_) get_day() const { return day_; }
	decltype(month_) get_month() const { return month_; }
	decltype(year_) get_year() const { return year_; }
	decltype(local_zone_hours_) get_local_zone_hours() const { return local_zone_hours_; }
	decltype(local_zone_minutes_) get_local_zone_minutes() const { return local_zone_minutes_; }

	void set_time_utc(const nmea::time & t) noexcept { time_utc_ = t; }
	void set_date(uint32_t y, uint32_t m, uint32_t d) noexcept
	{
		year_ = y;
		month_ = m;
		day_ = d;
	}
	void set_local_zone(int32_t h, int32_t m) noexcept
	{
		local_zone_hours_ = h;
		local_zone_minutes_ = m;
	}
};
}
}

#endif
