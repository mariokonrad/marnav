#include "rpm.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{

namespace
{
/// Converts data read from the NMEA string to the corresponding
/// enumerator.
///
/// @param[in] value The numerical value to convert.
/// @return The corresponding enumerator.
/// @exception std::invalid_argument The specified value to convert is unknown.
///
static rpm::source_id source_id_mapping(
	typename std::underlying_type<rpm::source_id>::type value)
{
	switch (value) {
		case 'S':
			return rpm::source_id::shaft;
		case 'E':
			return rpm::source_id::engine;
	}
	throw std::invalid_argument{"invaild value for conversion to rpm::source_id"};
}
}

std::string to_string(rpm::source_id value)
{
	switch (value) {
		case rpm::source_id::shaft:
			return "S";
		case rpm::source_id::engine:
			return "E";
	}
	throw std::invalid_argument{"invaild value for conversion of rpm::source_id"};
}

constexpr const char * rpm::TAG;

rpm::rpm()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
}

rpm::rpm(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	if (std::distance(first, last) != 5)
		throw std::invalid_argument{"invalid number of fields in rpm"};

	read(*(first + 0), source, source_id_mapping);
	read(*(first + 1), source_number);
	read(*(first + 2), revolutions);
	read(*(first + 3), propeller_pitch);
	read(*(first + 4), data_valid);
}

void rpm::set_source(source_id id, uint32_t num)
{
	source = id;
	source_number = num;
}

std::unique_ptr<sentence> rpm::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	return std::unique_ptr<rpm>(new rpm(talker, first, last));
}

std::vector<std::string> rpm::get_data() const
{
	return {to_string(source), to_string(source_number), format(revolutions, 1),
		format(propeller_pitch, 1), to_string(data_valid)};
}
}
}
