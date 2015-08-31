#include "dpt.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * dpt::TAG;

dpt::dpt()
	: dpt(talker_id::integrated_instrumentation)
{
}

dpt::dpt(const std::string & talker)
	: sentence(ID, TAG, talker)
	, depth_meter(0.0)
	, transducer_offset(0.0)
{
}

std::unique_ptr<sentence> dpt::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument, std::runtime_error)
{
	if ((fields.size() < 2) || (fields.size() > 3))
		throw std::invalid_argument{"invalid number of fields in dpt::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<dpt>(talker);
	dpt & detail = static_cast<dpt &>(*result);

	read(fields[0], detail.depth_meter);
	read(fields[1], detail.transducer_offset);

	if (fields.size() > 2)
		read(fields[2], detail.max_depth);

	return result;
}

std::vector<std::string> dpt::get_data() const
{
	return {to_string(depth_meter), to_string(transducer_offset), to_string(max_depth)};
}
}
}
