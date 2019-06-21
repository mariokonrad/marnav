#ifndef MARNAV__NMEA__VHW__HPP
#define MARNAV__NMEA__VHW__HPP

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
/// 7. Kilometers per hour (speed of vessel relative to the water)
/// 8. K = Kilometers per hour
///
class vhw : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::VHW;
	constexpr static const char * TAG = "VHW";

	vhw();
	vhw(const vhw &) = default;
	vhw & operator=(const vhw &) = default;
	vhw(vhw &&) = default;
	vhw & operator=(vhw &&) = default;

protected:
	vhw(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<char> heading_empty_; // heading (empty)
	utils::optional<reference> degrees_true_; // T:true
	utils::optional<double> heading_; // heading in degrees, 0..359
	utils::optional<reference> degrees_mag_; // M:magnetic
	utils::optional<double> speed_knots_; // speed in knots
	utils::optional<unit::velocity> speed_knots_unit_; // N:knots
	utils::optional<double> speed_kmh_; // speed in kilometers per hour
	utils::optional<unit::velocity> speed_kmh_unit_; // K:kmh

public:
	decltype(heading_empty_) get_heading_empty() const { return heading_empty_; }
	decltype(degrees_true_) get_degrees_true() const { return degrees_true_; }
	decltype(heading_) get_heading() const { return heading_; }
	decltype(degrees_mag_) get_degrees_mag() const { return degrees_mag_; }
	decltype(speed_knots_) get_speed_knots() const { return speed_knots_; }
	decltype(speed_knots_unit_) get_speed_knots_unit() const { return speed_knots_unit_; }
	decltype(speed_kmh_) get_speed_kmh() const { return speed_kmh_; }
	decltype(speed_kmh_unit_) get_speed_kmh_unit() const { return speed_kmh_unit_; }

	void set_heading(double t) noexcept;
	void set_speed_knots(double t) noexcept;
	void set_speed_kmh(double t) noexcept;
};
}
}

#endif
