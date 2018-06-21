#ifndef MARNAV__NMEA__TLL__HPP
#define MARNAV__NMEA__TLL__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/nmea/waypoint.hpp>
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
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::TLL;
	constexpr static const char * TAG = "TLL";

	tll();
	tll(const tll &) = default;
	tll & operator=(const tll &) = default;
	tll(tll &&) = default;
	tll & operator=(tll &&) = default;

protected:
	tll(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	uint32_t number_ = 0;
	geo::latitude lat_;
	direction lat_hem_ = direction::north;
	geo::longitude lon_;
	direction lon_hem_ = direction::east;
	waypoint name_;
	nmea::time time_utc_;
	target_status status_ = target_status::tracking;
	utils::optional<char> reference_target_;

public:
	decltype(number_) get_number() const { return number_; }
	decltype(name_) get_name() const { return name_; }
	decltype(time_utc_) get_time_utc() const { return time_utc_; }
	decltype(status_) get_status() const { return status_; }
	decltype(reference_target_) get_reference_target() const { return reference_target_; }

	geo::longitude get_longitude() const;
	geo::latitude get_latitude() const;

	void set_number(uint32_t t) noexcept { number_ = t; }
	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_name(const waypoint & t) { name_ = t; }
	void set_time_utc(const nmea::time & t) noexcept { time_utc_ = t; }
	void set_status(target_status t) noexcept { status_ = t; }
	void set_reference_target(char t) noexcept { reference_target_ = t; }
};
}
}

#endif
