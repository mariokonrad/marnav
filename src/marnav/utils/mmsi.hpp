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
	explicit mmsi(uint32_t t)
		: value(t)
	{
	}

	mmsi(const mmsi &) = default;
	mmsi(mmsi &&) = default;
	mmsi & operator=(const mmsi &) = default;

	operator uint32_t() const { return value; }

	uint32_t regular_mid() const
	{
		if (!is_regular())
			return 0;
		return (value / 1000000) % 1000;
	}

	uint32_t regular_id() const
	{
		if (!is_regular())
			return 0;
		return value % 1000000;
	}

	uint32_t group_mid() const
	{
		if (!is_group())
			return 0;
		return (value / 100000) % 1000;
	}

	uint32_t group_id() const
	{
		if (!is_group())
			return 0;
		return value % 100000;
	}

	uint32_t coastal_mid() const
	{
		if (!is_coastal())
			return 0;
		return (value / 10000) % 1000;
	}

	uint32_t coastal_id() const
	{
		if (!is_coastal())
			return 0;
		return value % 10000;
	}

	uint32_t auxiliary_mid() const
	{
		if (!is_auxiliary())
			return 0;
		return (value / 10000) % 1000;
	}

	uint32_t auxiliary_id() const
	{
		if (!is_auxiliary())
			return 0;
		return value % 10000;
	}

	uint32_t mob_mid() const
	{
		if (!is_mob())
			return 0;
		return (value / 1000) % 1000;
	}

	uint32_t mob_id() const
	{
		if (!is_mob())
			return 0;
		return value % 1000;
	}

	/// True if MIDxxxxxx
	inline bool is_regular() const
	{
		const uint32_t m = (value / 1000000) % 1000;
		return (m >= 200) && (m < 900);
	}

	/// True if 0MIDxxxxx
	inline bool is_group() const
	{
		const uint32_t p = value / 100000000;
		const uint32_t m = (value / 100000) % 1000;
		return (p == 0) && (m >= 100) && !is_auxiliary() && !is_ais_aids();
	}

	/// True if 00MIDxxxx
	inline bool is_coastal() const
	{
		const uint32_t p = value / 10000000;
		return p == 0;
	}

	/// True if 00MID0000 and same MID.
	inline bool is_all_coastal_for(uint32_t mid) const
	{
		const uint32_t p = value / 10000000;
		const uint32_t m = (value / 10000) % 1000;
		const uint32_t i = value % 10000;
		return (p == 0) && (m == mid) && (mid >= 100) && (i == 0);
	}

	/// True if 009990000
	inline bool is_all_coastal() const
	{
		const uint32_t p = value / 10000000;
		const uint32_t m = (value / 10000) % 1000;
		const uint32_t i = value % 10000;
		return (p == 0) && (m == 999) && (i == 0);
	}

	/// True if 98MIDxxxx
	inline bool is_auxiliary() const
	{
		const uint32_t p = value / 10000000;
		return p == 98;
	}

	/// True if 99MIDxxxx
	inline bool is_ais_aids() const
	{
		const uint32_t p = value / 10000000;
		return p == 99;
	}

	/// True if 111MIDxxx
	inline bool is_sar_aircraft() const
	{
		const uint32_t p = (value / 1000000) % 1000;
		return p == 111;
	}

	/// True if 970MIDxxx
	inline bool is_sart() const
	{
		const uint32_t p = (value / 1000000) % 1000;
		return p == 970;
	}

	/// True if 972MIDxxx
	inline bool is_mob() const
	{
		const uint32_t p = (value / 1000000) % 1000;
		return p == 972;
	}

	/// True if 974MIDxxx
	inline bool is_epirb_ais() const
	{
		const uint32_t p = (value / 1000000) % 1000;
		return p == 974;
	}

private:
	uint32_t value;
};
}
}

#endif
