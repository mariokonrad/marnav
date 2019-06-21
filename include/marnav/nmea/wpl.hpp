#ifndef MARNAV__NMEA__WPL__HPP
#define MARNAV__NMEA__WPL__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/angle.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief WPL - Waypoint Location
///
/// @code
///        1       2 3        4 5
///        |       | |        | |
/// $--WPL,llll.ll,a,yyyyy.yy,a,c--c*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Latitude
/// 2. Latitude hemisphere
///    - N = North
///    - S = South
/// 3. Longitude
/// 4. Longitude hemisphere
///    - E = East
///    - W = West
/// 5. Waypoint ID
///
class wpl : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::WPL;
	constexpr static const char * TAG = "WPL";

	wpl();
	wpl(const wpl &) = default;
	wpl & operator=(const wpl &) = default;
	wpl(wpl &&) = default;
	wpl & operator=(wpl &&) = default;

protected:
	wpl(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<geo::latitude> lat_;
	utils::optional<direction> lat_hem_; // latitude hemisphere (N or S)
	utils::optional<geo::longitude> lon_;
	utils::optional<direction> lon_hem_; // longitude hemisphere (E or W)
	utils::optional<waypoint> waypoint_id_;

public:
	decltype(waypoint_id_) get_waypoint_id() const { return waypoint_id_; }

	utils::optional<geo::longitude> get_longitude() const;
	utils::optional<geo::latitude> get_latitude() const;

	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_waypoint(const waypoint & id) { waypoint_id_ = id; }
};
}
}

#endif
