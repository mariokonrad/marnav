#include "rpm.hpp"
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
///
/// @param[in] value The numerical value to convert.
/// @return The corresponding enumerator.
/// @exception std::invalid_argument The specified value to convert is unknown.
///
static rpm::source_id source_id_mapping(
	typename std::underlying_type<rpm::source_id>::type value) throw(std::invalid_argument)
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

std::string to_string(rpm::source_id value) throw(std::invalid_argument)
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

void rpm::set_source(source_id id, uint32_t num)
{
	source = id;
	source_number = num;
}

std::unique_ptr<sentence> rpm::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument, std::runtime_error)
{
	if (fields.size() != 5)
		throw std::invalid_argument{"invalid number of fields in rpm::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<rpm>();
	result->set_talker(talker);
	rpm & detail = static_cast<rpm &>(*result);

	read(fields[0], detail.source, source_id_mapping);
	read(fields[1], detail.source_number);
	read(fields[2], detail.revolutions);
	read(fields[3], detail.propeller_pitch);
	read(fields[4], detail.data_valid);

	return result;
}

std::vector<std::string> rpm::get_data() const
{
	return {to_string(source), to_string(source_number), format(revolutions, 1),
		format(propeller_pitch, 1), to_string(data_valid)};
}
}
}

