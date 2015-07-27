#ifndef __NMEA__MWV__HPP__
#define __NMEA__MWV__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief MWV - Wind Speed and Angle
///
/// @code
///        1   2 3   4 5
///        |   | |   | |
/// $--MWV,x.x,a,x.x,a,a*hh<CR><LF>
/// @endcode
///
/// Field Number:
///  1. Wind Angle, 0 to 360 degrees
///  2. Wind Angle Reference
///     - R = Relative
///     - T = True
///  3. Wind Speed
///  4. Wind Speed Unit
///     - K
///     - M
///     - N
///  5. Status
///     - A = Data Valid
//      - V = Invalid
///
class mwv : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::MWV;
	constexpr static const char * TAG = "MWV";

	mwv();
	mwv(const mwv &) = default;
	mwv & operator=(const mwv &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> angle; // wind angle, 0..359 right of bow
	utils::optional<char> type; // R:relative, T:true
	utils::optional<double> speed; // wind speed
	utils::optional<char> speed_unit; // wind speed unit, K:knots, M:mph
	utils::optional<char> status; // status, A:valid

public:
	NMEA_GETTER(angle)
	NMEA_GETTER(type)
	NMEA_GETTER(speed)
	NMEA_GETTER(speed_unit)
	NMEA_GETTER(status)

	void set_angle(double deg, char type);
	void set_speed(double speed, char unit);
	void set_status(char t) { status = t; }
};
}
}

#endif
