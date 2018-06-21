#ifndef MARNAV__NMEA__MWD__HPP
#define MARNAV__NMEA__MWD__HPP

#include <marnav/nmea/sentence.hpp>
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
	utils::optional<reference> direction_true_ref_;
	utils::optional<double> direction_mag_;
	utils::optional<reference> direction_mag_ref_;
	utils::optional<double> speed_kn_;
	utils::optional<unit::velocity> speed_kn_unit_;
	utils::optional<double> speed_ms_;
	utils::optional<unit::velocity> speed_ms_unit_;

public:
	decltype(direction_true_) get_direction_true() const { return direction_true_; }
	decltype(direction_true_ref_) get_direction_true_ref() const { return direction_true_ref_; }
	decltype(direction_mag_) get_direction_mag() const { return direction_mag_; }
	decltype(direction_mag_ref_) get_direction_mag_ref() const { return direction_mag_ref_; }
	decltype(speed_kn_) get_speed_kn() const { return speed_kn_; }
	decltype(speed_kn_unit_) get_speed_kn_unit() const { return speed_kn_unit_; }
	decltype(speed_ms_) get_speed_ms() const { return speed_ms_; }
	decltype(speed_ms_unit_) get_speed_ms_unit() const { return speed_ms_unit_; }

	void set_direction_true(double t) noexcept;
	void set_direction_mag(double t) noexcept;
	void set_speed_knots(double t) noexcept;
	void set_speed_mps(double t) noexcept;
};
}
}

#endif
