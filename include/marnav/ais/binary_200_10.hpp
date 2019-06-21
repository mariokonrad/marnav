#ifndef MARNAV__AIS__BINARY_200_10__HPP
#define MARNAV__AIS__BINARY_200_10__HPP

#include <marnav/ais/binary_data.hpp>

namespace marnav
{
namespace ais
{
/// @brief Inland ship static and voyage related data (Inland AIS).
///
class binary_200_10 final : public binary_data
{
public:
	/// This offset is the size of the header of the binary message 08,
	/// which carries the binary information of this class.
	/// For convenience (see bitset value mapping below), the offsets
	/// are the same as the documentation for easier reading and understanding.
	/// It is also less error prone. This means however, the offset
	/// must be computed, which is a minor nuisance, especially since
	/// the header of the message 08 must not be included in this header.
	constexpr static uint32_t MSG08_HEAD = 56;

	constexpr static uint32_t SIZE_BITS = 168 - MSG08_HEAD;

	enum class loaded_state : uint8_t { not_available = 0, unloaded = 1, loaded = 2 };

	binary_200_10();

	void read_from(const raw & payload);
	void write_to(raw & payload) const;

private:
	// clang-format off
	bitset_value< 56 - MSG08_HEAD,  8, std::string > vessel_id;
	bitset_value<104 - MSG08_HEAD, 13, uint32_t    > length = 0;
	bitset_value<117 - MSG08_HEAD, 10, uint32_t    > beam = 0;
	bitset_value<127 - MSG08_HEAD, 14, uint32_t    > shiptype = 8000; // TODO: enumeration
	bitset_value<141 - MSG08_HEAD,  3, uint32_t    > hazard = 5;
	bitset_value<144 - MSG08_HEAD, 11, uint32_t    > draught = 0;
	bitset_value<155 - MSG08_HEAD,  2, loaded_state> loaded = loaded_state::not_available;
	bitset_value<157 - MSG08_HEAD,  1, bool        > speed_q = false;
	bitset_value<158 - MSG08_HEAD,  1, bool        > course_q = false;
	bitset_value<159 - MSG08_HEAD,  1, bool        > heading_q = false;
	// clang-format on

public:
	std::string get_vessel_id() const;
	double get_length() const;
	double get_beam() const;
	uint32_t get_shiptype() const { return shiptype; }
	uint32_t get_hazard() const { return hazard; }
	double get_draught() const;
	loaded_state get_loaded() const { return loaded; }
	bool get_speed_q() const { return speed_q; }
	bool get_course_q() const { return course_q; }
	bool get_heading_q() const { return heading_q; }

	void set_vessel_id(const std::string & t);
	void set_length(double t);
	void set_beam(double t);
	void set_shiptype(uint32_t t) { shiptype = t; }
	void set_hazard(uint32_t t) { hazard = t; }
	void set_draught(double t);
	void set_loaded(loaded_state t) { loaded = t; }
	void set_speed_q(bool t) { speed_q = t; }
	void set_course_q(bool t) { course_q = t; }
	void set_heading_q(bool t) { heading_q = t; }
};
}
}

#endif
