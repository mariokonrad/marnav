#ifndef __NMEA__ITS__HPP__
#define __NMEA__ITS__HPP__

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
public:
	constexpr static const sentence_id ID = sentence_id::ITS;
	constexpr static const char * TAG = "ITS";

	its();
	its(const its &) = default;
	its & operator=(const its &) = default;

	static std::unique_ptr<sentence> parse(
		const std::string & talker, const std::vector<std::string> & fields);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	double distance;
	unit::distance distance_unit;

public:
	NMEA_GETTER(distance)
	NMEA_GETTER(distance_unit)

	void set_distance(double t) noexcept
	{
		distance = t;
		distance_unit = unit::distance::METER;
	};
};
}
}

#endif
