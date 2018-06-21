#ifndef MARNAV__NMEA__XTE__HPP
#define MARNAV__NMEA__XTE__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief XTE - Cross-Track Error, Measured
///
/// @code
///        1 2 3   4 5 6
///        | | |   | | |
/// $--XTE,A,A,x.x,a,N,m,*hh<CR><LF>
/// @endcode
///
/// Field Number:
///
/// 1. Status
///    - V = LORAN-C Blink or SNR warning
///    - V = general warning flag or other navigation systems when a reliable fix is not
///    available
/// 2. Status
///    - V = Loran-C Cycle Lock warning flag
///    - A = OK or not used
/// 3. Cross Track Error Magnitude
/// 4. Direction to steer
///    - L = Left
///    - R = Right
/// 5. Cross Track Units
///    - N = Nautical Miles
/// 6. FAA mode indicator (NMEA 2.3 and later, optional)
///
class xte : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::XTE;
	constexpr static const char * TAG = "XTE";

	xte();
	xte(const xte &) = default;
	xte & operator=(const xte &) = default;
	xte(xte &&) = default;
	xte & operator=(xte &&) = default;

protected:
	xte(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<status> status1_;
	utils::optional<status> status2_;
	utils::optional<double> cross_track_error_magnitude_;
	utils::optional<side> direction_to_steer_;
	utils::optional<unit::distance> cross_track_unit_;
	utils::optional<mode_indicator> mode_ind_;

public:
	decltype(status1_) get_status1() const { return status1_; }
	decltype(status2_) get_status2() const { return status2_; }
	decltype(cross_track_error_magnitude_) get_cross_track_error_magnitude() const
	{
		return cross_track_error_magnitude_;
	}
	decltype(direction_to_steer_) get_direction_to_steer() const { return direction_to_steer_; }
	decltype(cross_track_unit_) get_cross_track_unit() const { return cross_track_unit_; }
	decltype(mode_ind_) get_mode_ind() const { return mode_ind_; }

	void set_status1(status t) noexcept { status1_ = t; }
	void set_status2(status t) noexcept { status2_ = t; }
	void set_cross_track_error_magnitude(double t) noexcept
	{
		cross_track_error_magnitude_ = t;
		cross_track_unit_ = unit::distance::nm;
	}
	void set_direction_to_steer(side t) noexcept { direction_to_steer_ = t; }
	void set_mode_indicato(mode_indicator t) noexcept { mode_ind_ = t; }
};
}
}

#endif
