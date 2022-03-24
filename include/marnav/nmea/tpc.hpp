#ifndef MARNAV_NMEA_TPC_HPP
#define MARNAV_NMEA_TPC_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/units/units.hpp>
#include <optional>

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
	virtual void append_data_to(std::string &, const version &) const override;

private:
	units::meters distance_centerline_;
	units::meters distance_transducer_;
	units::meters depth_;

public:
	units::length get_distance_centerline() const { return {distance_centerline_}; }
	units::length get_distance_transducer() const { return {distance_transducer_}; }
	units::length get_depth() const { return {depth_}; }

	void set_distance_centerline(units::length t) noexcept
	{
		distance_centerline_ = t.get<units::meters>();
	}

	void set_distance_transducer(units::length t) noexcept
	{
		distance_transducer_ = t.get<units::meters>();
	}

	void set_depth(units::length t) noexcept { depth_ = t.get<units::meters>(); }
};
}
}

#endif
