#ifndef __MARNAV__NMEA__TPC__HPP__
#define __MARNAV__NMEA__TPC__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(tpc)

/// @brief TPC - Trawl Position Cartesian Coordinates
///
/// @code
///        1 2 3 4  5  6
///        | | | |  |  |
/// $--TPC,x,M,y,P,z.z,M*hh,<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Horizontal distance from the vessel center line
/// 2. Unit of horizontal distance
///    - M = Meters
/// 3. Horizontal distance from the transducer to the trawl along the vessel
///    center line. The value is normally positive assuming the trawl is located
///    behind the vessel.
/// 4. Unit of horizontal distance from transducer to the trawl
///    - M = Meters
/// 5. Depth of the trawl below the surface
/// 6. Unit of Depth
///    - M = Meters
///
class tpc : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(tpc)

public:
	constexpr static const sentence_id ID = sentence_id::TPC;
	constexpr static const char * TAG = "TPC";

	tpc();
	tpc(const tpc &) = default;
	tpc & operator=(const tpc &) = default;
	tpc(tpc &&) = default;
	tpc & operator=(tpc &&) = default;

protected:
	tpc(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	double distance_centerline = 0.0;
	unit::distance distance_centerline_unit = unit::distance::meter;
	double distance_transducer = 0.0;
	unit::distance distance_transducer_unit = unit::distance::meter;
	double depth = 0.0;
	unit::distance depth_unit = unit::distance::meter;

public:
	decltype(distance_centerline) get_distance_centerline() const
	{
		return distance_centerline;
	}
	decltype(distance_centerline_unit) get_distance_centerline_unit() const
	{
		return distance_centerline_unit;
	}
	decltype(distance_transducer) get_distance_transducer() const
	{
		return distance_transducer;
	}
	decltype(distance_transducer_unit) get_distance_transducer_unit() const
	{
		return distance_transducer_unit;
	}
	decltype(depth) get_depth() const { return depth; }
	decltype(depth_unit) get_depth_unit() const { return depth_unit; }

	void set_distance_centerline(double t) noexcept
	{
		distance_centerline = t;
		distance_centerline_unit = unit::distance::meter;
	}
	void set_distance_transducer(double t) noexcept
	{
		distance_transducer = t;
		distance_centerline_unit = unit::distance::meter;
	}
	void set_depth(double t) noexcept
	{
		depth = t;
		distance_centerline_unit = unit::distance::meter;
	}
};
}
}

#endif
