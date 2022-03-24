#ifndef MARNAV_NMEA_ZTE_HPP
#define MARNAV_NMEA_ZTE_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/nmea/waypoint.hpp>

namespace marnav
{
namespace nmea
{
/// @brief ZTE - Estimated time to event
///
/// @code
///        1         2         3
///        |         |         |
/// $--ZTE,hhmmss.ss,hhmmss.ss,c--c*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Time UTC
/// 2. Estimated remaining time
/// 3. Waypoint ID
///
class zte : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::ZTE;
	constexpr static const char * TAG = "ZTE";

	zte();
	zte(const zte &) = default;
	zte & operator=(const zte &) = default;
	zte(zte &&) = default;
	zte & operator=(zte &&) = default;

protected:
	zte(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	nmea::time time_utc_;
	nmea::duration time_remaining_;
	waypoint waypoint_id_;

public:
	nmea::time get_time_utc() const { return time_utc_; }
	nmea::duration get_time_remaining() const { return time_remaining_; }
	waypoint get_waypoint_id() const { return waypoint_id_; }

	void set_time_utc(nmea::time t) noexcept { time_utc_ = t; }
	void set_time_remaining(nmea::duration t) noexcept { time_remaining_ = t; }
	void set_waypoint_id(const waypoint & t) { waypoint_id_ = t; }
};
}
}

#endif
