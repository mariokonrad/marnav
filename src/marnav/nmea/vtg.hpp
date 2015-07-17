#ifndef __NMEA__VTG__HPP__
#define __NMEA__VTG__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

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
public:
	constexpr static const sentence_id ID = sentence_id::VTG;
	constexpr static const char * TAG = "VTG";

	vtg();
	vtg(const vtg &) = default;
	vtg & operator=(const vtg &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> track_true;
	utils::optional<char> type_true; // T:true
	utils::optional<double> track_magn;
	utils::optional<char> type_magn; // M:magnetic
	utils::optional<double> speed_kn;
	utils::optional<char> unit_speed_kn; // N:knots
	utils::optional<double> speed_kmh;
	utils::optional<char> unit_speed_kmh; // K:kilometers per hour
	utils::optional<char> faa_mode_indicator; // NMEA 2.3 or newer

public:
	decltype(track_true) get_track_true() const { return track_true; }
	decltype(type_true) get_type_true() const { return type_true; }
	decltype(track_magn) get_track_magn() const { return track_magn; }
	decltype(type_magn) get_type_magn() const { return type_magn; }
	decltype(speed_kn) get_speed_kn() const { return speed_kn; }
	decltype(unit_speed_kn) get_unit_speed_kn() const { return unit_speed_kn; }
	decltype(speed_kmh) get_speed_kmh() const { return speed_kmh; }
	decltype(unit_speed_kmh) get_unit_speed_kmh() const { return unit_speed_kmh; }
	decltype(faa_mode_indicator) get_faa_mode_indicator() const { return faa_mode_indicator; }

	void set_track_true(double t);
	void set_track_magn(double t);
	void set_speed_kn(double t);
	void set_speed_kmh(double t);
	void set_mode_indicator(char t) { faa_mode_indicator = t; }
};
}
}

#endif
