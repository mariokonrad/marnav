#ifndef __NMEA__XTE__HPP__
#define __NMEA__XTE__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief XTE - Cross-Track Error, Measured
///
/// @code
///        1 2 3   4 5 6
///        | | |   | | |
/// $--XTE,A,A,x.x,a,N,m,*hh<CR><LF>
/// @endcode
///
/// Field Number:
///
/// 1. Status
///    - V = LORAN-C Blink or SNR warning
///    - V = general warning flag or other navigation systems when a reliable fix is not
///    available
/// 2. Status
///    - V = Loran-C Cycle Lock warning flag
///    - A = OK or not used
/// 3. Cross Track Error Magnitude
/// 4. Direction to steer
///    - L = Left
///    - R = Right
/// 5. Cross Track Units
///    - N = Nautical Miles
/// 6. FAA mode indicator (NMEA 2.3 and later, optional)
///
class xte : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::XTE;
	constexpr static const char * TAG = "XTE";

	xte();
	xte(const xte &) = default;
	xte & operator=(const xte &) = default;

	static std::unique_ptr<sentence> parse(
		const std::string & talker, const std::vector<std::string> & fields);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<status> status1;
	utils::optional<status> status2;
	utils::optional<double> cross_track_error_magnitude;
	utils::optional<side> direction_to_steer;
	utils::optional<unit::distance> cross_track_unit;
	utils::optional<positioning_system_mode_indicator> mode_indicator;

public:
	NMEA_GETTER(status1)
	NMEA_GETTER(status2)
	NMEA_GETTER(cross_track_error_magnitude)
	NMEA_GETTER(direction_to_steer)
	NMEA_GETTER(cross_track_unit)
	NMEA_GETTER(mode_indicator)

	void set_status1(status t) noexcept { status1 = t; }
	void set_status2(status t) noexcept { status2 = t; }
	void set_cross_track_error_magnitude(double t) noexcept
	{
		cross_track_error_magnitude = t;
		cross_track_unit = unit::distance::nm;
	}
	void set_direction_to_steer(side t) noexcept { direction_to_steer = t; }
	void set_faa_mode_indicato(positioning_system_mode_indicator t) noexcept
	{
		mode_indicator = t;
	}
};
}
}

#endif
