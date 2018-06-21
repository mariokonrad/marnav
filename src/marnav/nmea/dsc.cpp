#include "dsc.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
namespace
{
/// Converts data read from the NMEA string to the corresponding
/// enumerator.
/// @note This function already takes care about the two lowest digit
///       representation of the values in the string.
///
/// @param[in] value The numerical value to convert.
/// @return The corresponding enumerator.
/// @exception std::invalid_argument The specified value to convert is unknown.
///
static dsc::format_specifier format_specifier_mapping(
	typename std::underlying_type<dsc::format_specifier>::type value)
{
	switch (value) {
		case 2:
			return dsc::format_specifier::geographical_area;
		case 12:
			return dsc::format_specifier::distress;
		case 16:
			return dsc::format_specifier::all_ships;
		case 20:
			return dsc::format_specifier::individual_station;
	}
	throw std::invalid_argument{"invaild value for conversion to dsc::format_specifier"};
}

/// Converts data read from the NMEA string to the corresponding
/// enumerator.
/// @note This function already takes care about the two lowest digit
///       representation of the values in the string.
///
/// @param[in] value The numerical value to convert.
/// @return The corresponding enumerator.
/// @exception std::invalid_argument The specified value to convert is unknown.
///
static dsc::category category_mapping(typename std::underlying_type<dsc::category>::type value)
{
	switch (value) {
		case 0:
			return dsc::category::routine;
		case 8:
			return dsc::category::safety;
		case 10:
			return dsc::category::urgency;
		case 12:
			return dsc::category::distress;
	}
	throw std::invalid_argument{"invaild value for conversion to dsc::category"};
}

/// Converts data read from the NMEA string to the corresponding
/// enumerator.
/// @note This function already takes care about the two lowest digit
///       representation of the values in the string.
///
/// @param[in] value The numerical value to convert.
/// @return The corresponding enumerator.
/// @exception std::invalid_argument The specified value to convert is unknown.
///
static dsc::acknowledgement acknowledgement_mapping(
	typename std::underlying_type<dsc::acknowledgement>::type value)
{
	switch (value) {
		case 'B':
			return dsc::acknowledgement::B;
		case 'R':
			return dsc::acknowledgement::R;
		case 'S':
			return dsc::acknowledgement::end_of_sequence;
	}
	throw std::invalid_argument{"invaild value for conversion to dsc::acknowledgement"};
}

/// Converts data read from the NMEA string to the corresponding
/// enumerator.
/// @note This function already takes care about the two lowest digit
///       representation of the values in the string.
///
/// @param[in] value The numerical value to convert.
/// @return The corresponding enumerator.
/// @exception std::invalid_argument The specified value to convert is unknown.
///
static dsc::extension_indicator extension_indicator_mapping(
	typename std::underlying_type<dsc::extension_indicator>::type value)
{
	switch (value) {
		case 0: // works beause 'value' is default initialized in the calling 'read' function
			return dsc::extension_indicator::none;
		case 'E':
			return dsc::extension_indicator::extension_follows;
	}
	throw std::invalid_argument{"invaild value for conversion to dsc::extension_indicator"};
}
}

std::string to_string(dsc::format_specifier value)
{
	switch (value) {
		case dsc::format_specifier::geographical_area:
			return "00";
		case dsc::format_specifier::distress:
			return "12";
		case dsc::format_specifier::all_ships:
			return "16";
		case dsc::format_specifier::individual_station:
			return "20";
	}
	throw std::invalid_argument{"invaild value for conversion of dsc::format_specifier"};
}

std::string to_string(dsc::category value)
{
	switch (value) {
		case dsc::category::routine:
			return "00";
		case dsc::category::safety:
			return "08";
		case dsc::category::urgency:
			return "10";
		case dsc::category::distress:
			return "12";
	}
	throw std::invalid_argument{"invaild value for conversion of dsc::category"};
}

