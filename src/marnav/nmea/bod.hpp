#ifndef __NMEA__BOD__HPP__
#define __NMEA__BOD__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief BOD - Bearing - Waypoint to Waypoint
///
/// @code
///        1   2 3   4 5    6    7
///        |   | |   | |    |    |
/// $--BOD,x.x,T,x.x,M,c--c,c--c*hh<CR><LF>
/// @endcode
///
/// Field Number:
///
///  1. Bearing Degrees, TRUE
///  2. T = True
///  3. Bearing Degrees, Magnetic
///  4. M = Magnetic
///  5. TO Waypoint
///  6. FROM Waypoint
///  7. Checksum
///
/// Example 1: <tt>$GPBOD,099.3,T,105.6,M,POINTB,*01</tt>
///
class bod : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::BOD;

	bod();
	bod(const bod &) = default;
	bod & operator=(const bod &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	void check_waypoint_id(const std::string & id) const throw(std::invalid_argument);

	utils::optional<double> bearing_true;
	utils::optional<char> type_true; // T:true
	utils::optional<double> bearing_magn;
	utils::optional<char> type_magn; // M:magnetic
	utils::optional<std::string> waypoint_to; // TO waypoint ID
	utils::optional<std::string> waypoint_from; // FROM waypoint ID

public:
	decltype(bearing_true) get_bearing_true() const { return bearing_true; }
	decltype(type_true) get_type_true() const { return type_true; }
	decltype(bearing_magn) get_bearing_magn() const { return bearing_magn; }
	decltype(type_magn) get_type_magn() const { return type_magn; }
	decltype(waypoint_to) get_waypoint_to() const { return waypoint_to; }
	decltype(waypoint_from) get_waypoint_from() const { return waypoint_from; }

	void set_bearing_true(double t);
	void set_bearing_magn(double t);
	void set_waypoint_to(const std::string & id);
	void set_waypoint_from(const std::string & id);
};
}
}

#endif
