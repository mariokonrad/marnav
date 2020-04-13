#ifndef MARNAV_AIS_VESSEL_DIMENSION_HPP
#define MARNAV_AIS_VESSEL_DIMENSION_HPP

#include <marnav/units/units.hpp>

namespace marnav
{
namespace ais
{
class vessel_dimension
{
	friend class message_05;
	friend class message_19;
	friend class message_21;
	friend class message_24;

public:
	vessel_dimension() = default;

	vessel_dimension(units::meters to_bow, units::meters to_stern, units::meters to_port,
		units::meters to_starboard);

	units::meters get_to_bow() const noexcept;
	units::meters get_to_stern() const noexcept;
	units::meters get_to_port() const noexcept;
	units::meters get_to_starboard() const noexcept;

	units::meters length() const noexcept;
	units::meters width() const noexcept;

	// Resolution of length is 1m, specified value is rounded.
	void set_to_bow(units::length t);

	// Resolution of length is 1m, specified value is rounded.
	void set_to_stern(units::length t);

	// Resolution of length is 1m, specified value is rounded.
	void set_to_port(units::length t);

	// Resolution of length is 1m, specified value is rounded.
	void set_to_starboard(units::length t);

private:
	uint32_t to_bow_ = 0u; // raw data, in meters
	uint32_t to_stern_ = 0u; // raw data, in meters
	uint32_t to_port_ = 0u; // raw data, in meters
	uint32_t to_starboard_ = 0u; // raw data, in meters

	vessel_dimension(
		uint32_t to_bow, uint32_t to_stern, uint32_t to_port, uint32_t to_starboard)
		: to_bow_(to_bow)
		, to_stern_(to_stern)
		, to_port_(to_port)
		, to_starboard_(to_starboard)
	{
	}

	uint32_t get_raw_to_bow() const noexcept { return to_bow_; }
	uint32_t get_raw_to_stern() const noexcept { return to_stern_; }
	uint32_t get_raw_to_port() const noexcept { return to_port_; }
	uint32_t get_raw_to_starboard() const noexcept { return to_starboard_; }
};
}
}

#endif
