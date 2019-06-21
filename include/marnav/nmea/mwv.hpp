#ifndef MARNAV__NMEA__MWV__HPP
#define MARNAV__NMEA__MWV__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

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
///    - K
///    - M
///    - N
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
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<double> angle_; // wind angle, 0..359 right of bow
	utils::optional<reference> angle_ref_; // R:relative, T:true
	utils::optional<double> speed_; // wind speed
	utils::optional<unit::velocity> speed_unit_; // wind speed unit, K:knots, M:mph
	utils::optional<status> data_valid_; // status, A:valid

public:
	decltype(angle_) get_angle() const { return angle_; }
	decltype(angle_ref_) get_angle_ref() const { return angle_ref_; }
	decltype(speed_) get_speed() const { return speed_; }
	decltype(speed_unit_) get_speed_unit() const { return speed_unit_; }
	decltype(data_valid_) get_data_valid() const { return data_valid_; }

	void set_angle(double deg, reference ref);
	void set_speed(double speed, unit::velocity u) noexcept;
	void set_data_valid(status t) noexcept { data_valid_ = t; }
};
}
}

#endif
