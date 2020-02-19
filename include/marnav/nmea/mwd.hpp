#ifndef MARNAV_NMEA_MWD_HPP
#define MARNAV_NMEA_MWD_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/units/units.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief MWD - Wind Direction and Speed
///
/// Wind Direction and Speed, with respect to north.
///
/// @code
///        1   2 3
///        |   | |
/// $--MWD,x.x,T,x.x,M,x.x.,N,x.x,M*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Wind direction true in degrees (0.0 .. 359.9), resolution: 0.1 degree
/// 2. Reference of wind direction
///    - T = True
/// 3. Wind direction magnetic in degrees (0.0 .. 359.9), resolution: 0.1 degree
/// 4. Reference of wind direction
///    - M = Magnetic
/// 5. Wind speed in knots (resolution: 0.1 knots)
/// 6. Wind speed unit
///    - N = Knots
/// 7. Wind speed in meters per second (resolution: 0.1 m/s)
/// 8. Wind speed unit
///    - M = Meters per Second
///
class mwd : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::MWD;
	constexpr static const char * TAG = "MWD";

	mwd();
	mwd(const mwd &) = default;
	mwd & operator=(const mwd &) = default;
	mwd(mwd &&) = default;
	mwd & operator=(mwd &&) = default;

protected:
	mwd(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<double> direction_true_;
	utils::optional<double> direction_mag_;
	utils::optional<units::knots> speed_kn_;
	utils::optional<units::meters_per_second> speed_ms_;

public:
	utils::optional<double> get_direction_true() const { return direction_true_; }
	utils::optional<double> get_direction_mag() const { return direction_mag_; }
	utils::optional<units::velocity> get_speed_kn() const;
	utils::optional<units::velocity> get_speed_ms() const;

	void set_direction_true(double t) noexcept;
	void set_direction_mag(double t) noexcept;
	void set_speed_knots(units::velocity t) noexcept;
	void set_speed_mps(units::velocity t) noexcept;
};
}
}

#endif
