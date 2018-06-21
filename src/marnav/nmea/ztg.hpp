#ifndef MARNAV__NMEA__ZTG__HPP
#define MARNAV__NMEA__ZTG__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief ZTG - UTC & Time to Destination Waypoint
///
/// @code
///        1         2         3
///        |         |         |
/// $--ZTG,hhmmss.ss,hhmmss.ss,c--c*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Universal Time Coordinated (UTC)
/// 2. Time Remaining
/// 3. Destination Waypoint ID
///
class ztg : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::ZTG;
	constexpr static const char * TAG = "ZTG";

	ztg();
	ztg(const ztg &) = default;
	ztg & operator=(const ztg &) = default;
	ztg(ztg &&) = default;
	ztg & operator=(ztg &&) = default;

protected:
	ztg(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<nmea::time> time_utc_;
	utils::optional<nmea::time> time_remaining_;
	utils::optional<waypoint> waypoint_id_;

public:
	decltype(time_utc_) get_time_utc() const { return time_utc_; }
	decltype(time_remaining_) get_time_remaining() const { return time_remaining_; }
	decltype(waypoint_id_) get_waypoint_id() const { return waypoint_id_; }

	void set_time_utc(const nmea::time & t) noexcept { time_utc_ = t; }
	void set_time_remaining(const nmea::time & t) noexcept { time_remaining_ = t; }
	void set_waypoint_id(const waypoint & id) { waypoint_id_ = id; }
};
}
}

#endif
