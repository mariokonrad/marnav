#include "dsc.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * dsc::TAG;

dsc::dsc()
	: sentence(ID, TAG, talker_id::communications_dsc)
{
}

dsc::format_specifier dsc::format_specifier_maping(
	typename std::underlying_type<format_specifier>::type value)
{
	using U = std::underlying_type<format_specifier>::type;
	switch (value) {
		case static_cast<U>(format_specifier::geographical_area):
			return format_specifier::geographical_area;
		case static_cast<U>(format_specifier::distress):
			return format_specifier::distress;
		case static_cast<U>(format_specifier::all_ships):
			return format_specifier::all_ships;
		case static_cast<U>(format_specifier::individual_station):
			return format_specifier::individual_station;
	}

	return static_cast<format_specifier>(-1); // invalid value on purpose
}

std::unique_ptr<sentence> dsc::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 11)
		throw std::invalid_argument{"invalid number of fields in dsc::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<dsc>();
	result->set_talker(talker);
	dsc & detail = static_cast<dsc &>(*result);

	read(fields[0], detail.fmt_spec, format_specifier_maping);
	// TODO: read fields

	return result;
}

std::vector<std::string> dsc::get_data() const
{
	return {}; // TODO: stringify fields
}
}
}
