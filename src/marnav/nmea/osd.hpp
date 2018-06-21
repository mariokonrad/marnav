#ifndef MARNAV__NMEA__OSD__HPP
#define MARNAV__NMEA__OSD__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief OSD - Own Ship Data
///
/// @code
///        1   2 3   4 5   6 7   8   9
///        |   | |   | |   | |   |   |
/// $--OSD,x.x,A,x.x,a,x.x,a,x.x,x.x,a*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Heading, degrees true
/// 2. Status
///    - A = Data Valid
///    - V = Invalid
/// 3. Vessel Course, degrees True
/// 4. Course Reference
///    - T = True
/// 5. Vessel Speed
/// 6. Speed Unit
/// 7. Vessel Set, degrees True
/// 8. Vessel drift (speed)
/// 9. Speed Units
///
class osd : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::OSD;
	constexpr static const char * TAG = "OSD";

	osd();
	osd(const osd &) = default;
	osd & operator=(const osd &) = default;
	osd(osd &&) = default;
	osd & operator=(osd &&) = default;

protected:
	osd(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<double> heading_; // degrees true
	utils::optional<status> data_valid_;
	utils::optional<double> course_; // degrees true
	utils::optional<reference> course_ref_;
	utils::optional<double> speed_;
	utils::optional<unit::velocity> speed_unit_;
	utils::optional<double> vessel_set_; // degrees true
	utils::optional<double> vessel_drift_; // (speed)
	utils::optional<unit::velocity> vessel_drift_unit_;

public:
	decltype(heading_) get_heading() const { return heading_; }
	decltype(data_valid_) get_data_valid() const { return data_valid_; }
	decltype(course_) get_course() const { return course_; }
	decltype(course_ref_) get_course_ref() const { return course_ref_; }
	decltype(speed_) get_speed() const { return speed_; }
	decltype(speed_unit_) get_speed_unit() const { return speed_unit_; }
	decltype(vessel_set_) get_vessel_set() const { return vessel_set_; }
	decltype(vessel_drift_) get_vessel_drift() const { return vessel_drift_; }
	decltype(vessel_drift_unit_) get_vessel_drift_unit() const { return vessel_drift_unit_; }

	void set_heading(double t) noexcept { heading_ = t; }
	void set_data_valid(status t) noexcept { data_valid_ = t; }
	void set_course(double t) noexcept;
	void set_speed(double t, unit::velocity u) noexcept;
	void set_vessel_set(double t) noexcept { vessel_set_ = t; }
	void set_drift(double t, unit::velocity u) noexcept;
};
}
}

#endif
