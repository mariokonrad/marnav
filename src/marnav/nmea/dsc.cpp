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
/// simply wrong.
utils::mmsi dsc::get_mmsi() const
{
	return utils::mmsi{static_cast<uint32_t>(address / 10)};
}

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
	// TODO: read fields

	return result;
}

std::vector<std::string> dsc::get_data() const
{
	return {}; // TODO: stringify fields
}
}
}
