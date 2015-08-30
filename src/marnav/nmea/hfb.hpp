#ifndef __NMEA__HFB__HPP__
#define __NMEA__HFB__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief HFB - Trawl Headrope to Footrope and Bottom
///
/// @code
///        1   2 3   4
///        |   | |   |
/// $--HFB,x.x,M,y.y,M*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Distance from headrope to footrope in meters (0..100)
/// 2. Unit of distance headrope to footrope
///    - M = Meters
/// 3. Distance from headrope to bottom in meters (0..100)
/// 4. Unit of distance headrope to bottom
///    - M = Meters
///
class hfb : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::HFB;
	constexpr static const char * TAG = "HFB";

	hfb();
	hfb(const hfb &) = default;
	hfb & operator=(const hfb &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument,
		std::runtime_error);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	double distance_head_foot;
	unit::distance distance_head_foot_unit;
	double distance_head_bottom;
	unit::distance distance_head_bottom_unit;

public:
	NMEA_GETTER(distance_head_foot)
	NMEA_GETTER(distance_head_foot_unit)
	NMEA_GETTER(distance_head_bottom)
	NMEA_GETTER(distance_head_bottom_unit)

	void set_head_foot(double t)
	{
		distance_head_foot = t;
		distance_head_foot_unit = unit::distance::METER;
	};
	void set_head_bottom(double t)
	{
		distance_head_bottom = t;
		distance_head_bottom_unit = unit::distance::METER;
	};
};
}
}

#endif
