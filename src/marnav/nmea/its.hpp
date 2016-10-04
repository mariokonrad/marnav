#ifndef __NMEA__ITS__HPP__
#define __NMEA__ITS__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(its)

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
	MARNAV_NMEA_SENTENCE_FRIENDS(its)

public:
	constexpr static const sentence_id ID = sentence_id::ITS;
	constexpr static const char * TAG = "ITS";

	its();
	its(const its &) = default;
	its & operator=(const its &) = default;
	its(its &&) = default;
	its & operator=(its &&) = default;

protected:
	its(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	double distance = 0.0;
	unit::distance distance_unit = unit::distance::meter;

public:
	MARNAV_NMEA_GETTER(distance)
	MARNAV_NMEA_GETTER(distance_unit)

	void set_distance(double t) noexcept
	{
		distance = t;
		distance_unit = unit::distance::meter;
	};
};
}
}

#endif
