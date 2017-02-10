#ifndef MARNAV__NMEA__HDG__HPP
#define MARNAV__NMEA__HDG__HPP

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
	friend class detail::factory;

public:
	constexpr static const sentence_id ID = sentence_id::HDG;
	constexpr static const char * TAG = "HDG";

	hdg();
	hdg(const hdg &) = default;
	hdg & operator=(const hdg &) = default;
	hdg(hdg &&) = default;
	hdg & operator=(hdg &&) = default;

protected:
	hdg(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> heading; // magnetic sensor heading in deg
	utils::optional<double> magn_dev; // magnetic deviation in deg
	utils::optional<direction> magn_dev_hem; // E:east, W:west
	utils::optional<double> magn_var; // magnetic variation in deg
	utils::optional<direction> magn_var_hem; // E:east, W:west

public:
	decltype(heading) get_heading() const { return heading; }
	decltype(magn_dev) get_magn_dev() const { return magn_dev; }
	decltype(magn_dev_hem) get_magn_dev_hem() const { return magn_dev_hem; }
	decltype(magn_var) get_magn_var() const { return magn_var; }
	decltype(magn_var_hem) get_magn_var_hem() const { return magn_var_hem; }

	void set_heading(double t) noexcept { heading = t; }
	void set_magn_dev(double deg, direction hem);
	void set_magn_var(double deg, direction hem);
};
}
}

#endif
