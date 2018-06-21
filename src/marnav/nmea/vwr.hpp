#ifndef MARNAV__NMEA__VWR__HPP
#define MARNAV__NMEA__VWR__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief VWR - Relative Wind Speed and Angle.
///
/// @code
///         1  2  3  4  5  6  7  8
///         |  |  |  |  |  |  |  |
/// $--VWR,x.x,a,x.x,N,x.x,M,x.x,K*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Wind direction magnitude in degrees
/// 2. Wind direction regarding to bow
///    - L = Left
///    - R = Right
/// 3. Speed knots
/// 4. Speed knots unit
///    - N = Knots
/// 5. Speed meters per second
/// 6. Speed meters per second unit
///    - M = Meters Per Second
/// 7. Speed kilometers per hour
/// 8. Speed kilometers per hour unit
///    - K = Kilometers Per Hour
///
class vwr : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::VWR;
	constexpr static const char * TAG = "VWR";

	vwr();
	vwr(const vwr &) = default;
	vwr & operator=(const vwr &) = default;
	vwr(vwr &&) = default;
	vwr & operator=(vwr &&) = default;

protected:
	vwr(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<double> angle_; // wind angle, 0..180
	utils::optional<side> angle_side_; // side of vessel, R:right, L:left
	utils::optional<double> speed_knots_; // wind speed in knots
	utils::optional<unit::velocity> speed_knots_unit_; // N:knots
	utils::optional<double> speed_mps_; // wind speed in meters per second
	utils::optional<unit::velocity> speed_mps_unit_; // M:mps
	utils::optional<double> speed_kmh_; // wind speed in kilometers per hour
	utils::optional<unit::velocity> speed_kmh_unit_; // K:kmh

public:
	decltype(angle_) get_angle() const { return angle_; }
	decltype(angle_side_) get_angle_side() const { return angle_side_; }
	decltype(speed_knots_) get_speed_knots() const { return speed_knots_; }
	decltype(speed_knots_unit_) get_speed_knots_unit() const { return speed_knots_unit_; }
	decltype(speed_mps_) get_speed_mps() const { return speed_mps_; }
	decltype(speed_mps_unit_) get_speed_mps_unit() const { return speed_mps_unit_; }
	decltype(speed_kmh_) get_speed_kmh() const { return speed_kmh_; }
	decltype(speed_kmh_unit_) get_speed_kmh_unit() const { return speed_kmh_unit_; }

	void set_angle(double angle, side s) noexcept;
	void set_speed_knots(double t) noexcept;
	void set_speed_mps(double t) noexcept;
	void set_speed_kmh(double t) noexcept;
};
}
}

#endif
