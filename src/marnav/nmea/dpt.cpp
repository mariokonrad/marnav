#include "dpt.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * dpt::TAG;

dpt::dpt()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
}

std::unique_ptr<sentence> dpt::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 2)
		throw std::invalid_argument{"invalid number of fields in dpt::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<dpt>();
	result->set_talker(talker);
	dpt & detail = static_cast<dpt &>(*result);

	read(fields[0], detail.depth_meter);
	read(fields[1], detail.transducer_offset);

	return result;
}

std::vector<std::string> dpt::get_data() const
{
	return {to_string(depth_meter), to_string(transducer_offset)};
}
}
}
