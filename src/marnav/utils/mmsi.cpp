#include <marnav/utils/mmsi.hpp>

namespace marnav
{
namespace utils
{
bool mmsi::operator==(const mmsi & other) const
{
	// not comparing (this == &other) because the comparison
	// of the value is trivial.
	return value_ == other.value_;
}

bool mmsi::operator!=(const mmsi & other) const
{
	return !(*this == other);
}

/// This function is for convenience. It tries to find
/// out about the type of MMSI, and returns the appropriate MID.
/// If there is no MID, `initial_value` will return.
mmsi::value_type mmsi::mid() const
{
	if (is_regular())
		return regular_mid();
	if (is_group())
		return group_mid();
	if (is_coastal())
		return coastal_mid();
	if (is_auxiliary())
		return auxiliary_mid();
	if (is_sar_aircraft())
		return sar_mid();
	return initial_value;
}

/// This function is for convenience. It tries to find
/// out about the type of MMSI, and returns the appropriate ID.
/// If there is no ID, `initial_value` will return.
mmsi::value_type mmsi::id() const
{
	if (is_regular())
		return regular_id();
	if (is_group())
		return group_id();
	if (is_coastal())
		return coastal_id();
	if (is_auxiliary())
		return auxiliary_id();
	if (is_sar_aircraft())
		return sar_id();
	if (is_mob())
		return mob_id();
	if (is_sart())
		return sart_id();
	if (is_epirb_ais())
		return epirb_ais_id();
	if (is_ais_aids())
		return ais_aids_id();
	return initial_value;
}

/// This function is for convenience. It tries to find
/// out about the type of MMSI, and returns the appropriate manufacturer ID.
/// If there is no manufacturer ID, `initial_value` will return.
mmsi::value_type mmsi::man() const
{
	if (is_sart())
		return sart_man();
	if (is_mob())
		return mob_man();
	if (is_epirb_ais())
		return epirb_ais_man();
	return initial_value;
}

/// Returns MID of MIDxxxxxx
mmsi::value_type mmsi::regular_mid() const
{
	if (!is_regular())
		return initial_value;
	return (value_ / 1000000u) % 1000u;
}

/// Returns ID of MIDaaaaaa
mmsi::value_type mmsi::regular_id() const
{
	if (!is_regular())
		return initial_value;
	return value_ % 1000000;
}

/// Returns MID of 0MIDxxxxx
mmsi::value_type mmsi::group_mid() const
{
	if (!is_group())
		return initial_value;
	return (value_ / 100000u) % 1000u;
}

/// Returns ID of 0MIDaaaaa
mmsi::value_type mmsi::group_id() const
{
	if (!is_group())
		return initial_value;
	return value_ % 100000u;
}

/// Returns MID of 00MIDxxxx
mmsi::value_type mmsi::coastal_mid() const
{
	if (!is_coastal())
		return initial_value;
	return (value_ / 10000u) % 1000u;
}

/// Returns ID of 00MIDaaaa
mmsi::value_type mmsi::coastal_id() const
{
	if (!is_coastal())
		return initial_value;
	return value_ % 10000u;
}

/// Returns MID of 98MIDxxxx
mmsi::value_type mmsi::auxiliary_mid() const
{
	if (!is_auxiliary())
		return initial_value;
	return (value_ / 10000u) % 1000u;
}

/// Returns ID of 98MIDaaaa
mmsi::value_type mmsi::auxiliary_id() const
{
	if (!is_auxiliary())
		return initial_value;
	return value_ % 10000u;
}

/// Returns ID of 972xaaaa
mmsi::value_type mmsi::mob_id() const
{
	if (!is_mob())
		return initial_value;
	return value_ % 10000u;
}

/// Return MID of 111MIDxxx
mmsi::value_type mmsi::sar_mid() const
{
	if (!is_sar_aircraft())
		return initial_value;
	return (value_ / 1000u) % 1000u;
}

/// Returns ID of 111MIDaaa
mmsi::value_type mmsi::sar_id() const
{
	if (!is_sar_aircraft())
		return initial_value;
	return value_ % 1000u;
}

/// Returns MID of 970xxaaaa
mmsi::value_type mmsi::sart_id() const
{
	if (!is_sart())
		return initial_value;
	return value_ % 10000u;
}

/// Returns ID of 974xxaaaaa
mmsi::value_type mmsi::epirb_ais_id() const
{
	if (!is_epirb_ais())
		return initial_value;
	return value_ % 10000u;
}

/// Returns ID of 99MIDxxxx
mmsi::value_type mmsi::ais_aids_id() const
{
	if (!is_ais_aids())
		return initial_value;
	return value_ % 10000u;
}

/// Returns manufacturer ID of 970IDxxxx
mmsi::value_type mmsi::sart_man() const
{
	if (!is_sart())
		return initial_value;
	return (value_ / 10000u) % 100u;
}

/// Returns manufacturer ID of 972IDxxxx
mmsi::value_type mmsi::mob_man() const
{
	if (!is_mob())
		return initial_value;
	return (value_ / 10000u) % 100u;
}

/// Returns manufacturer ID of 974IDxxxx
mmsi::value_type mmsi::epirb_ais_man() const
{
	if (!is_epirb_ais())
		return initial_value;
	return (value_ / 10000u) % 100u;
}

/// True if MIDxxxxxx
bool mmsi::is_regular() const
{
	const value_type m = (value_ / 1000000) % 1000;
	return (m >= 200u) && (m < 900u);
}

/// True if 0MIDxxxxx
bool mmsi::is_group() const
{
	const value_type p = value_ / 100000000u;
	const value_type m = (value_ / 100000u) % 1000u;
	return (p == 0u) && (m >= 100u) && !is_auxiliary() && !is_ais_aids();
}

/// True if 00MIDxxxx
bool mmsi::is_coastal() const
{
	const value_type p = value_ / 10000000u;
	return p == 0u;
}

/// True if 00MID0000 and same MID.
bool mmsi::is_all_coastal_for(value_type mid) const
{
	const value_type p = value_ / 10000000u;
	const value_type m = (value_ / 10000u) % 1000u;
	const value_type i = value_ % 10000u;
	return (p == 0u) && (m == mid) && (mid >= 100u) && (i == 0u);
}

/// True if 009990000
bool mmsi::is_all_coastal() const
{
	const value_type p = value_ / 10000000u;
	const value_type m = (value_ / 10000u) % 1000u;
	const value_type i = value_ % 10000u;
	return (p == 0u) && (m == 999u) && (i == 0u);
}

/// True if 98MIDxxxx
bool mmsi::is_auxiliary() const
{
	const value_type p = value_ / 10000000u;
	return p == 98u;
}

/// True if 99MIDxxxx
bool mmsi::is_ais_aids() const
{
	const value_type p = value_ / 10000000u;
	return p == 99u;
}

/// True if 111MIDxxx
bool mmsi::is_sar_aircraft() const
{
	const value_type p = (value_ / 1000000u) % 1000u;
	return p == 111u;
}

/// True if 970aaxxxx
bool mmsi::is_sart() const
{
	const value_type p = (value_ / 1000000u) % 1000u;
	return p == 970u;
}

/// True if 972aaxxxx
bool mmsi::is_mob() const
{
	const value_type p = (value_ / 1000000u) % 1000u;
	return p == 972u;
}

/// True if 974MIDxxx
bool mmsi::is_epirb_ais() const
{
	const value_type p = (value_ / 1000000u) % 1000u;
	return p == 974u;
}
}
}
