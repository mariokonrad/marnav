#include <marnav/ais/binary_200_10.hpp>
#include <marnav/utils/clamp.hpp>
#include <algorithm>
#include <cmath>

namespace marnav::ais
{
binary_200_10::binary_200_10()
	: vessel_id_("@@@@@@@@")
{
}

void binary_200_10::read_from(const raw & payload)
{
	if (payload.size() != SIZE_BITS)
		throw std::invalid_argument{"wrong number of bits in playload of binary_200_10"};

	get(payload, vessel_id_);
	get(payload, length_);
	get(payload, beam_);
	get(payload, shiptype_);
	get(payload, hazard_);
	get(payload, draught_);
	get(payload, loaded_);
	get(payload, speed_q_);
	get(payload, course_q_);
	get(payload, heading_q_);
}

void binary_200_10::write_to(raw & payload) const
{
	payload = raw(SIZE_BITS);
	set(payload, vessel_id_);
	set(payload, length_);
	set(payload, beam_);
	set(payload, shiptype_);
	set(payload, hazard_);
	set(payload, draught_);
	set(payload, loaded_);
	set(payload, speed_q_);
	set(payload, course_q_);
	set(payload, heading_q_);
}

std::string binary_200_10::get_vessel_id() const
{
	return trim_ais_string(vessel_id_);
}

void binary_200_10::set_vessel_id(const std::string & t)
{
	if (t.size() > 8) {
		vessel_id_ = t.substr(0, 8);
	} else {
		vessel_id_ = t;
	}
}

/// Returns the lenght in meters.
double binary_200_10::get_length() const
{
	return 0.1 * length_;
}

void binary_200_10::set_length(double t)
{
	length_ = utils::clamp(static_cast<uint32_t>(std::round(10.0 * t)), 0u, 8000u);
}

/// Returns the beam in meters.
double binary_200_10::get_beam() const
{
	return 0.1 * beam_;
}

void binary_200_10::set_beam(double t)
{
	beam_ = utils::clamp(static_cast<uint32_t>(std::round(10.0 * t)), 0u, 1000u);
}

/// Returns the draught in meters.
double binary_200_10::get_draught() const
{
	return 0.01 * draught_;
}

void binary_200_10::set_draught(double t)
{
	draught_ = utils::clamp(static_cast<uint32_t>(std::round(100.0 * t)), 0u, 200u);
}
}
