#ifndef __NMEA__VHW__HPP__
#define __NMEA__VHW__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(vhw)

/// @brief VHW - Water speed and heading
///
/// @code
///        1   2 3   4 5   6 7   8
///        |   | |   | |   | |   |
/// $--VHW,x.x,T,x.x,M,x.x,N,x.x,K*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Degress True
/// 2. Degress True reference
///    - T = True
/// 3. Degrees Magnetic
/// 4. Degrees Magnetic reference
///    - M = Magnetic
/// 5. Knots (speed of vessel relative to the water)
/// 6. N = Knots
/// 7. Kilometers per hour (speed of vessel relative to the water)
/// 8. K = Kilometers per hour
///
class vhw : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(vhw)

public:
	constexpr static const sentence_id ID = sentence_id::VHW;
	constexpr static const char * TAG = "VHW";

	vhw();
	vhw(const vhw &) = default;
	vhw & operator=(const vhw &) = default;
	vhw(vhw &&) = default;
	vhw & operator=(vhw &&) = default;

protected:
	vhw(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<char> heading_empty; // heading (empty)
	utils::optional<reference> degrees_true; // T:true
	utils::optional<double> heading; // heading in degrees, 0..359
	utils::optional<reference> degrees_mag; // M:magnetic
	utils::optional<double> speed_knots; // speed in knots
	utils::optional<unit::velocity> speed_knots_unit; // N:knots
	utils::optional<double> speed_kmh; // speed in kilometers per hour
	utils::optional<unit::velocity> speed_kmh_unit; // K:kmh

public:
	decltype(heading_empty) get_heading_empty() const { return heading_empty; }
	decltype(degrees_true) get_degrees_true() const { return degrees_true; }
	decltype(heading) get_heading() const { return heading; }
	decltype(degrees_mag) get_degrees_mag() const { return degrees_mag; }
	decltype(speed_knots) get_speed_knots() const { return speed_knots; }
	decltype(speed_knots_unit) get_speed_knots_unit() const { return speed_knots_unit; }
	decltype(speed_kmh) get_speed_kmh() const { return speed_kmh; }
	decltype(speed_kmh_unit) get_speed_kmh_unit() const { return speed_kmh_unit; }

	void set_heading(double t) noexcept;
	void set_speed_knots(double t) noexcept;
	void set_speed_kmh(double t) noexcept;
};
}
}

#endif
