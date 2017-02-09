#ifndef MARNAV__NMEA__XTR__HPP
#define MARNAV__NMEA__XTR__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(xtr)

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
	MARNAV_NMEA_SENTENCE_FRIENDS(xtr)

public:
	constexpr static const sentence_id ID = sentence_id::XTR;
	constexpr static const char * TAG = "XTR";

	xtr();
	xtr(const xtr &) = default;
	xtr & operator=(const xtr &) = default;
	xtr(xtr &&) = default;
	xtr & operator=(xtr &&) = default;

protected:
	xtr(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> cross_track_error_magnitude;
	utils::optional<side> direction_to_steer;
	utils::optional<unit::distance> cross_track_unit;

public:
	decltype(cross_track_error_magnitude) get_cross_track_error_magnitude() const
	{
		return cross_track_error_magnitude;
	}
	decltype(direction_to_steer) get_direction_to_steer() const { return direction_to_steer; }
	decltype(cross_track_unit) get_cross_track_unit() const { return cross_track_unit; }

	void set_cross_track_error_magnitude(double t) noexcept
	{
		cross_track_error_magnitude = t;
		cross_track_unit = unit::distance::nm;
	}
	void set_direction_to_steer(side t) noexcept { direction_to_steer = t; }
};
}
}

#endif
