#ifndef __NMEA__VWR__HPP__
#define __NMEA__VWR__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief VWR - Relative Wind Speed and Angle.
///
/// @code
///         1  2  3  4  5  6  7  8 9
///         |  |  |  |  |  |  |  | |
/// $--VWR,x.x,a,x.x,N,x.x,M,x.x,K*hh<CR><LF>
/// @endcode
///
/// Field Number:
///
/// 1. Wind direction magnitude in degrees
/// 2. Wind direction Left/Right of bow
/// 3. Speed
/// 4. N = Knots
/// 5. Speed
/// 6. M = Meters Per Second
/// 7. Speed
/// 8. K = Kilometers Per Hour
/// 9. Checksum
///
class vwr : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::VWR;
	constexpr static const char * TAG = "VWR";

	vwr();
	vwr(const vwr &) = default;
	vwr & operator=(const vwr &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> angle; // wind angle, 0..180
	utils::optional<char> side; // side of vessel, R:right, L:left
	utils::optional<double> speed_knots; // wind speed in knots
	utils::optional<char> speed_knots_unit; // N:knots
	utils::optional<double> speed_mps; // wind speed in miles per second
	utils::optional<char> speed_mps_unit; // M:mps
	utils::optional<double> speed_kmh; // wind speed in kilometers per hour
	utils::optional<char> speed_kmh_unit; // K:kmh

public:
	decltype(angle) get_angle() const { return angle; }
	decltype(side) get_side() const { return side; }
	decltype(speed_knots) get_speed_knots() const { return speed_knots; }
	decltype(speed_knots_unit) get_speed_knots_unit() const { return speed_knots_unit; }
	decltype(speed_mps) get_speed_mps() const { return speed_mps; }
	decltype(speed_mps_unit) get_speed_mps_unit() const { return speed_mps_unit; }
	decltype(speed_kmh) get_speed_kmh() const { return speed_kmh; }
	decltype(speed_kmh_unit) get_speed_kmh_unit() const { return speed_kmh_unit; }

	void set_angle(double angle, char side);
	void set_speed_knots(double t);
	void set_speed_mps(double t);
	void set_speed_kmh(double t);
};
}
}

#endif
