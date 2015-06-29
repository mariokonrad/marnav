#ifndef __NMEA__OSD__HPP__
#define __NMEA__OSD__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief OSD - Own Ship Data
///
/// @code
///        1   2 3   4 5   6 7   8   9 10
///        |   | |   | |   | |   |   | |
/// $--OSD,x.x,A,x.x,a,x.x,a,x.x,x.x,a*hh<CR><LF>
/// @endcode
///
/// Field Number:
///
/// 1.  Heading, degrees true
/// 2.  Status, A = Data Valid
/// 3.  Vessel Course, degrees True
/// 4.  Course Reference
/// 5.  Vessel Speed
/// 6.  Speed Reference
/// 7.  Vessel Set, degrees True
/// 8.  Vessel drift (speed)
/// 9.  Speed Units
/// 10. Checksum
///
class osd : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::OSD;

	osd();
	osd(const osd &) = default;
	osd & operator=(const osd &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> heading; // degrees true
	utils::optional<char> status;
	utils::optional<double> course; // degrees true
	utils::optional<char> course_ref;
	utils::optional<double> speed;
	utils::optional<char> speed_ref;
	utils::optional<double> vessel_set; // degrees true
	utils::optional<double> vessel_drift; // (speed)
	utils::optional<char> vessel_drift_unit;

public:
	decltype(heading) get_heading() const { return heading; }
	decltype(status) get_status() const { return status; }
	decltype(course) get_course() const { return course; }
	decltype(course_ref) get_course_ref() const { return course_ref; }
	decltype(speed) get_speed() const { return speed; }
	decltype(speed_ref) get_speed_ref() const { return speed_ref; }
	decltype(vessel_set) get_vessel_set() const { return vessel_set; }
	decltype(vessel_drift) get_vessel_drift() const { return vessel_drift; }
	decltype(vessel_drift_unit) get_vessel_drift_unit() const { return vessel_drift_unit; }

	void set_heading(double t) { heading = t; }
	void set_status(char t) { status = t;}
	void set_course(double t, char ref);
	void set_speed(double t, char ref);
	void set_vessel_set(double t) { vessel_set = t; }
	void set_drift(double t, char unit);
};
}
}

#endif
