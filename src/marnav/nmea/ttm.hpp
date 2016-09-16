#ifndef __NMEA__TTM__HPP__
#define __NMEA__TTM__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(ttm)

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
	MARNAV_NMEA_SENTENCE_FRIENDS(ttm)

public:
	constexpr static const sentence_id ID = sentence_id::TTM;
	constexpr static const char * TAG = "TTM";

	virtual ~ttm() {}

	ttm();
	ttm(const ttm &) = default;
	ttm & operator=(const ttm &) = default;

protected:
	ttm(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
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
	MARNAV_NMEA_GETTER(target_number)
	MARNAV_NMEA_GETTER(target_distance)
	MARNAV_NMEA_GETTER(bearing_from_ownship)
	MARNAV_NMEA_GETTER(bearing_from_ownship_ref)
	MARNAV_NMEA_GETTER(target_speed)
	MARNAV_NMEA_GETTER(target_course)
	MARNAV_NMEA_GETTER(target_course_ref)
	MARNAV_NMEA_GETTER(distance_cpa)
	MARNAV_NMEA_GETTER(tcpa)
	MARNAV_NMEA_GETTER(unknown)
	MARNAV_NMEA_GETTER(target_name)
	MARNAV_NMEA_GETTER(target_status)
	MARNAV_NMEA_GETTER(reference_target)

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
