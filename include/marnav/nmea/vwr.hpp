#ifndef MARNAV_NMEA_VWR_HPP
#define MARNAV_NMEA_VWR_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/units/units.hpp>
#include <optional>

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
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<double> angle_; // wind angle, 0..180
	std::optional<side> angle_side_; // side of vessel, R:right, L:left
	std::optional<units::knots> speed_knots_;
	std::optional<units::meters_per_second> speed_mps_;
	std::optional<units::kilometers_per_hour> speed_kmh_;

public:
	std::optional<double> get_angle() const { return angle_; }
	std::optional<side> get_angle_side() const { return angle_side_; }
	std::optional<units::velocity> get_speed_knots() const;
	std::optional<units::velocity> get_speed_mps() const;
	std::optional<units::velocity> get_speed_kmh() const;

	void set_angle(double angle, side s) noexcept;
	void set_speed_knots(units::velocity t) noexcept;
	void set_speed_mps(units::velocity t) noexcept;
	void set_speed_kmh(units::velocity t) noexcept;
};
}
}

#endif
