#ifndef MARNAV_NMEA_VDR_HPP
#define MARNAV_NMEA_VDR_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/units/units.hpp>
#include <optional>

namespace marnav
{
namespace nmea
{
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
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::VDR;
	constexpr static const char * TAG = "VDR";

	vdr();
	vdr(const vdr &) = default;
	vdr & operator=(const vdr &) = default;
	vdr(vdr &&) = default;
	vdr & operator=(vdr &&) = default;

protected:
	vdr(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<double> degrees_true_;
	std::optional<double> degrees_magn_;
	std::optional<units::knots> speed_;

public:
	std::optional<double> get_degrees_true() const { return degrees_true_; }
	std::optional<double> get_degrees_magn() const { return degrees_magn_; }
	std::optional<units::velocity> get_speed() const;

	void set_degrees_true(double t) noexcept;
	void set_degrees_magn(double t) noexcept;
	void set_speed(units::velocity t) noexcept;
};
}
}

#endif
