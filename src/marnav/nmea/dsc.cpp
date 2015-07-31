#include "dsc.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

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
	typename std::underlying_type<dsc::format_specifier>::type
		value) throw(std::invalid_argument)
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
static dsc::category category_mapping(
	typename std::underlying_type<dsc::category>::type value) throw(std::invalid_argument)
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
}

constexpr const char * dsc::TAG;

dsc::dsc()
	: sentence(ID, TAG, talker_id::communications_dsc)
	, fmt_spec(format_specifier::distress)
	, address(0)
	, cat(category::distress)
{
}

/// Valid only for format specifier other than geographical area.
/// However, there are no checks and special treatment, the MMSI is
/// simply wrong if taken with an invalid format specifier.
utils::mmsi dsc::get_mmsi() const
{
	return utils::mmsi{static_cast<utils::mmsi::value_type>(address / 10)};
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
geo::region dsc::get_geographical_area() const throw(std::invalid_argument)
{
	uint32_t quadrant = (address / 1000000000) % 10;

	geo::latitude::hemisphere lat_hem = geo::latitude::hemisphere::NORTH;
	geo::longitude::hemisphere lon_hem = geo::longitude::hemisphere::WEST;
	switch (quadrant) {
		case 0: // NE quadrant
			lat_hem = geo::latitude::hemisphere::NORTH;
			lon_hem = geo::longitude::hemisphere::EAST;
			break;
		case 1: // NW quadrant
			lat_hem = geo::latitude::hemisphere::NORTH;
			lon_hem = geo::longitude::hemisphere::WEST;
			break;
		case 2: // SE quadrant
			lat_hem = geo::latitude::hemisphere::SOUTH;
			lon_hem = geo::longitude::hemisphere::EAST;
			break;
		case 3: // SW quadrant
			lat_hem = geo::latitude::hemisphere::SOUTH;
			lon_hem = geo::longitude::hemisphere::WEST;
			break;
		default:
			throw std::invalid_argument{"invalid quadrant"};
	}

	uint32_t lat = (address / 10000000) % 100;
	uint32_t lon = (address / 10000) % 1000;
	uint32_t d_lat = (address / 100) % 100;
	uint32_t d_lon = address % 100;

	return geo::region{{{lat, 0, 0, lat_hem}, {lon, 0, 0, lon_hem}}, static_cast<double>(d_lat),
		static_cast<double>(d_lon)};
}

/// @todo Read and interpret more fields
///
std::unique_ptr<sentence> dsc::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 11)
		throw std::invalid_argument{"invalid number of fields in dsc::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<dsc>();
	result->set_talker(talker);
	dsc & detail = static_cast<dsc &>(*result);

	read(fields[0], detail.fmt_spec, format_specifier_mapping);
	read(fields[1], detail.address);
	read(fields[2], detail.cat, category_mapping);

	return result;
}

/// @todo Implementation
///
std::vector<std::string> dsc::get_data() const
{
	return {};
}
}
}
