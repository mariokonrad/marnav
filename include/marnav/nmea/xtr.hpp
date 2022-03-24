#ifndef MARNAV_NMEA_XTR_HPP
#define MARNAV_NMEA_XTR_HPP

#include <marnav/nmea/sentence.hpp>
#include <optional>

namespace marnav
{
namespace nmea
{
/// @brief XTR - Cross Track Error - Dead Reckoning
///
/// @code
///        1   2 3
///        |   | |
/// $--XTR,x.x,a,N*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Magnitude of cross track error
/// 2. Direction to steer
///    - L = left
///    - R = right
/// 3. Unit
///    - N = Nautical Miles
///
class xtr : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::XTR;
	constexpr static const char * TAG = "XTR";

	xtr();
	xtr(const xtr &) = default;
	xtr & operator=(const xtr &) = default;
	xtr(xtr &&) = default;
	xtr & operator=(xtr &&) = default;

protected:
	xtr(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<double> cross_track_error_magnitude_;
	std::optional<side> direction_to_steer_;
	std::optional<unit::distance> cross_track_unit_;

public:
	std::optional<double> get_cross_track_error_magnitude() const
	{
		return cross_track_error_magnitude_;
	}
	std::optional<side> get_direction_to_steer() const { return direction_to_steer_; }
	std::optional<unit::distance> get_cross_track_unit() const { return cross_track_unit_; }

	void set_cross_track_error_magnitude(double t) noexcept
	{
		cross_track_error_magnitude_ = t;
		cross_track_unit_ = unit::distance::nm;
	}
	void set_direction_to_steer(side t) noexcept { direction_to_steer_ = t; }
};
}
}

#endif
