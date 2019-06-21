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
	constexpr static sentence_id ID = sentence_id::TDS;
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
	double distance_ = 0.0;
	nmea::unit::distance distance_unit_ = nmea::unit::distance::meter;

public:
	decltype(distance_) get_distance() const { return distance_; }
	decltype(distance_unit_) get_distance_unit() const { return distance_unit_; }

	void set_distance(double t) noexcept
	{
		distance_ = t;
		distance_unit_ = nmea::unit::distance::meter;
	}
};
}
}

#endif
