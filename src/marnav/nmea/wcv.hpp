#ifndef MARNAV__NMEA__WCV__HPP
#define MARNAV__NMEA__WCV__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
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
	friend class detail::factory;

public:
	constexpr static const sentence_id ID = sentence_id::WCV;
	constexpr static const char * TAG = "WCV";

	wcv();
	wcv(const wcv &) = default;
	wcv & operator=(const wcv &) = default;
	wcv(wcv &&) = default;
	wcv & operator=(wcv &&) = default;

protected:
	wcv(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> speed;
	utils::optional<unit::velocity> speed_unit;
	utils::optional<waypoint> waypoint_id;

public:
	decltype(speed) get_speed() const { return speed; }
	decltype(speed_unit) get_speed_unit() const { return speed_unit; }
	decltype(waypoint_id) get_waypoint_id() const { return waypoint_id; }

	void set_speed(double t) noexcept;
	void set_waypoint(const waypoint & id) { waypoint_id = id; }
};
}
}

#endif
