#ifndef __NMEA__ZFO__HPP__
#define __NMEA__ZFO__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(zfo)

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
class zfo : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(zfo)

public:
	constexpr static const sentence_id ID = sentence_id::ZFO;
	constexpr static const char * TAG = "ZFO";

	virtual ~zfo() {}

	zfo();
	zfo(const zfo &) = default;
	zfo & operator=(const zfo &) = default;

protected:
	zfo(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<nmea::time> time_utc;
	utils::optional<nmea::duration> time_elapsed;
	utils::optional<waypoint> waypoint_id;

public:
	NMEA_GETTER(time_utc)
	NMEA_GETTER(time_elapsed)
	NMEA_GETTER(waypoint_id)

	void set_time_utc(const nmea::time & t) noexcept { time_utc = t; }
	void set_time_elapsed(const nmea::duration & t) noexcept { time_elapsed = t; }
	void set_waypoint_id(const waypoint & id) { waypoint_id = id; }
};
}
}

#endif
