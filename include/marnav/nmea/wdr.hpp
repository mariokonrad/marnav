#ifndef MARNAV_NMEA_WDR_HPP
#define MARNAV_NMEA_WDR_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/units/units.hpp>

namespace marnav
{
namespace nmea
{
/// @brief WDR - Distance to Waypoint, Rumb line
///
/// @code
///         1   2 3
///         |   | |
///  $--WDR,x.x,N,c--c*hh<CR><LF>
///
/// Field Number:
/// 1. Distance to Waypoint
/// 2. Distance unit
///    - N = Nautical Miles
/// 3. Waypoint ID
/// @endcode
///
class wdr : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::WDR;
	constexpr static const char * TAG = "WDR";

	wdr();
	wdr(const wdr &) = default;
	wdr & operator=(const wdr &) = default;
	wdr(wdr &&) = default;
	wdr & operator=(wdr &&) = default;

protected:
	wdr(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	units::nautical_miles distance_;
	waypoint waypoint_id_;

public:
	units::nautical_miles get_distance() const { return distance_; }
	waypoint get_waypoint_id() const { return waypoint_id_; }

	void set_distance(units::length t);
	void set_waypoint_id(const waypoint & id) { waypoint_id_ = id; }
};
}
}

#endif
