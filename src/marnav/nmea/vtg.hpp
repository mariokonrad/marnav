#ifndef __NMEA__VTG__HPP__
#define __NMEA__VTG__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(vtg)

/// @brief VTG - Track made good and Ground speed
///
/// @code
///         1  2  3  4  5  6  7  8 9
///         |  |  |  |  |  |  |  | |
/// $--VTG,x.x,T,x.x,M,x.x,N,x.x,K,m*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Track Degrees true
/// 2. Track degrees true reference
///    - T = True
/// 3. Track Degrees magnetic
/// 4. Track Degrees magnetic reference
///    - M = Magnetic
/// 5. Speed Knots
/// 6. Speed knots unit
///    - N = Knots
/// 7. Speed Kilometers Per Hour
/// 8. speed Kilometers per hour unit
///    - K = Kilometers Per Hour
/// 9. FAA mode indicator (NMEA 2.3 and later)
///
class vtg : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(vtg)

public:
	constexpr static const sentence_id ID = sentence_id::VTG;
	constexpr static const char * TAG = "VTG";

	vtg();
	vtg(const vtg &) = default;
	vtg & operator=(const vtg &) = default;
	vtg(vtg &&) = default;
	vtg & operator=(vtg &&) = default;

protected:
	vtg(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> track_true;
	utils::optional<reference> type_true; // T:true
	utils::optional<double> track_magn;
	utils::optional<reference> type_magn; // M:magnetic
	utils::optional<double> speed_kn;
	utils::optional<unit::velocity> speed_kn_unit; // N:knots
	utils::optional<double> speed_kmh;
	utils::optional<unit::velocity> speed_kmh_unit; // K:kilometers per hour
	utils::optional<mode_indicator> mode_ind; // NMEA 2.3 or newer

public:
	MARNAV_NMEA_GETTER(track_true)
	MARNAV_NMEA_GETTER(type_true)
	MARNAV_NMEA_GETTER(track_magn)
	MARNAV_NMEA_GETTER(type_magn)
	MARNAV_NMEA_GETTER(speed_kn)
	MARNAV_NMEA_GETTER(speed_kn_unit)
	MARNAV_NMEA_GETTER(speed_kmh)
	MARNAV_NMEA_GETTER(speed_kmh_unit)
	MARNAV_NMEA_GETTER(mode_ind)

	void set_track_true(double t) noexcept;
	void set_track_magn(double t) noexcept;
	void set_speed_kn(double t) noexcept;
	void set_speed_kmh(double t) noexcept;
	void set_mode_indicator(mode_indicator t) noexcept { mode_ind = t; }
};
}
}

#endif
