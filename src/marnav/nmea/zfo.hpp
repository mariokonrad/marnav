#ifndef MARNAV__NMEA__ZFO__HPP
#define MARNAV__NMEA__ZFO__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/utils/optional.hpp>

#include <marnav/marnav_export.h>

namespace marnav
{
namespace nmea
{
/// @brief ZFO - UTC & Time from origin Waypoint
///
/// @code
///        1         2         3
///        |         |         |
/// $--ZFO,hhmmss.ss,hhmmss.ss,c--c*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Universal Time Coordinated (UTC)
/// 2. Elapsed Time
/// 3. Origin Waypoint ID
///
class MARNAV_EXPORT zfo : public sentence
{
	friend class detail::factory;

public:
	constexpr static const sentence_id ID = sentence_id::ZFO;
	constexpr static const char * TAG = "ZFO";

	zfo();
	zfo(const zfo &) = default;
	zfo & operator=(const zfo &) = default;
	zfo(zfo &&) = default;
	zfo & operator=(zfo &&) = default;

protected:
	zfo(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif
	utils::optional<nmea::time> time_utc_;
	utils::optional<nmea::duration> time_elapsed_;
	utils::optional<waypoint> waypoint_id_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

public:
	decltype(time_utc_) get_time_utc() const { return time_utc_; }
	decltype(time_elapsed_) get_time_elapsed() const { return time_elapsed_; }
	decltype(waypoint_id_) get_waypoint_id() const { return waypoint_id_; }

	void set_time_utc(const nmea::time & t) noexcept { time_utc_ = t; }
	void set_time_elapsed(const nmea::duration & t) noexcept { time_elapsed_ = t; }
	void set_waypoint_id(const waypoint & id) { waypoint_id_ = id; }
};
}
}

#endif
