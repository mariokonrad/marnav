#ifndef __NMEA__OSD__HPP__
#define __NMEA__OSD__HPP__

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

	virtual ~osd() {}

	osd();
	osd(const osd &) = default;
	osd & operator=(const osd &) = default;

protected:
	osd(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
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
	MARNAV_NMEA_GETTER(heading)
	MARNAV_NMEA_GETTER(data_valid)
	MARNAV_NMEA_GETTER(course)
	MARNAV_NMEA_GETTER(course_ref)
	MARNAV_NMEA_GETTER(speed)
	MARNAV_NMEA_GETTER(speed_unit)
	MARNAV_NMEA_GETTER(vessel_set)
	MARNAV_NMEA_GETTER(vessel_drift)
	MARNAV_NMEA_GETTER(vessel_drift_unit)

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
