#ifndef MARNAV_NMEA_WCV_HPP
#define MARNAV_NMEA_WCV_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/units/units.hpp>
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
	utils::optional<units::knots> speed_;
	utils::optional<waypoint> waypoint_id_;

public:
	utils::optional<units::velocity> get_speed() const;
	utils::optional<waypoint> get_waypoint_id() const { return waypoint_id_; }

	void set_speed(units::velocity t) noexcept;
	void set_waypoint(const waypoint & id) { waypoint_id_ = id; }
};
}
}

#endif
