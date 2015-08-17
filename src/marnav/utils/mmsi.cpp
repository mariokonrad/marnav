#include "mmsi.hpp"

namespace marnav
{
namespace utils
{

mmsi::value_type mmsi::regular_mid() const
{
	if (!is_regular())
		return 0;
	return (value / 1000000) % 1000;
}

mmsi::value_type mmsi::regular_id() const
{
	if (!is_regular())
		return 0;
	return value % 1000000;
}

mmsi::value_type mmsi::group_mid() const
{
	if (!is_group())
		return 0;
	return (value / 100000) % 1000;
}

mmsi::value_type mmsi::group_id() const
{
	if (!is_group())
		return 0;
	return value % 100000;
}

mmsi::value_type mmsi::coastal_mid() const
{
	if (!is_coastal())
		return 0;
	return (value / 10000) % 1000;
}

mmsi::value_type mmsi::coastal_id() const
{
	if (!is_coastal())
		return 0;
	return value % 10000;
}

mmsi::value_type mmsi::auxiliary_mid() const
{
	if (!is_auxiliary())
		return 0;
	return (value / 10000) % 1000;
}

mmsi::value_type mmsi::auxiliary_id() const
{
	if (!is_auxiliary())
		return 0;
	return value % 10000;
}

mmsi::value_type mmsi::mob_mid() const
{
	if (!is_mob())
		return 0;
	return (value / 1000) % 1000;
}

mmsi::value_type mmsi::mob_id() const
{
	if (!is_mob())
		return 0;
	return value % 1000;
}

/// True if MIDxxxxxx
bool mmsi::is_regular() const
{
	const value_type m = (value / 1000000) % 1000;
	return (m >= 200) && (m < 900);
}

/// True if 0MIDxxxxx
bool mmsi::is_group() const
{
	const value_type p = value / 100000000;
	const value_type m = (value / 100000) % 1000;
	return (p == 0) && (m >= 100) && !is_auxiliary() && !is_ais_aids();
}

/// True if 00MIDxxxx
bool mmsi::is_coastal() const
{
	const value_type p = value / 10000000;
	return p == 0;
}

/// True if 00MID0000 and same MID.
bool mmsi::is_all_coastal_for(value_type mid) const
{
	const value_type p = value / 10000000;
	const value_type m = (value / 10000) % 1000;
	const value_type i = value % 10000;
	return (p == 0) && (m == mid) && (mid >= 100) && (i == 0);
}

/// True if 009990000
bool mmsi::is_all_coastal() const
{
	const value_type p = value / 10000000;
	const value_type m = (value / 10000) % 1000;
	const value_type i = value % 10000;
	return (p == 0) && (m == 999) && (i == 0);
}

/// True if 98MIDxxxx
bool mmsi::is_auxiliary() const
{
	const value_type p = value / 10000000;
	return p == 98;
}

/// True if 99MIDxxxx
bool mmsi::is_ais_aids() const
{
	const value_type p = value / 10000000;
	return p == 99;
}

/// True if 111MIDxxx
bool mmsi::is_sar_aircraft() const
{
	const value_type p = (value / 1000000) % 1000;
	return p == 111;
}

/// True if 970MIDxxx
bool mmsi::is_sart() const
{
	const value_type p = (value / 1000000) % 1000;
	return p == 970;
}

/// True if 972MIDxxx
bool mmsi::is_mob() const
{
	const value_type p = (value / 1000000) % 1000;
	return p == 972;
}

/// True if 974MIDxxx
bool mmsi::is_epirb_ais() const
{
	const value_type p = (value / 1000000) % 1000;
	return p == 974;
}
}
}
