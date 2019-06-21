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
	constexpr static sentence_id ID = sentence_id::WCV;
	constexpr static const char * TAG = "WCV";

	wcv();
	wcv(const wcv &) = default;
	wcv & operator=(const wcv &) = default;
	wcv(wcv &&) = default;
	wcv & operator=(wcv &&) = default;

protected:
	wcv(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<double> speed_;
	utils::optional<unit::velocity> speed_unit_;
	utils::optional<waypoint> waypoint_id_;

public:
	decltype(speed_) get_speed() const { return speed_; }
	decltype(speed_unit_) get_speed_unit() const { return speed_unit_; }
	decltype(waypoint_id_) get_waypoint_id() const { return waypoint_id_; }

	void set_speed(double t) noexcept;
	void set_waypoint(const waypoint & id) { waypoint_id_ = id; }
};
}
}

#endif
