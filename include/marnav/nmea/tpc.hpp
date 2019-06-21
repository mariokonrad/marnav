#ifndef MARNAV__NMEA__TPC__HPP
#define MARNAV__NMEA__TPC__HPP

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
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::TPC;
	constexpr static const char * TAG = "TPC";

	tpc();
	tpc(const tpc &) = default;
	tpc & operator=(const tpc &) = default;
	tpc(tpc &&) = default;
	tpc & operator=(tpc &&) = default;

protected:
	tpc(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	double distance_centerline_ = 0.0;
	unit::distance distance_centerline_unit_ = unit::distance::meter;
	double distance_transducer_ = 0.0;
	unit::distance distance_transducer_unit_ = unit::distance::meter;
	double depth_ = 0.0;
	unit::distance depth_unit_ = unit::distance::meter;

public:
	decltype(distance_centerline_) get_distance_centerline() const
	{
		return distance_centerline_;
	}
	decltype(distance_centerline_unit_) get_distance_centerline_unit() const
	{
		return distance_centerline_unit_;
	}
	decltype(distance_transducer_) get_distance_transducer() const
	{
		return distance_transducer_;
	}
	decltype(distance_transducer_unit_) get_distance_transducer_unit() const
	{
		return distance_transducer_unit_;
	}
	decltype(depth_) get_depth() const { return depth_; }
	decltype(depth_unit_) get_depth_unit() const { return depth_unit_; }

	void set_distance_centerline(double t) noexcept
	{
		distance_centerline_ = t;
		distance_centerline_unit_ = unit::distance::meter;
	}
	void set_distance_transducer(double t) noexcept
	{
		distance_transducer_ = t;
		distance_centerline_unit_ = unit::distance::meter;
	}
	void set_depth(double t) noexcept
	{
		depth_ = t;
		distance_centerline_unit_ = unit::distance::meter;
	}
};
}
}

#endif
