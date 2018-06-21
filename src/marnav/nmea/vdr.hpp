#ifndef MARNAV__NMEA__VDR__HPP
#define MARNAV__NMEA__VDR__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

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
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<double> degrees_true_;
	utils::optional<reference> degrees_true_ref_; // T:true
	utils::optional<double> degrees_mag_;
	utils::optional<reference> degrees_mag_ref_; // M:magnetic
	utils::optional<double> speed_;
	utils::optional<unit::velocity> speed_unit_; // N:knots

public:
	decltype(degrees_true_) get_degrees_true() const { return degrees_true_; }
	decltype(degrees_true_ref_) get_degrees_true_ref() const { return degrees_true_ref_; }
	decltype(degrees_mag_) get_degrees_mag() const { return degrees_mag_; }
	decltype(degrees_mag_ref_) get_degrees_mag_ref() const { return degrees_mag_ref_; }
	decltype(speed_) get_speed() const { return speed_; }
	decltype(speed_unit_) get_speed_unit() const { return speed_unit_; }

	void set_degrees_true(double t) noexcept;
	void set_degrees_mag(double t) noexcept;
	void set_speed(double t) noexcept;
};
}
}

#endif
