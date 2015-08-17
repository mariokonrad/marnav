#ifndef __UTILS__MMSI__HPP__
#define __UTILS__MMSI__HPP__

#include <cstdint>

namespace marnav
{
namespace utils
{

/// Represents an MMSI (Maritime Mobile Service Identiy).
///
/// @see http://www.navcen.uscg.gov/?pageName=mtMmsi
class mmsi
{
public:
	using value_type = uint32_t;

	mmsi()
		: value(0)
	{
	}

	explicit mmsi(value_type t)
		: value(t)
	{
	}

	mmsi(const mmsi &) = default;
	mmsi(mmsi &&) = default;
	mmsi & operator=(const mmsi &) = default;

	operator value_type() const { return value; }

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
	value_type value;
};
}
}

#endif
