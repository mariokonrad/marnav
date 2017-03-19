#ifndef MARNAV__NMEA__TDS__HPP
#define MARNAV__NMEA__TDS__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief TDS - Trawl Door Spread Distance
///
/// @code
///        1   2
///        |   |
/// $--TDS,x.x,M*hh<CR><LF>
/// @endcode
///
/// Field Number
/// 1. Distance between trawl doors in meters (0..300)
/// 2. Units
///    - M = Meters
///
class tds : public sentence
{
	friend class detail::factory;

public:
	constexpr static const sentence_id ID = sentence_id::TDS;
	constexpr static const char * TAG = "TDS";

	tds();
	tds(const tds &) = default;
	tds & operator=(const tds &) = default;
	tds(tds &&) = default;
	tds & operator=(tds &&) = default;

protected:
	tds(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	double distance = 0.0;
	nmea::unit::distance distance_unit = nmea::unit::distance::meter;

public:
	decltype(distance) get_distance() const { return distance; }
	decltype(distance_unit) get_distance_unit() const { return distance_unit; }

	void set_distance(double t) noexcept
	{
		distance = t;
		distance_unit = nmea::unit::distance::meter;
	}
};
}
}

#endif
