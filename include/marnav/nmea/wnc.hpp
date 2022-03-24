#ifndef MARNAV_NMEA_WNC_HPP
#define MARNAV_NMEA_WNC_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/units/units.hpp>
#include <optional>

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
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<units::nautical_miles> distance_nm_;
	std::optional<units::kilometers> distance_km_;
	std::optional<waypoint> waypoint_to_;
	std::optional<waypoint> waypoint_from_;

public:
	std::optional<units::length> get_distance_nm() const;
	std::optional<units::length> get_distance_km() const;
	std::optional<waypoint> get_waypoint_to() const { return waypoint_to_; }
	std::optional<waypoint> get_waypoint_from() const { return waypoint_from_; }

	void set_distance_nm(units::length t) noexcept;
	void set_distance_km(units::length t) noexcept;
	void set_waypoint_to(const waypoint & id) { waypoint_to_ = id; }
	void set_waypoint_from(const waypoint & id) { waypoint_from_ = id; }
};
}
}

#endif
