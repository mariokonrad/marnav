#ifndef __NMEA__BWW__HPP__
#define __NMEA__BWW__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief BWW - Bearing - Waypoint to Waypoint
///
/// @code
///         1   2 3   4 5    6    7
///         |   | |   | |    |    |
///  $--BWW,x.x,T,x.x,M,c--c,c--c*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Bearing Degrees, TRUE
/// 2. T = True
/// 3. Bearing Degrees, Magnetic
/// 4. M = Magnetic
/// 5. TO Waypoint
/// 6. FROM Waypoint
/// 7. Checksum
///
class bww : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::BWW;
	constexpr static const char * TAG = "BWW";

	bww();
	bww(const bww &) = default;
	bww & operator=(const bww &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> bearing_true;
	utils::optional<char> bearing_true_ref;
	utils::optional<double> bearing_mag;
	utils::optional<char> bearing_mag_ref;
	utils::optional<std::string> waypoint_to;
	utils::optional<std::string> waypoint_from;

public:
	decltype(bearing_true) get_bearing_true() const { return bearing_true; }
	decltype(bearing_true_ref) get_bearing_true_ref() const { return bearing_true_ref; }
	decltype(bearing_mag) get_bearing_mag() const { return bearing_mag; }
	decltype(bearing_mag_ref) get_bearing_mag_ref() const { return bearing_mag_ref; }
	decltype(waypoint_to) get_waypoint_to() const { return waypoint_to; }
	decltype(waypoint_from) get_waypoint_from() const { return waypoint_from; }

	void set_bearing_true(double t);
	void set_bearing_mag(double t);
	void set_waypoint_to(const std::string & id);
	void set_waypoint_from(const std::string & id);
};
}
}

#endif
