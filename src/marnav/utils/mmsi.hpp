#ifndef __UTILS__MMSI__HPP__
#define __UTILS__MMSI__HPP__

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

	value_type regular_mid() const
	{
		if (!is_regular())
			return 0;
		return (value / 1000000) % 1000;
	}

	value_type regular_id() const
	{
		if (!is_regular())
			return 0;
		return value % 1000000;
	}

	value_type group_mid() const
	{
		if (!is_group())
			return 0;
		return (value / 100000) % 1000;
	}

	value_type group_id() const
	{
		if (!is_group())
			return 0;
		return value % 100000;
	}

	value_type coastal_mid() const
	{
		if (!is_coastal())
			return 0;
		return (value / 10000) % 1000;
	}

	value_type coastal_id() const
	{
		if (!is_coastal())
			return 0;
		return value % 10000;
	}

	value_type auxiliary_mid() const
	{
		if (!is_auxiliary())
			return 0;
		return (value / 10000) % 1000;
	}

	value_type auxiliary_id() const
	{
		if (!is_auxiliary())
			return 0;
		return value % 10000;
	}

	value_type mob_mid() const
	{
		if (!is_mob())
			return 0;
		return (value / 1000) % 1000;
	}

	value_type mob_id() const
	{
		if (!is_mob())
			return 0;
		return value % 1000;
	}

	/// True if MIDxxxxxx
	inline bool is_regular() const
	{
		const value_type m = (value / 1000000) % 1000;
		return (m >= 200) && (m < 900);
	}

	/// True if 0MIDxxxxx
	inline bool is_group() const
	{
		const value_type p = value / 100000000;
		const value_type m = (value / 100000) % 1000;
		return (p == 0) && (m >= 100) && !is_auxiliary() && !is_ais_aids();
	}

	/// True if 00MIDxxxx
	inline bool is_coastal() const
	{
		const value_type p = value / 10000000;
		return p == 0;
	}

	/// True if 00MID0000 and same MID.
	inline bool is_all_coastal_for(value_type mid) const
	{
		const value_type p = value / 10000000;
		const value_type m = (value / 10000) % 1000;
		const value_type i = value % 10000;
		return (p == 0) && (m == mid) && (mid >= 100) && (i == 0);
	}

	/// True if 009990000
	inline bool is_all_coastal() const
	{
		const value_type p = value / 10000000;
		const value_type m = (value / 10000) % 1000;
		const value_type i = value % 10000;
		return (p == 0) && (m == 999) && (i == 0);
	}

	/// True if 98MIDxxxx
	inline bool is_auxiliary() const
	{
		const value_type p = value / 10000000;
		return p == 98;
	}

	/// True if 99MIDxxxx
	inline bool is_ais_aids() const
	{
		const value_type p = value / 10000000;
		return p == 99;
	}

	/// True if 111MIDxxx
	inline bool is_sar_aircraft() const
	{
		const value_type p = (value / 1000000) % 1000;
		return p == 111;
	}

	/// True if 970MIDxxx
	inline bool is_sart() const
	{
		const value_type p = (value / 1000000) % 1000;
		return p == 970;
	}

	/// True if 972MIDxxx
	inline bool is_mob() const
	{
		const value_type p = (value / 1000000) % 1000;
		return p == 972;
	}

	/// True if 974MIDxxx
	inline bool is_epirb_ais() const
	{
		const value_type p = (value / 1000000) % 1000;
		return p == 974;
	}

private:
	value_type value;
};
}
}

#endif
