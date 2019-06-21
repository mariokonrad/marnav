#ifndef MARNAV__NMEA__VPW__HPP
#define MARNAV__NMEA__VPW__HPP

#include <marnav/nmea/sentence.hpp>
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
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<double> speed_knots_; // negative means downwind
	utils::optional<unit::velocity> speed_knots_unit_;
	utils::optional<double> speed_meters_per_second_; // negative means downwind
	utils::optional<unit::velocity> speed_meters_per_second_unit_;

public:
	decltype(speed_knots_) get_speed_knots() const { return speed_knots_; }
	decltype(speed_knots_unit_) get_speed_knots_unit() const { return speed_knots_unit_; }
	decltype(speed_meters_per_second_) get_speed_meters_per_second() const
	{
		return speed_meters_per_second_;
	}
	decltype(speed_meters_per_second_unit_) get_speed_meters_per_second_unit() const
	{
		return speed_meters_per_second_unit_;
	}

	void set_speed_knots(double t) noexcept;
	void set_speed_mps(double t) noexcept;
};
}
}

#endif
