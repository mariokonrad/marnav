#ifndef __NMEA__VHW__HPP__
#define __NMEA__VHW__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

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
/// 7. Kilometers (speed of vessel relative to the water)
/// 8. K = Kilometers
///
class vhw : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::VHW;
	constexpr static const char * TAG = "VHW";

	vhw();
	vhw(const vhw &) = default;
	vhw & operator=(const vhw &) = default;

	static std::unique_ptr<sentence> parse(
		const std::string & talker, fields::const_iterator first, fields::const_iterator last);

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
	NMEA_GETTER(heading_empty)
	NMEA_GETTER(degrees_true)
	NMEA_GETTER(heading)
	NMEA_GETTER(degrees_mag)
	NMEA_GETTER(speed_knots)
	NMEA_GETTER(speed_knots_unit)
	NMEA_GETTER(speed_kmh)
	NMEA_GETTER(speed_kmh_unit)

	void set_heading(double t) noexcept;
	void set_speed_knots(double t) noexcept;
	void set_speed_kmh(double t) noexcept;
};
}
}

#endif
