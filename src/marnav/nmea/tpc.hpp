#ifndef __NMEA__TPC__HPP__
#define __NMEA__TPC__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

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
public:
	constexpr static const sentence_id ID = sentence_id::TPC;
	constexpr static const char * TAG = "TPC";

	tpc();
	tpc(const tpc &) = default;
	tpc & operator=(const tpc &) = default;

	static std::unique_ptr<sentence> parse(
		const std::string & talker, const std::vector<std::string> & fields);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	double distance_centerline;
	unit::distance distance_centerline_unit;
	double distance_transducer;
	unit::distance distance_transducer_unit;
	double depth;
	unit::distance depth_unit;

public:
	NMEA_GETTER(distance_centerline)
	NMEA_GETTER(distance_centerline_unit)
	NMEA_GETTER(distance_transducer)
	NMEA_GETTER(distance_transducer_unit)
	NMEA_GETTER(depth)
	NMEA_GETTER(depth_unit)

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
