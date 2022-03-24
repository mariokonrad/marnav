#ifndef MARNAV_NMEA_ZLZ_HPP
#define MARNAV_NMEA_ZLZ_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>

namespace marnav
{
namespace nmea
{
/// @brief ZLZ - Time of Day
///
/// @code
///        1         2         3
///        |         |         |
/// $--ZLZ,hhmmss.ss,hhmmss.ss,xx*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Universal Time Coordinated (UTC)
/// 2. Local Time
/// 3. Local Zone Description, number of whole hours added to local time to obtain GMT,
///    range -12..+12
///
class zlz : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::ZLZ;
	constexpr static const char * TAG = "ZLZ";

	zlz();
	zlz(const zlz &) = default;
	zlz & operator=(const zlz &) = default;
	zlz(zlz &&) = default;
	zlz & operator=(zlz &&) = default;

protected:
	zlz(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	nmea::time time_utc_;
	nmea::time time_local_;
	int32_t local_zone_description_ = 0;

public:
	nmea::time get_time_utc() const { return time_utc_; }
	nmea::time get_time_local() const { return time_local_; }
	int32_t get_local_zone_description() const { return local_zone_description_; }

	void set_time_utc(const nmea::time & t) noexcept { time_utc_ = t; }
	void set_time_local(const nmea::time & t) noexcept { time_local_ = t; }
	void set_local_zone_description(int32_t t);
};
}
}

#endif
