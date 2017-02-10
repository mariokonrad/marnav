#ifndef MARNAV__NMEA__WNC__HPP
#define MARNAV__NMEA__WNC__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief WNC - Distance - Waypoint to Waypoint
///
/// @code
///        1   2 3   4 5    6
///        |   | |   | |    |
/// $--WNC,x.x,N,x.x,K,c--c,c--c*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Distance nautical miles
/// 2. Distance nautical miles unit
///    - N = Nautical Miles
/// 3. Distance Kilometers
/// 4. Distance Kilometers unit
///    - K = Kilometers
/// 5. TO Waypoint ID
/// 6. FROM Waypoint ID
///
class wnc : public sentence
{
	friend class detail::factory;

public:
	constexpr static const sentence_id ID = sentence_id::WNC;
	constexpr static const char * TAG = "WNC";

	wnc();
	wnc(const wnc &) = default;
	wnc & operator=(const wnc &) = default;
	wnc(wnc &&) = default;
	wnc & operator=(wnc &&) = default;

protected:
	wnc(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> distance_nm;
	utils::optional<unit::distance> distance_nm_unit;
	utils::optional<double> distance_km;
	utils::optional<unit::distance> distance_km_unit;
	utils::optional<waypoint> waypoint_to;
	utils::optional<waypoint> waypoint_from;

public:
	decltype(distance_nm) get_distance_nm() const { return distance_nm; }
	decltype(distance_nm_unit) get_distance_nm_unit() const { return distance_nm_unit; }
	decltype(distance_km) get_distance_km() const { return distance_km; }
	decltype(distance_km_unit) get_distance_km_unit() const { return distance_km_unit; }
	decltype(waypoint_to) get_waypoint_to() const { return waypoint_to; }
	decltype(waypoint_from) get_waypoint_from() const { return waypoint_from; }

	void set_distance_nm(double t) noexcept;
	void set_distance_km(double t) noexcept;
	void set_waypoint_to(const waypoint & id) { waypoint_to = id; }
	void set_waypoint_from(const waypoint & id) { waypoint_from = id; }
};
}
}

#endif
