#ifndef __NMEA__ZTG__HPP__
#define __NMEA__ZTG__HPP__

#include "sentence.hpp"
#include <marnav/nmea/time.hpp>
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
public:
	constexpr static const sentence_id ID = sentence_id::ZTG;
	constexpr static const char * TAG = "ZTG";

	ztg();
	ztg(const ztg &) = default;
	ztg & operator=(const ztg &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<nmea::time> time_utc;
	utils::optional<nmea::time> time_remaining;
	utils::optional<std::string> waypoint_id;

public:
	NMEA_GETTER(time_utc)
	NMEA_GETTER(time_remaining)
	NMEA_GETTER(waypoint_id)

	void set_time_utc(const nmea::time & t) { time_utc = t; }
	void set_time_remaining(const nmea::time & t) { time_remaining = t; }
	void set_waypoint_id(const std::string & id);
};
}
}

#endif
