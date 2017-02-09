#ifndef MARNAV__NMEA__VDR__HPP
#define MARNAV__NMEA__VDR__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(vdr)

/// @brief VDR - Set and Drift
///
/// @code
///        1   2 3   4 5   6
///        |   | |   | |   |
/// $--VDR,x.x,T,x.x,M,x.x,N*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Degress True
/// 2. Degress True reference
///    - T = True
/// 3. Degrees Magnetic
/// 4. Degrees Magnetic reference
///    - M = Magnetic
/// 5. Speed of current
/// 6. Speed of current unit
///    - N = Knots
///
class vdr : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(vdr)

public:
	constexpr static const sentence_id ID = sentence_id::VDR;
	constexpr static const char * TAG = "VDR";

	vdr();
	vdr(const vdr &) = default;
	vdr & operator=(const vdr &) = default;
	vdr(vdr &&) = default;
	vdr & operator=(vdr &&) = default;

protected:
	vdr(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> degrees_true;
	utils::optional<reference> degrees_true_ref; // T:true
	utils::optional<double> degrees_mag;
	utils::optional<reference> degrees_mag_ref; // M:magnetic
	utils::optional<double> speed;
	utils::optional<unit::velocity> speed_unit; // N:knots

public:
	decltype(degrees_true) get_degrees_true() const { return degrees_true; }
	decltype(degrees_true_ref) get_degrees_true_ref() const { return degrees_true_ref; }
	decltype(degrees_mag) get_degrees_mag() const { return degrees_mag; }
	decltype(degrees_mag_ref) get_degrees_mag_ref() const { return degrees_mag_ref; }
	decltype(speed) get_speed() const { return speed; }
	decltype(speed_unit) get_speed_unit() const { return speed_unit; }

	void set_degrees_true(double t) noexcept;
	void set_degrees_mag(double t) noexcept;
	void set_speed(double t) noexcept;
};
}
}

#endif
