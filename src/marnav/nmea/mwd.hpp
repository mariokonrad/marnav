#ifndef __MARNAV__NMEA__MWD__HPP__
#define __MARNAV__NMEA__MWD__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(mwd)

/// @brief MWD - Wind Direction and Speed
///
/// Wind Direction and Speed, with respect to north.
///
/// @code
///        1   2 3
///        |   | |
/// $--MWD,x.x,T,x.x,M,x.x.,N,x.x,M*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Wind direction true in degrees (0.0 .. 359.9), resolution: 0.1 degree
/// 2. Reference of wind direction
///    - T = True
/// 3. Wind direction magnetic in degrees (0.0 .. 359.9), resolution: 0.1 degree
/// 4. Reference of wind direction
///    - M = Magnetic
/// 5. Wind speed in knots (resolution: 0.1 knots)
/// 6. Wind speed unit
///    - N = Knots
/// 7. Wind speed in meters per second (resolution: 0.1 m/s)
/// 8. Wind speed unit
///    - M = Meters per Second
///
class mwd : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(mwd)

public:
	constexpr static const sentence_id ID = sentence_id::MWD;
	constexpr static const char * TAG = "MWD";

	mwd();
	mwd(const mwd &) = default;
	mwd & operator=(const mwd &) = default;
	mwd(mwd &&) = default;
	mwd & operator=(mwd &&) = default;

protected:
	mwd(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> direction_true;
	utils::optional<reference> direction_true_ref;
	utils::optional<double> direction_mag;
	utils::optional<reference> direction_mag_ref;
	utils::optional<double> speed_kn;
	utils::optional<unit::velocity> speed_kn_unit;
	utils::optional<double> speed_ms;
	utils::optional<unit::velocity> speed_ms_unit;

public:
	decltype(direction_true) get_direction_true() const { return direction_true; }
	decltype(direction_true_ref) get_direction_true_ref() const { return direction_true_ref; }
	decltype(direction_mag) get_direction_mag() const { return direction_mag; }
	decltype(direction_mag_ref) get_direction_mag_ref() const { return direction_mag_ref; }
	decltype(speed_kn) get_speed_kn() const { return speed_kn; }
	decltype(speed_kn_unit) get_speed_kn_unit() const { return speed_kn_unit; }
	decltype(speed_ms) get_speed_ms() const { return speed_ms; }
	decltype(speed_ms_unit) get_speed_ms_unit() const { return speed_ms_unit; }

	void set_direction_true(double t) noexcept;
	void set_direction_mag(double t) noexcept;
	void set_speed_knots(double t) noexcept;
	void set_speed_mps(double t) noexcept;
};
}
}

#endif
