#ifndef __MARNAV__NMEA__BOD__HPP__
#define __MARNAV__NMEA__BOD__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(bod)

/// @brief BOD - Bearing - Waypoint to Waypoint
///
/// @code
///        1   2 3   4 5    6
///        |   | |   | |    |
/// $--BOD,x.x,T,x.x,M,c--c,c--c*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Bearing Degrees True
/// 2. Bearing Degrees True reference
///    - T = True
/// 3. Bearing Degrees Magnetic
/// 4. Bearing Degrees Magnetic reference
///    - M = Magnetic
/// 5. TO Waypoint ID
/// 6. FROM Waypoint ID
///
/// Example: <tt>$GPBOD,099.3,T,105.6,M,POINTB,*01</tt>
///
class bod : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(bod)

public:
	constexpr static const sentence_id ID = sentence_id::BOD;
	constexpr static const char * TAG = "BOD";

	bod();
	bod(const bod &) = default;
	bod & operator=(const bod &) = default;
	bod(bod &&) = default;
	bod & operator=(bod &&) = default;

protected:
	bod(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> bearing_true;
	utils::optional<reference> type_true; // T:true
	utils::optional<double> bearing_magn;
	utils::optional<reference> type_magn; // M:magnetic
	utils::optional<waypoint> waypoint_to; // TO waypoint ID
	utils::optional<waypoint> waypoint_from; // FROM waypoint ID

public:
	decltype(bearing_true) get_bearing_true() const { return bearing_true; }
	decltype(type_true) get_type_true() const { return type_true; }
	decltype(bearing_magn) get_bearing_magn() const { return bearing_magn; }
	decltype(type_magn) get_type_magn() const { return type_magn; }
	decltype(waypoint_to) get_waypoint_to() const { return waypoint_to; }
	decltype(waypoint_from) get_waypoint_from() const { return waypoint_from; }

	void set_bearing_true(double t) noexcept;
	void set_bearing_magn(double t) noexcept;
	void set_waypoint_to(const waypoint & id) { waypoint_to = id; }
	void set_waypoint_from(const waypoint & id) { waypoint_from = id; }
};
}
}

#endif
