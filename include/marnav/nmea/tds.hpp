#ifndef MARNAV_NMEA_TDS_HPP
#define MARNAV_NMEA_TDS_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/units/units.hpp>
#include <optional>

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
	virtual void append_data_to(std::string &, const version &) const override;

private:
	units::meters distance_;

public:
	units::length get_distance() const { return {distance_}; }

	void set_distance(units::length t) noexcept { distance_ = t.get<units::meters>(); }
};
}
}

#endif
