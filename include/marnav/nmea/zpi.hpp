#ifndef MARNAV_NMEA_ZPI_HPP
#define MARNAV_NMEA_ZPI_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/nmea/waypoint.hpp>

namespace marnav
{
namespace nmea
{
/// @brief ZPI - Arrival time at point of interest
///
/// @code
///        1         2         3
///        |         |         |
/// $--ZPI,hhmmss.ss,hhmmss.ss,c--c*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Universal Time Coordinated (UTC)
/// 2. Time Remaining
/// 3. Destination Waypoint ID
///
class zpi : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::ZPI;
	constexpr static const char * TAG = "ZPI";

	zpi();
	zpi(const zpi &) = default;
	zpi & operator=(const zpi &) = default;
	zpi(zpi &&) = default;
	zpi & operator=(zpi &&) = default;

protected:
	zpi(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	nmea::time time_utc_;
	nmea::time time_arrival_;
	waypoint waypoint_id_;

public:
	nmea::time get_time_utc() const { return time_utc_; }
	nmea::time get_time_arrival() const { return time_arrival_; }
	waypoint get_waypoint_id() const { return waypoint_id_; }

	void set_time_utc(const nmea::time & t) noexcept { time_utc_ = t; }
	void set_time_arrival(const nmea::time & t) noexcept { time_arrival_ = t; }
	void set_waypoint_id(const waypoint & id) { waypoint_id_ = id; }
};
}
}

#endif
