#ifndef MARNAV__NMEA__ITS__HPP
#define MARNAV__NMEA__ITS__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

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
	virtual void append_data_to(std::string &) const override;

private:
	double distance_ = 0.0;
	unit::distance distance_unit_ = unit::distance::meter;

public:
	decltype(distance_) get_distance() const { return distance_; }
	decltype(distance_unit_) get_distance_unit() const { return distance_unit_; }

	void set_distance(double t) noexcept
	{
		distance_ = t;
		distance_unit_ = unit::distance::meter;
	};
};
}
}

#endif
