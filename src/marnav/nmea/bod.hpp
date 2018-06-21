#ifndef MARNAV__NMEA__BOD__HPP
#define MARNAV__NMEA__BOD__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
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
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::BOD;
	constexpr static const char * TAG = "BOD";

	bod();
	bod(const bod &) = default;
	bod & operator=(const bod &) = default;
	bod(bod &&) = default;
	bod & operator=(bod &&) = default;

protected:
	bod(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<double> bearing_true_;
	utils::optional<reference> type_true_; // T:true
	utils::optional<double> bearing_magn_;
	utils::optional<reference> type_magn_; // M:magnetic
	utils::optional<waypoint> waypoint_to_; // TO waypoint ID
	utils::optional<waypoint> waypoint_from_; // FROM waypoint ID

public:
	decltype(bearing_true_) get_bearing_true() const { return bearing_true_; }
	decltype(type_true_) get_type_true() const { return type_true_; }
	decltype(bearing_magn_) get_bearing_magn() const { return bearing_magn_; }
	decltype(type_magn_) get_type_magn() const { return type_magn_; }
	decltype(waypoint_to_) get_waypoint_to() const { return waypoint_to_; }
	decltype(waypoint_from_) get_waypoint_from() const { return waypoint_from_; }

	void set_bearing_true(double t) noexcept;
	void set_bearing_magn(double t) noexcept;
	void set_waypoint_to(const waypoint & id) { waypoint_to_ = id; }
	void set_waypoint_from(const waypoint & id) { waypoint_from_ = id; }
};
}
}

#endif
