#ifndef MARNAV_NMEA_ZFI_HPP
#define MARNAV_NMEA_ZFI_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/nmea/waypoint.hpp>

namespace marnav
{
namespace nmea
{
/// @brief ZFI - Elapsed time from point of interest
///
/// @code
///        1         2         3
///        |         |         |
/// $--ZFI,hhmmss.ss,hhmmss.ss,c--c*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Time UTC
/// 2. Elapsed time
/// 3. Waypoint ID
///
class zfi : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::ZFI;
	constexpr static const char * TAG = "ZFI";

	zfi();
	zfi(const zfi &) = default;
	zfi & operator=(const zfi &) = default;
	zfi(zfi &&) = default;
	zfi & operator=(zfi &&) = default;

protected:
	zfi(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	nmea::time time_utc_;
	nmea::duration time_elapsed_;
	waypoint waypoint_id_;

public:
	nmea::time get_time_utc() const { return time_utc_; }
	nmea::duration get_time_elapsed() const { return time_elapsed_; }
	waypoint get_waypoint_id() const { return waypoint_id_; }

	void set_time_utc(nmea::time t) noexcept { time_utc_ = t; }
	void set_time_elapsed(nmea::duration t) noexcept { time_elapsed_ = t; }
	void set_waypoint_id(const waypoint & t) { waypoint_id_ = t; }
};
}
}

#endif
