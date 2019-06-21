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
	constexpr static sentence_id ID = sentence_id::WNC;
	constexpr static const char * TAG = "WNC";

	wnc();
	wnc(const wnc &) = default;
	wnc & operator=(const wnc &) = default;
	wnc(wnc &&) = default;
	wnc & operator=(wnc &&) = default;

protected:
	wnc(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<double> distance_nm_;
	utils::optional<unit::distance> distance_nm_unit_;
	utils::optional<double> distance_km_;
	utils::optional<unit::distance> distance_km_unit_;
	utils::optional<waypoint> waypoint_to_;
	utils::optional<waypoint> waypoint_from_;

public:
	decltype(distance_nm_) get_distance_nm() const { return distance_nm_; }
	decltype(distance_nm_unit_) get_distance_nm_unit() const { return distance_nm_unit_; }
	decltype(distance_km_) get_distance_km() const { return distance_km_; }
	decltype(distance_km_unit_) get_distance_km_unit() const { return distance_km_unit_; }
	decltype(waypoint_to_) get_waypoint_to() const { return waypoint_to_; }
	decltype(waypoint_from_) get_waypoint_from() const { return waypoint_from_; }

	void set_distance_nm(double t) noexcept;
	void set_distance_km(double t) noexcept;
	void set_waypoint_to(const waypoint & id) { waypoint_to_ = id; }
	void set_waypoint_from(const waypoint & id) { waypoint_from_ = id; }
};
}
}

#endif
