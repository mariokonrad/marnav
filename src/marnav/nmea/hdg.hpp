#ifndef __NMEA__HDG__HPP__
#define __NMEA__HDG__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

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
public:
	constexpr static const sentence_id ID = sentence_id::HDG;
	constexpr static const char * TAG = "HDG";

	hdg();
	hdg(const hdg &) = default;
	hdg(hdg &&) noexcept = default;
	hdg & operator=(const hdg &) = default;
	hdg & operator=(hdg &&) noexcept = default;

	static std::unique_ptr<sentence> parse(
		const std::string & talker, const std::vector<std::string> & fields);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> heading; // magnetic sensor heading in deg
	utils::optional<double> magn_dev; // magnetic deviation in deg
	utils::optional<direction> magn_dev_hem; // E:east, W:west
	utils::optional<double> magn_var; // magnetic variation in deg
	utils::optional<direction> magn_var_hem; // E:east, W:west

public:
	NMEA_GETTER(heading)
	NMEA_GETTER(magn_dev)
	NMEA_GETTER(magn_dev_hem)
	NMEA_GETTER(magn_var)
	NMEA_GETTER(magn_var_hem)

	void set_heading(double t) noexcept { heading = t; }
	void set_magn_dev(double deg, direction hem);
	void set_magn_var(double deg, direction hem);
};
}
}

#endif
