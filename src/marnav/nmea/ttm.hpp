#ifndef MARNAV__NMEA__TTM__HPP
#define MARNAV__NMEA__TTM__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief TTM - Tracked Target Message
///
/// @code
///                                         11     13
///        1  2   3   4 5   6   7 8   9   10|    12| 14
///        |  |   |   | |   |   | |   |   | |    | | |
/// $--TTM,xx,x.x,x.x,a,x.x,x.x,a,x.x,x.x,a,c--c,a,a*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1.  Target Number (00-99)
/// 2.  Target Distance
/// 3.  Bearing from own ship
/// 4.  Bearing reference
///     - T = True
///     - R = Relative
/// 5.  Target Speed
/// 6.  Target Course
/// 7.  Target Course reference
///     - T = True
///     - R = Relative
/// 8.  Distance of closest-point-of-approach
/// 9.  Time until closest-point-of-approach "-" means increasing
/// 10. ?
/// 11. Target name
/// 12. Target Status
/// 13. Reference Target
///
/// @note Field 14 and 15 are not supported right now due to lack of
///       documentation. The sentence just ignores them. The other fields
///       are being processed.
///
class ttm : public sentence
{
	friend class detail::factory;

public:
	constexpr static const sentence_id ID = sentence_id::TTM;
	constexpr static const char * TAG = "TTM";

	ttm();
	ttm(const ttm &) = default;
	ttm & operator=(const ttm &) = default;
	ttm(ttm &&) = default;
	ttm & operator=(ttm &&) = default;

protected:
	ttm(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<uint32_t> target_number;
	utils::optional<double> target_distance;
	utils::optional<double> bearing_from_ownship;
	utils::optional<reference> bearing_from_ownship_ref;
	utils::optional<double> target_speed;
	utils::optional<double> target_course;
	utils::optional<reference> target_course_ref;
	utils::optional<double> distance_cpa; ///< Distance to closest point of approach
	utils::optional<double> tcpa;
	utils::optional<char> unknown;
	utils::optional<std::string> target_name;
	utils::optional<char> target_status;
	utils::optional<char> reference_target;

public:
	decltype(target_number) get_target_number() const { return target_number; }
	decltype(target_distance) get_target_distance() const { return target_distance; }
	decltype(bearing_from_ownship) get_bearing_from_ownship() const
	{
		return bearing_from_ownship;
	}
	decltype(bearing_from_ownship_ref) get_bearing_from_ownship_ref() const
	{
		return bearing_from_ownship_ref;
	}
	decltype(target_speed) get_target_speed() const { return target_speed; }
	decltype(target_course) get_target_course() const { return target_course; }
	decltype(target_course_ref) get_target_course_ref() const { return target_course_ref; }
	decltype(distance_cpa) get_distance_cpa() const { return distance_cpa; }
	decltype(tcpa) get_tcpa() const { return tcpa; }
	decltype(unknown) get_unknown() const { return unknown; }
	decltype(target_name) get_target_name() const { return target_name; }
	decltype(target_status) get_target_status() const { return target_status; }
	decltype(reference_target) get_reference_target() const { return reference_target; }

	void set_target_number(uint32_t t) noexcept { target_number = t; }
	void set_target_distance(double t) noexcept { target_distance = t; }
	void set_bearing_from_ownship(double t, reference r) noexcept
	{
		bearing_from_ownship = t;
		bearing_from_ownship_ref = r;
	}
	void set_target_speed(double t) noexcept { target_speed = t; }
	void set_target_course(double t, reference r) noexcept
	{
		target_course = t;
		target_course_ref = r;
	}
	void set_distance_cpa(double t) noexcept { distance_cpa = t; }
	void set_tcpa(double t) noexcept { tcpa = t; }
	void set_unknown(char t) noexcept { unknown = t; }
	void set_target_name(const std::string & t) { target_name = t; }
	void set_target_status(char t) noexcept { target_status = t; }
	void set_reference_target(char t) noexcept { reference_target = t; }
};
}
}

#endif
