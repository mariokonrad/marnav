#ifndef __NMEA__VWR__HPP__
#define __NMEA__VWR__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(vwr)

/// @brief VWR - Relative Wind Speed and Angle.
///
/// @code
///         1  2  3  4  5  6  7  8
///         |  |  |  |  |  |  |  |
/// $--VWR,x.x,a,x.x,N,x.x,M,x.x,K*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Wind direction magnitude in degrees
/// 2. Wind direction regarding to bow
///    - L = Left
///    - R = Right
/// 3. Speed knots
/// 4. Speed knots unit
///    - N = Knots
/// 5. Speed meters per second
/// 6. Speed meters per second unit
///    - M = Meters Per Second
/// 7. Speed kilometers per hour
/// 8. Speed kilometers per hour unit
///    - K = Kilometers Per Hour
///
class vwr : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(vwr)

public:
	constexpr static const sentence_id ID = sentence_id::VWR;
	constexpr static const char * TAG = "VWR";

	virtual ~vwr() {}

	vwr();
	vwr(const vwr &) = default;
	vwr & operator=(const vwr &) = default;

protected:
	vwr(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> angle; // wind angle, 0..180
	utils::optional<side> angle_side; // side of vessel, R:right, L:left
	utils::optional<double> speed_knots; // wind speed in knots
	utils::optional<unit::velocity> speed_knots_unit; // N:knots
	utils::optional<double> speed_mps; // wind speed in meters per second
	utils::optional<unit::velocity> speed_mps_unit; // M:mps
	utils::optional<double> speed_kmh; // wind speed in kilometers per hour
	utils::optional<unit::velocity> speed_kmh_unit; // K:kmh

public:
	NMEA_GETTER(angle)
	NMEA_GETTER(angle_side)
	NMEA_GETTER(speed_knots)
	NMEA_GETTER(speed_knots_unit)
	NMEA_GETTER(speed_mps)
	NMEA_GETTER(speed_mps_unit)
	NMEA_GETTER(speed_kmh)
	NMEA_GETTER(speed_kmh_unit)

	void set_angle(double angle, side s) noexcept;
	void set_speed_knots(double t) noexcept;
	void set_speed_mps(double t) noexcept;
	void set_speed_kmh(double t) noexcept;
};
}
}

#endif
