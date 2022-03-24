#ifndef MARNAV_NMEA_OSD_HPP
#define MARNAV_NMEA_OSD_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/units/units.hpp>
#include <optional>

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
///    - B
///    - M
///    - W
///    - R
///    - P
/// 5. Vessel Speed
/// 6. Speed Reference
///    - B
///    - M
///    - W
///    - R
///    - P
/// 7. Vessel Set, degrees True
/// 8. Vessel drift speed
/// 9. Speed Units
///    - K = Kilometers per hour
///    - N = Knots
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
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<double> heading_; // degrees true
	std::optional<status> data_valid_;
	std::optional<double> course_; // degrees true
	std::optional<reference> course_ref_;
	std::optional<double> speed_;
	std::optional<char> speed_ref_;
	std::optional<double> vessel_set_; // degrees true
	std::optional<double> vessel_drift_; // (speed)
	std::optional<unit::velocity> speed_unit_;

public:
	std::optional<double> get_heading() const { return heading_; }
	std::optional<status> get_data_valid() const { return data_valid_; }
	std::optional<double> get_course() const { return course_; }
	std::optional<reference> get_course_ref() const { return course_ref_; }
	std::optional<double> get_speed() const { return speed_; }
	std::optional<char> get_speed_ref() const { return speed_ref_; }
	std::optional<double> get_vessel_set() const { return vessel_set_; }
	std::optional<double> get_vessel_drift() const { return vessel_drift_; }
	std::optional<unit::velocity> get_speed_unit() const { return speed_unit_; }

	void set_heading(double t) noexcept { heading_ = t; }
	void set_data_valid(status t) noexcept { data_valid_ = t; }
	void set_course(double t) noexcept;
	void set_speed(double t) noexcept;
	void set_speed_ref(char t) noexcept { speed_ref_ = t; }
	void set_vessel_set(double t) noexcept { vessel_set_ = t; }
	void set_drift(double t) noexcept;
	void set_speed_unit(unit::velocity u) noexcept;
};
}
}

#endif
