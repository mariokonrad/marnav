#ifndef __NMEA__MWV__HPP__
#define __NMEA__MWV__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(mwv)

/// @brief MWV - Wind Speed and Angle
///
/// @code
///        1   2 3   4 5
///        |   | |   | |
/// $--MWV,x.x,a,x.x,a,a*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Wind Angle, 0 to 360 degrees
/// 2. Wind Angle Reference
///    - R = Relative
///    - T = True
/// 3. Wind Speed
/// 4. Wind Speed Unit
///    - K
///    - M
///    - N
/// 5. Status
///    - A = Data Valid
//     - V = Invalid
///
class mwv : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(mwv)

public:
	constexpr static const sentence_id ID = sentence_id::MWV;
	constexpr static const char * TAG = "MWV";

	mwv();
	mwv(const mwv &) = default;
	mwv & operator=(const mwv &) = default;

protected:
	mwv(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> angle; // wind angle, 0..359 right of bow
	utils::optional<reference> angle_ref; // R:relative, T:true
	utils::optional<double> speed; // wind speed
	utils::optional<unit::velocity> speed_unit; // wind speed unit, K:knots, M:mph
	utils::optional<status> data_valid; // status, A:valid

public:
	NMEA_GETTER(angle)
	NMEA_GETTER(angle_ref)
	NMEA_GETTER(speed)
	NMEA_GETTER(speed_unit)
	NMEA_GETTER(data_valid)

	void set_angle(double deg, reference ref);
	void set_speed(double speed, unit::velocity u) noexcept;
	void set_data_valid(status t) noexcept { data_valid = t; }
};
}
}

#endif
