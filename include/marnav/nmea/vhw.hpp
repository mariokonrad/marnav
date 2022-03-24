#ifndef MARNAV_NMEA_VHW_HPP
#define MARNAV_NMEA_VHW_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/units/units.hpp>
#include <optional>

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
/// 1. Heading Degress True
/// 2. Heading Degress True reference
///    - T = True
/// 3. Heading Degrees Magnetic
/// 4. Heading Degrees Magnetic reference
///    - M = Magnetic
/// 5. Speed of vessel relative to the water
/// 6. Speed of vessel relative to the water unit
///    - N = Knots
/// 7. Speed of vessel relative to the water
/// 8. Speed of vessel relative to the water unit
///    - K = Kilometers per hour
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
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<double> heading_true_; // 0..359
	std::optional<double> heading_magn_; // 0..359
	std::optional<units::knots> speed_knots_;
	std::optional<units::kilometers_per_hour> speed_kmh_;

public:
	std::optional<double> get_heading_true() const { return heading_true_; }
	std::optional<double> get_heading_magn() const { return heading_magn_; }
	std::optional<units::knots> get_speed_knots() const { return speed_knots_; }
	std::optional<units::kilometers_per_hour> get_speed_kmh() const { return speed_kmh_; }

	void set_heading_true(double t) noexcept;
	void set_heading_magn(double t) noexcept;
	void set_speed_knots(units::velocity t) noexcept;
	void set_speed_kmh(units::velocity t) noexcept;
};
}
}

#endif
