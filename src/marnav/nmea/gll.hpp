#ifndef __NMEA__GLL__HPP__
#define __NMEA__GLL__HPP__

#include "sentence.hpp"
#include "angle.hpp"
#include "time.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief GLL - Geographic Position - Latitude/Longitude
///
/// @code
///        1       2 3        4 5         6 7
///        |       | |        | |         | |
/// $--GLL,llll.ll,a,yyyyy.yy,a,hhmmss.ss,a,m*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Latitude
/// 2. Latitude hemipsphere
///    - N = North
///    - S = South
/// 3. Longitude
/// 4. Longitude hemisphere
///    - E = East
///    - W = West
/// 5. Time (UTC) of position
/// 6. Status
///    - A = Data Valid
///    - V = Data Invalid
/// 7. Mode indicator (only in newer versions)
///    - V = Invalid
///    - A = Autonomous
///    - D = Differential
///
class gll : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::GLL;
	constexpr static const char * TAG = "GLL";

	gll();
	gll(const gll &) = default;
	gll & operator=(const gll &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<geo::latitude> lat;
	utils::optional<direction> lat_hem;
	utils::optional<geo::longitude> lon;
	utils::optional<direction> lon_hem;
	utils::optional<nmea::time> time_utc;
	utils::optional<char> status;
	utils::optional<char> mode_indicator;

public:
	NMEA_GETTER(lat)
	NMEA_GETTER(lat_hem)
	NMEA_GETTER(lon)
	NMEA_GETTER(lon_hem)
	NMEA_GETTER(time_utc)
	NMEA_GETTER(status)
	NMEA_GETTER(mode_indicator)

	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_time_utc(const nmea::time & t) { time_utc = t; }
	void set_status(char t) { status = t; }
	void set_mode_indicator(char t) { mode_indicator = t; }
};
}
}

#endif
