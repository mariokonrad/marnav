#ifndef MARNAV__NMEA__BWW__HPP
#define MARNAV__NMEA__BWW__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief BWW - Bearing - Waypoint to Waypoint
///
/// @code
///        1   2 3   4 5    6
///        |   | |   | |    |
/// $--BWW,x.x,T,x.x,M,c--c,c--c*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Bearing Degrees true
/// 2. Bearing Degrees true reference
///    - T = True
/// 3. Bearing Degrees Magnetic
/// 4. Bearing Degrees Magnetic reference
///    - M = Magnetic
/// 5. TO Waypoint ID
/// 6. FROM Waypoint ID
///
class bww : public sentence
{
	friend class detail::factory;

public:
	constexpr static const sentence_id ID = sentence_id::BWW;
	constexpr static const char * TAG = "BWW";

	bww();
	bww(const bww &) = default;
	bww & operator=(const bww &) = default;
	bww(bww &&) = default;
	bww & operator=(bww &&) = default;

protected:
	bww(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> bearing_true;
	utils::optional<reference> bearing_true_ref;
	utils::optional<double> bearing_mag;
	utils::optional<reference> bearing_mag_ref;
	utils::optional<waypoint> waypoint_to;
	utils::optional<waypoint> waypoint_from;

public:
	decltype(bearing_true) get_bearing_true() const { return bearing_true; }
	decltype(bearing_true_ref) get_bearing_true_ref() const { return bearing_true_ref; }
	decltype(bearing_mag) get_bearing_mag() const { return bearing_mag; }
	decltype(bearing_mag_ref) get_bearing_mag_ref() const { return bearing_mag_ref; }
	decltype(waypoint_to) get_waypoint_to() const { return waypoint_to; }
	decltype(waypoint_from) get_waypoint_from() const { return waypoint_from; }

	void set_bearing_true(double t) noexcept;
	void set_bearing_mag(double t) noexcept;
	void set_waypoint_to(const waypoint & id) { waypoint_to = id; }
	void set_waypoint_from(const waypoint & id) { waypoint_from = id; }
};
}
}

#endif