std::string to_string(dsc::acknowledgement value)
{
	switch (value) {
		case dsc::acknowledgement::B:
			return "B";
		case dsc::acknowledgement::R:
			return "R";
		case dsc::acknowledgement::end_of_sequence:
			return "S";
	}
	throw std::invalid_argument{"invaild value for conversion of dsc::acknowledgement"};
}

std::string to_string(dsc::extension_indicator value)
{
	switch (value) {
		case dsc::extension_indicator::none:
			return "";
		case dsc::extension_indicator::extension_follows:
			return "E";
	}
	throw std::invalid_argument{"invaild value for conversion of dsc::extension_indicator"};
}

constexpr sentence_id dsc::ID;
constexpr const char * dsc::TAG;

dsc::dsc()
	: sentence(ID, TAG, talker_id::communications_dsc)
{
}

/// @todo Read and interpret more fields
dsc::dsc(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 11)
		throw std::invalid_argument{"invalid number of fields in dsc"};

	read(*(first + 0), fmt_spec_, format_specifier_mapping);
	read(*(first + 1), address_);
	read(*(first + 2), cat_, category_mapping);
	// @todo read other 6 data members
	read(*(first + 9), ack_, acknowledgement_mapping);
	read(*(first + 10), extension_, extension_indicator_mapping);
}

/// Valid only for format specifier other than geographical area.
/// However, there are no checks and special treatment, the MMSI is
/// simply wrong if taken with an invalid format specifier.
utils::mmsi dsc::get_mmsi() const
{
	return utils::mmsi{static_cast<utils::mmsi::value_type>(address_ / 10)};
}

/// Valid only for format specifier geographical_area.
/// However, there are no checks and special treatment, the data is
/// simply wrong if taken with an invalid format specifier.
///
/// Format:
/// @code
///  2
/// 1| 3  4 5
/// || |  | |
/// qxxyyyaabb
/// @endcode
///
/// Field Number:
/// 1. Quadrant 0..3
/// 2. Latitude in degrees, 2 digits
/// 3. Longitude in degrees, 3 digits
/// 4. Vertical side of the rectangle (north to south) in degrees, 2 digits
/// 5. Horizontal side of the rectangle (west to east) in degrees, 2 digits
///
geo::region dsc::get_geographical_area() const
{
	const auto quadrant = (address_ / 1000000000) % 10;

	geo::latitude::hemisphere lat_hem = geo::latitude::hemisphere::north;
	geo::longitude::hemisphere lon_hem = geo::longitude::hemisphere::west;
	switch (quadrant) {
		case 0: // NE quadrant
			lat_hem = geo::latitude::hemisphere::north;
			lon_hem = geo::longitude::hemisphere::east;
			break;
		case 1: // NW quadrant
			lat_hem = geo::latitude::hemisphere::north;
			lon_hem = geo::longitude::hemisphere::west;
			break;
		case 2: // SE quadrant
			lat_hem = geo::latitude::hemisphere::south;
			lon_hem = geo::longitude::hemisphere::east;
			break;
		case 3: // SW quadrant
			lat_hem = geo::latitude::hemisphere::south;
			lon_hem = geo::longitude::hemisphere::west;
			break;
		default:
			throw std::invalid_argument{"invalid quadrant"};
	}

	const uint32_t lat = static_cast<uint32_t>((address_ / 10000000) % 100);
	const uint32_t lon = static_cast<uint32_t>((address_ / 10000) % 1000);
	const double d_lat = static_cast<double>((address_ / 100) % 100);
	const double d_lon = static_cast<double>(address_ % 100);

	return geo::region{{{lat, 0, 0, lat_hem}, {lon, 0, 0, lon_hem}}, d_lat, d_lon};
}

/// @todo Implementation
///
void dsc::append_data_to(std::string & s) const
{
	append(s, to_string(fmt_spec_));
	append(s, format(address_, 10));
	append(s, to_string(cat_));
	append(s, "");
	append(s, "");
	append(s, "");
	append(s, "");
	append(s, "");
	append(s, "");
	append(s, to_string(ack_));
	append(s, to_string(extension_));
}
}
}
