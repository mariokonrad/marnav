#ifndef __NMEA__TLL__HPP__
#define __NMEA__TLL__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/geo/angle.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief TLL - Target latitude and longitude
///
/// @code
///        1  2        3 4         5 6    7         8 9
///        |  |        | |         | |    |         | |
/// $--TLL,xx,llll.lll,a,yyyyy.yyy,a,c--c,hhmmss.ss,a,a*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Target number 00 - 99
/// 2. Latitude
/// 3. Latitude hemisphere
///    - N = North
///    - S = South
/// 4. Longitude
/// 5. Longitude hemisphere
///    - E = East
///    - W = West
/// 6. Target name
/// 7. UTC of data
/// 8. Target status
///    - L = lost,tracked target has beenlost
///    - Q = query,target in the process of acquisition
///    - T = tracking
/// 9. Reference target
///    - R
///    - null/empty
///
class tll : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::TLL;
	constexpr static const char * TAG = "TLL";

	tll();
	tll(const tll &) = default;
	tll & operator=(const tll &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	uint32_t target_number;
	geo::latitude lat;
	direction lat_hem;
	geo::longitude lon;
	direction lon_hem;
	std::string target_name;
	nmea::time time_utc;
	char target_status; // @todo use an enumeration
	utils::optional<char> reference_target;

public:
	NMEA_GETTER(target_number)
	NMEA_GETTER(lat)
	NMEA_GETTER(lat_hem)
	NMEA_GETTER(lon)
	NMEA_GETTER(lon_hem)
	NMEA_GETTER(target_name)
	NMEA_GETTER(time_utc)
	NMEA_GETTER(target_status)
	NMEA_GETTER(reference_target)

	void set_target_number(uint32_t t) { target_number = t; }
	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_target_name(const std::string & t);
	void set_time_utc(const nmea::time & t) { time_utc = t; }
	void set_target_status(char t) { target_status = t; }
	void set_reference_target(char t) { reference_target = t; }
};
}
}

#endif
