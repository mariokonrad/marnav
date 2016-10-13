#ifndef __MARNAV__NMEA__OSD__HPP__
#define __MARNAV__NMEA__OSD__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(osd)

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
	MARNAV_NMEA_SENTENCE_FRIENDS(osd)

public:
	constexpr static const sentence_id ID = sentence_id::OSD;
	constexpr static const char * TAG = "OSD";

	osd();
	osd(const osd &) = default;
	osd & operator=(const osd &) = default;
	osd(osd &&) = default;
	osd & operator=(osd &&) = default;

protected:
	osd(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> heading; // degrees true
	utils::optional<status> data_valid;
	utils::optional<double> course; // degrees true
	utils::optional<reference> course_ref;
	utils::optional<double> speed;
	utils::optional<unit::velocity> speed_unit;
	utils::optional<double> vessel_set; // degrees true
	utils::optional<double> vessel_drift; // (speed)
	utils::optional<unit::velocity> vessel_drift_unit;

public:
	decltype(heading) get_heading() const { return heading; }
	decltype(data_valid) get_data_valid() const { return data_valid; }
	decltype(course) get_course() const { return course; }
	decltype(course_ref) get_course_ref() const { return course_ref; }
	decltype(speed) get_speed() const { return speed; }
	decltype(speed_unit) get_speed_unit() const { return speed_unit; }
	decltype(vessel_set) get_vessel_set() const { return vessel_set; }
	decltype(vessel_drift) get_vessel_drift() const { return vessel_drift; }
	decltype(vessel_drift_unit) get_vessel_drift_unit() const { return vessel_drift_unit; }

	void set_heading(double t) noexcept { heading = t; }
	void set_data_valid(status t) noexcept { data_valid = t; }
	void set_course(double t) noexcept;
	void set_speed(double t, unit::velocity u) noexcept;
	void set_vessel_set(double t) noexcept { vessel_set = t; }
	void set_drift(double t, unit::velocity u) noexcept;
};
}
}

#endif
