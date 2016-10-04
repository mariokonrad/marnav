#ifndef __NMEA__HDG__HPP__
#define __NMEA__HDG__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(hdg)

/// @brief HDG - Heading - Deviation & Variation
///
/// @code
///        1   2   3 4   5
///        |   |   | |   |
/// $--HDG,x.x,x.x,a,x.x,a*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Magnetic Sensor heading in degrees
/// 2. Magnetic Deviation degrees
/// 3. Magnetic Deviation direction
///    - E = Easterly
///    - W = Westerly
/// 4. Magnetic Variation degrees
/// 5. Magnetic Variation direction
///    - E = Easterly
///    - W = Westerly
///
class hdg : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(hdg)

public:
	constexpr static const sentence_id ID = sentence_id::HDG;
	constexpr static const char * TAG = "HDG";

	hdg();
	hdg(const hdg &) = default;
	hdg & operator=(const hdg &) = default;
	hdg(hdg &&) = default;
	hdg & operator=(hdg &&) = default;

protected:
	hdg(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> heading; // magnetic sensor heading in deg
	utils::optional<double> magn_dev; // magnetic deviation in deg
	utils::optional<direction> magn_dev_hem; // E:east, W:west
	utils::optional<double> magn_var; // magnetic variation in deg
	utils::optional<direction> magn_var_hem; // E:east, W:west

public:
	MARNAV_NMEA_GETTER(heading)
	MARNAV_NMEA_GETTER(magn_dev)
	MARNAV_NMEA_GETTER(magn_dev_hem)
	MARNAV_NMEA_GETTER(magn_var)
	MARNAV_NMEA_GETTER(magn_var_hem)

	void set_heading(double t) noexcept { heading = t; }
	void set_magn_dev(double deg, direction hem);
	void set_magn_var(double deg, direction hem);
};
}
}

#endif
