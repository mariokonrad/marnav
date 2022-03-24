#ifndef MARNAV_NMEA_ZTG_HPP
#define MARNAV_NMEA_ZTG_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <optional>

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
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<nmea::time> time_utc_;
	std::optional<nmea::time> time_remaining_;
	std::optional<waypoint> waypoint_id_;

public:
	std::optional<nmea::time> get_time_utc() const { return time_utc_; }
	std::optional<nmea::time> get_time_remaining() const { return time_remaining_; }
	std::optional<waypoint> get_waypoint_id() const { return waypoint_id_; }

	void set_time_utc(const nmea::time & t) noexcept { time_utc_ = t; }
	void set_time_remaining(const nmea::time & t) noexcept { time_remaining_ = t; }
	void set_waypoint_id(const waypoint & id) { waypoint_id_ = id; }
};
}
}

#endif
