#ifndef MARNAV__UTILS__MMSI__HPP
#define MARNAV__UTILS__MMSI__HPP

#include <cstdint>

namespace marnav
{
namespace utils
{

/// @brief Represents a MMSI (Maritime Mobile Service Identiy).
///
/// @see http://www.navcen.uscg.gov/?pageName=mtMmsi
///
/// @note Not all variations and criterias are implemented.
///
class mmsi
{
public:
	using value_type = uint32_t;

	static constexpr value_type initial_value = 0;

	mmsi() noexcept {}

	explicit mmsi(value_type t) noexcept
		: value_(t)
	{
	}

	mmsi(const mmsi &) = default;
	mmsi(mmsi &&) noexcept = default;
	mmsi & operator=(const mmsi &) = default;
	mmsi & operator=(mmsi &&) noexcept = default;

	bool operator==(const mmsi & other) const;
	bool operator!=(const mmsi & other) const;

	operator value_type() const { return value_; }

	value_type mid() const;

	value_type regular_mid() const;
	value_type regular_id() const;
	value_type group_mid() const;
	value_type group_id() const;
	value_type coastal_mid() const;
	value_type coastal_id() const;
	value_type auxiliary_mid() const;
	value_type auxiliary_id() const;
	value_type mob_mid() const;
	value_type mob_id() const;
	value_type sar_mid() const;

	bool is_regular() const;
	bool is_group() const;
	bool is_coastal() const;
	bool is_all_coastal_for(value_type mid) const;
	bool is_all_coastal() const;
	bool is_auxiliary() const;
	bool is_ais_aids() const;
	bool is_sar_aircraft() const;
	bool is_sart() const;
	bool is_mob() const;
	bool is_epirb_ais() const;

private:
	value_type value_ = initial_value;
};
}
}

#endif
