#ifndef MARNAV_NMEA_VBW_HPP
#define MARNAV_NMEA_VBW_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/units/units.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief VBW - Dual Ground/Water Speed
///
/// @code
///        1   2   3 4   5   6
///        |   |   | |   |   |
/// $--VBW,x.x,x.x,A,x.x,x.x,A*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Longitudinal water speed, "-" means astern, knots
/// 2. Transverse water speed, "-" means port, knots
/// 3. Status, A = Data Valid
///    - A = Data Valid
///    - V = Invalid
/// 4. Longitudinal ground speed, "-" means astern, knots
/// 5. Transverse ground speed, "-" means port, knots
/// 6. Status
///    - A = Data Valid
///    - V = Invalid
///
class vbw : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::VBW;
	constexpr static const char * TAG = "VBW";

	vbw();
	vbw(const vbw &) = default;
	vbw & operator=(const vbw &) = default;
	vbw(vbw &&) = default;
	vbw & operator=(vbw &&) = default;

protected:
	vbw(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<units::knots> water_speed_longitudinal_;
	utils::optional<units::knots> water_speed_transveral_;
	utils::optional<status> water_speed_status_;
	utils::optional<units::knots> ground_speed_longitudinal_;
	utils::optional<units::knots> ground_speed_transveral_;
	utils::optional<status> ground_speed_status_;

public:
	utils::optional<units::velocity> get_water_speed_longitudinal() const;
	utils::optional<units::velocity> get_water_speed_transveral() const;
	utils::optional<status> get_water_speed_status() const { return water_speed_status_; }
	utils::optional<units::velocity> get_ground_speed_longitudinal() const;
	utils::optional<units::velocity> get_ground_speed_transveral() const;
	utils::optional<status> get_ground_speed_status() const { return ground_speed_status_; }

	void set_water_speed(units::velocity l, units::velocity t, status s);
	void set_ground_speed(units::velocity l, units::velocity t, status s);
};
}
}

#endif
