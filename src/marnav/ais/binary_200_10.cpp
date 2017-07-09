#include "binary_200_10.hpp"
#include <algorithm>
#include <cmath>

namespace marnav
{
namespace ais
{
binary_200_10::binary_200_10()
	: vessel_id("@@@@@@@@")
{
}

void binary_200_10::read_from(const raw & payload)
{
	if (payload.size() != SIZE_BITS)
		throw std::invalid_argument{"wrong number of bits in playload of binary_200_10"};

	get(payload, vessel_id);
	get(payload, length);
	get(payload, beam);
	get(payload, shiptype);
	get(payload, hazard);
	get(payload, draught);
	get(payload, loaded);
	get(payload, speed_q);
	get(payload, course_q);
	get(payload, heading_q);
}

void binary_200_10::write_to(raw & payload) const
{
	payload = raw(SIZE_BITS);
	set(payload, vessel_id);
	set(payload, length);
	set(payload, beam);
	set(payload, shiptype);
	set(payload, hazard);
	set(payload, draught);
	set(payload, loaded);
	set(payload, speed_q);
	set(payload, course_q);
	set(payload, heading_q);
}

std::string binary_200_10::get_vessel_id() const
{
	return trim_ais_string(vessel_id);
}

void binary_200_10::set_vessel_id(const std::string & t)
{
	if (t.size() > 8) {
		vessel_id = t.substr(0, 8);
	} else {
		vessel_id = t;
	}
}

/// Returns the lenght in meters.
double binary_200_10::get_length() const
{
	return 0.1 * length;
}

void binary_200_10::set_length(double t)
{
	length = std::max(0u, std::min(8000u, static_cast<uint32_t>(std::round(10.0 * t))));
}

/// Returns the beam in meters.
double binary_200_10::get_beam() const
{
	return 0.1 * beam;
}

void binary_200_10::set_beam(double t)
{
	beam = std::max(0u, std::min(1000u, static_cast<uint32_t>(std::round(10.0 * t))));
}

/// Returns the draught in meters.
double binary_200_10::get_draught() const
{
	return 0.01 * draught;
}

void binary_200_10::set_draught(double t)
{
	draught = std::max(0u, std::min(200u, static_cast<uint32_t>(std::round(100.0 * t))));
}
}
}
