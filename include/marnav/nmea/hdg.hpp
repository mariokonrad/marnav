#ifndef MARNAV_NMEA_HDG_HPP
#define MARNAV_NMEA_HDG_HPP

#include <marnav/nmea/magnetic.hpp>
#include <marnav/nmea/sentence.hpp>
#include <optional>

namespace marnav::nmea
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
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<double> heading_; // magnetic sensor heading in deg
	std::optional<double> magn_dev_; // magnetic deviation in deg
	std::optional<direction> magn_dev_hem_; // E:east, W:west
	std::optional<double> magn_var_; // magnetic variation in deg
	std::optional<direction> magn_var_hem_; // E:east, W:west

public:
	std::optional<double> get_heading() const { return heading_; }
	std::optional<magnetic> get_magn_dev() const;
	std::optional<magnetic> get_magn_var() const;

	void set_heading(double t) noexcept { heading_ = t; }
	void set_magn_dev(const magnetic & t);
	void set_magn_var(const magnetic & t);
};
}

#endif
