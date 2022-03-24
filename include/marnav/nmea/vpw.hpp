#ifndef MARNAV_NMEA_VPW_HPP
#define MARNAV_NMEA_VPW_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/units/units.hpp>
#include <optional>

namespace marnav
{
namespace nmea
{
/// @brief VPW - Speed - Measured Parallel to Wind
///
/// @code
///        1   2 3   4
///        |   | |   |
/// $--VPW,x.x,N,x.x,M*hh<CR><LF>
/// @endcode
///
/// Field Number:
///
/// 1. Speed knots, "-" means downwind
/// 2. Speed knots unit
///    - N = Knots
/// 3. Speed meters per second, "-" means downwind
/// 4. Speed meters per second unit
///    - M = Meters per second
///
class vpw : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::VPW;
	constexpr static const char * TAG = "VPW";

	vpw();
	vpw(const vpw &) = default;
	vpw & operator=(const vpw &) = default;
	vpw(vpw &&) = default;
	vpw & operator=(vpw &&) = default;

protected:
	vpw(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<units::knots> speed_knots_; // negative means downwind
	std::optional<units::meters_per_second> speed_mps_; // negative means downwind

public:
	std::optional<units::knots> get_speed_knots() const;
	std::optional<units::meters_per_second> get_speed_meters_per_second() const;

	void set_speed_knots(units::velocity t) noexcept;
	void set_speed_mps(units::velocity t) noexcept;
};
}
}

#endif
