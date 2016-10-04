#ifndef __NMEA__WCV__HPP__
#define __NMEA__WCV__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(wcv)

/// @brief WCV - Waypoint Closure Velocity
///
/// @code
///        1   2 3
///        |   | |
/// $--WCV,x.x,N,c--c*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Velocity
/// 2. Velocity unit
///    - N = knots
/// 3. Waypoint ID
///
class wcv : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(wcv)

public:
	constexpr static const sentence_id ID = sentence_id::WCV;
	constexpr static const char * TAG = "WCV";

	wcv();
	wcv(const wcv &) = default;
	wcv & operator=(const wcv &) = default;
	wcv(wcv &&) = default;
	wcv & operator=(wcv &&) = default;

protected:
	wcv(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> speed;
	utils::optional<unit::velocity> speed_unit;
	utils::optional<waypoint> waypoint_id;

public:
	MARNAV_NMEA_GETTER(speed)
	MARNAV_NMEA_GETTER(speed_unit)
	MARNAV_NMEA_GETTER(waypoint_id)

	void set_speed(double t) noexcept;
	void set_waypoint(const waypoint & id) { waypoint_id = id; }
};
}
}

#endif
