#ifndef MARNAV_NMEA_HDG_HPP
#define MARNAV_NMEA_HDG_HPP

#include <marnav/nmea/sentence.hpp>
#include <optional>

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
	constexpr static sentence_id ID = sentence_id::HDG;
	constexpr static const char * TAG = "HDG";

	hdg();
	hdg(const hdg &) = default;
	hdg & operator=(const hdg &) = default;
	hdg(hdg &&) = default;
	hdg & operator=(hdg &&) = default;

protected:
	hdg(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	std::optional<double> heading_; // magnetic sensor heading in deg
	std::optional<double> magn_dev_; // magnetic deviation in deg
	std::optional<direction> magn_dev_hem_; // E:east, W:west
	std::optional<double> magn_var_; // magnetic variation in deg
	std::optional<direction> magn_var_hem_; // E:east, W:west

public:
	std::optional<double> get_heading() const { return heading_; }
	std::optional<double> get_magn_dev() const { return magn_dev_; }
	std::optional<direction> get_magn_dev_hem() const { return magn_dev_hem_; }
	std::optional<double> get_magn_var() const { return magn_var_; }
	std::optional<direction> get_magn_var_hem() const { return magn_var_hem_; }

	void set_heading(double t) noexcept { heading_ = t; }
	void set_magn_dev(double deg, direction hem);
	void set_magn_var(double deg, direction hem);
};
}
}

#endif
