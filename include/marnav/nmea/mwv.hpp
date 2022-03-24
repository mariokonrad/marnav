#ifndef MARNAV_NMEA_MWV_HPP
#define MARNAV_NMEA_MWV_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/units/units.hpp>
#include <optional>

namespace marnav
{
namespace nmea
{
/// @brief MWV - Wind Speed and Angle
///
/// @code
///        1   2 3   4 5
///        |   | |   | |
/// $--MWV,x.x,a,x.x,a,a*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Wind Angle, 0 to 360 degrees
/// 2. Wind Angle Reference
///    - R = Relative
///    - T = True
/// 3. Wind Speed
/// 4. Wind Speed Unit
///    - K = kilometers per hour
///    - M = meters per second
///    - N = knots
/// 5. Status
///    - A = Data Valid
//     - V = Invalid
///
class mwv : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::MWV;
	constexpr static const char * TAG = "MWV";

	mwv();
	mwv(const mwv &) = default;
	mwv & operator=(const mwv &) = default;
	mwv(mwv &&) = default;
	mwv & operator=(mwv &&) = default;

protected:
	mwv(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<double> angle_; // wind angle, 0..359 right of bow
	std::optional<reference> angle_ref_; // R:relative, T:true
	std::optional<double> speed_; // wind speed
	std::optional<unit::velocity> speed_unit_; // wind speed unit
	std::optional<status> data_valid_; // status, A:valid

public:
	std::optional<double> get_angle() const { return angle_; }
	std::optional<reference> get_angle_ref() const { return angle_ref_; }
	std::optional<units::velocity> get_speed() const;
	std::optional<unit::velocity> get_speed_unit() const { return speed_unit_; }
	std::optional<status> get_data_valid() const { return data_valid_; }

	void set_angle(double deg, reference ref);
	void set_speed(units::velocity speed, unit::velocity u) noexcept;
	void set_speed(units::knots speed) noexcept;
	void set_speed(units::kilometers_per_hour speed) noexcept;
	void set_speed(units::meters_per_second speed) noexcept;
	void set_data_valid(status t) noexcept { data_valid_ = t; }
};
}
}

#endif
