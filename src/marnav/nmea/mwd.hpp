#ifndef __NMEA__MWD__HPP__
#define __NMEA__MWD__HPP__

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
public:
	constexpr static const sentence_id ID = sentence_id::MWD;
	constexpr static const char * TAG = "MWD";

	mwd();
	mwd(const mwd &) = default;
	mwd & operator=(const mwd &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument,
		std::runtime_error);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> direction_true;
	utils::optional<reference> direction_true_ref;
	utils::optional<double> direction_mag;
	utils::optional<reference> direction_mag_ref;
	utils::optional<double> speed_kn;
	utils::optional<unit::velocity> speed_kn_unit;
	utils::optional<double> speed_ms;
	utils::optional<unit::velocity> speed_ms_unit;

public:
	NMEA_GETTER(direction_true)
	NMEA_GETTER(direction_true_ref)
	NMEA_GETTER(direction_mag)
	NMEA_GETTER(direction_mag_ref)
	NMEA_GETTER(speed_kn)
	NMEA_GETTER(speed_kn_unit)
	NMEA_GETTER(speed_ms)
	NMEA_GETTER(speed_ms_unit)

	void set_direction_true(double t);
	void set_direction_mag(double t);
	void set_speed_knots(double t);
	void set_speed_mps(double t);
};
}
}

#endif
