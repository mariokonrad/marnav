#ifndef __NMEA__VPW__HPP__
#define __NMEA__VPW__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(vpw)

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
	MARNAV_NMEA_SENTENCE_FRIENDS(vpw)

public:
	constexpr static const sentence_id ID = sentence_id::VPW;
	constexpr static const char * TAG = "VPW";

	vpw();
	vpw(const vpw &) = default;
	vpw & operator=(const vpw &) = default;
	vpw(vpw &&) = default;
	vpw & operator=(vpw &&) = default;

protected:
	vpw(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> speed_knots; // negative means downwind
	utils::optional<unit::velocity> speed_knots_unit;
	utils::optional<double> speed_meters_per_second; // negative means downwind
	utils::optional<unit::velocity> speed_meters_per_second_unit;

public:
	MARNAV_NMEA_GETTER(speed_knots)
	MARNAV_NMEA_GETTER(speed_knots_unit)
	MARNAV_NMEA_GETTER(speed_meters_per_second)
	MARNAV_NMEA_GETTER(speed_meters_per_second_unit)

	void set_speed_knots(double t) noexcept;
	void set_speed_mps(double t) noexcept;
};
}
}

#endif
