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
///        1       2 3        4 5         6 7   8
///        |       | |        | |         | |   |
/// $--GLL,llll.ll,a,yyyyy.yy,a,hhmmss.ss,a,m,*hh<CR><LF>
/// @endcode
///
/// Field Number:
///
///  1. Latitude
///  2. N or S (North or South)
///  3. Longitude
///  4. E or W (East or West)
///  5. Universal Time Coordinated (UTC)
///  6. Status A - Data Valid, V - Data Invalid
///  7. FAA mode indicator (NMEA 2.3 and later)
///  8. Checksum
///
class gll : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::GLL;

	gll();
	gll(const gll &) = default;
	gll & operator=(const gll &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<geo::latitude> lat;
	utils::optional<char> lat_hem;
	utils::optional<geo::longitude> lon;
	utils::optional<char> lon_hem;
	utils::optional<nmea::time> time_utc;
	utils::optional<char> status;

public:
	decltype(lat) get_lat() const { return lat; }
	decltype(lat_hem) get_lat_hem() const { return lat_hem; }
	decltype(lon) get_lon() const { return lon; }
	decltype(lon_hem) get_lon_hem() const { return lon_hem; }
	decltype(time_utc) get_time_utc() const { return time_utc; }
	decltype(status) get_status() const { return status; }

	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_time_utc(const nmea::time & t) { time_utc = t; }
	void set_status(char t) { status = t; }
};
}
}

#endif
