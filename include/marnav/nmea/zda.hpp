#ifndef MARNAV_NMEA_ZDA_HPP
#define MARNAV_NMEA_ZDA_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/date.hpp>
#include <marnav/nmea/time.hpp>
#include <optional>

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
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<nmea::time> time_utc_;
	std::optional<nmea::date> date_;
	std::optional<int32_t> local_zone_hours_;
	std::optional<int32_t> local_zone_minutes_;

public:
	std::optional<nmea::time> get_time_utc() const { return time_utc_; }
	std::optional<nmea::date> get_date() const { return date_; }
	std::optional<int32_t> get_local_zone_hours() const { return local_zone_hours_; }
	std::optional<int32_t> get_local_zone_minutes() const { return local_zone_minutes_; }

	void set_time_utc(const nmea::time & t) noexcept { time_utc_ = t; }
	void set_date(const nmea::date & d) noexcept { date_ = d; }

	void set_local_zone(int32_t h, int32_t m) noexcept
	{
		local_zone_hours_ = h;
		local_zone_minutes_ = m;
	}
};
}
}

#endif
