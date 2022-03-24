#ifndef MARNAV_NMEA_ITS_HPP
#define MARNAV_NMEA_ITS_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/units/units.hpp>
#include <optional>

namespace marnav
{
namespace nmea
{
/// @brief ITS - Trawl Door Spread 2 Distance
///
/// @code
///        1   2
///        |   |
/// $--ITS,x.x,M*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Second spread distance
/// 2. Unit of distance
///    - M = Meters
///
class its : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::ITS;
	constexpr static const char * TAG = "ITS";

	its();
	its(const its &) = default;
	its & operator=(const its &) = default;
	its(its &&) = default;
	its & operator=(its &&) = default;

protected:
	its(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	units::meters distance_;

public:
	units::length get_distance() const { return {distance_}; }

	void set_distance(units::length t) noexcept { distance_ = t.get<units::meters>(); };
};
}
}

#endif
