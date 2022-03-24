#ifndef MARNAV_NMEA_TTM_HPP
#define MARNAV_NMEA_TTM_HPP

#include <marnav/nmea/sentence.hpp>
#include <optional>

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
	constexpr static sentence_id ID = sentence_id::TTM;
	constexpr static const char * TAG = "TTM";

	ttm();
	ttm(const ttm &) = default;
	ttm & operator=(const ttm &) = default;
	ttm(ttm &&) = default;
	ttm & operator=(ttm &&) = default;

protected:
	ttm(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<uint32_t> target_number_;
	std::optional<double> target_distance_;
	std::optional<double> bearing_from_ownship_;
	std::optional<reference> bearing_from_ownship_ref_;
	std::optional<double> target_speed_;
	std::optional<double> target_course_;
	std::optional<reference> target_course_ref_;
	std::optional<double> distance_cpa_; ///< Distance to closest point of approach
	std::optional<double> tcpa_;
	std::optional<char> unknown_;
	std::optional<std::string> target_name_;
	std::optional<char> target_status_;
	std::optional<char> reference_target_;

public:
	std::optional<uint32_t> get_target_number() const { return target_number_; }
	std::optional<double> get_target_distance() const { return target_distance_; }
	std::optional<double> get_bearing_from_ownship() const { return bearing_from_ownship_; }
	std::optional<reference> get_bearing_from_ownship_ref() const
	{
		return bearing_from_ownship_ref_;
	}
	std::optional<double> get_target_speed() const { return target_speed_; }
	std::optional<double> get_target_course() const { return target_course_; }
	std::optional<reference> get_target_course_ref() const { return target_course_ref_; }
	std::optional<double> get_distance_cpa() const { return distance_cpa_; }
	std::optional<double> get_tcpa() const { return tcpa_; }
	std::optional<char> get_unknown() const { return unknown_; }
	std::optional<std::string> get_target_name() const { return target_name_; }
	std::optional<char> get_target_status() const { return target_status_; }
	std::optional<char> get_reference_target() const { return reference_target_; }

	void set_target_number(uint32_t t) noexcept { target_number_ = t; }
	void set_target_distance(double t) noexcept { target_distance_ = t; }
	void set_bearing_from_ownship(double t, reference r) noexcept
	{
		bearing_from_ownship_ = t;
		bearing_from_ownship_ref_ = r;
	}
	void set_target_speed(double t) noexcept { target_speed_ = t; }
	void set_target_course(double t, reference r) noexcept
	{
		target_course_ = t;
		target_course_ref_ = r;
	}
	void set_distance_cpa(double t) noexcept { distance_cpa_ = t; }
	void set_tcpa(double t) noexcept { tcpa_ = t; }
	void set_unknown(char t) noexcept { unknown_ = t; }
	void set_target_name(const std::string & t) { target_name_ = t; }
	void set_target_status(char t) noexcept { target_status_ = t; }
	void set_reference_target(char t) noexcept { reference_target_ = t; }
};
}
}

#endif
