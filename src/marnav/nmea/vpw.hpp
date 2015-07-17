#ifndef __NMEA__VPW__HPP__
#define __NMEA__VPW__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

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
public:
	constexpr static const sentence_id ID = sentence_id::VPW;
	constexpr static const char * TAG = "VPW";

	vpw();
	vpw(const vpw &) = default;
	vpw & operator=(const vpw &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> speed_knots; // negative means downwind
	utils::optional<char> speed_knots_unit;
	utils::optional<double> speed_meters_per_second; // negative means downwind
	utils::optional<char> speed_meters_per_second_unit;

public:
	decltype(speed_knots) get_speed_knots() const { return speed_knots; }
	decltype(speed_knots_unit) get_speed_knots_unit() const { return speed_knots_unit; }
	decltype(speed_meters_per_second) get_speed_meters_per_second() const
	{
		return speed_meters_per_second;
	}
	decltype(speed_meters_per_second_unit) get_speed_meters_per_second_unit() const
	{
		return speed_meters_per_second_unit;
	}

	void set_speed_knots(double t);
	void set_speed_mps(double t);
};
}
}

#endif
