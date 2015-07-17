#ifndef __NMEA__ZFO__HPP__
#define __NMEA__ZFO__HPP__

#include "sentence.hpp"
#include <marnav/nmea/time.hpp>
#include <marnav/utils/optional.hpp>

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
class zfo : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::ZFO;
	constexpr static const char * TAG = "ZFO";

	zfo();
	zfo(const zfo &) = default;
	zfo & operator=(const zfo &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<nmea::time> time_utc;
	utils::optional<nmea::duration> time_elapsed;
	utils::optional<std::string> waypoint_id;

public:
	decltype(time_utc) get_time_utc() const { return time_utc; }
	decltype(time_elapsed) get_time_elapsed() const { return time_elapsed; }
	decltype(waypoint_id) get_waypoint_id() const { return waypoint_id; }

	void set_time_utc(const nmea::time & t) { time_utc = t; }
	void set_time_elapsed(const nmea::duration & t) { time_elapsed = t; }
	void set_waypoint_id(const std::string & id);
};
}
}

#endif
