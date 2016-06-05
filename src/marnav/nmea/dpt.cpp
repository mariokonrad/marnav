#include "dpt.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(dpt)

constexpr const char * dpt::TAG;

dpt::dpt()
	: dpt(talker_id::integrated_instrumentation)
{
}

dpt::dpt(const std::string & talker)
	: sentence(ID, TAG, talker)
{
}

dpt::dpt(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	const auto size = std::distance(first, last);
	if ((size < 2) || (size > 3))
		throw std::invalid_argument{"invalid number of fields in dpt"};

	read(*(first + 0), depth_meter);
	read(*(first + 1), transducer_offset);

	if (size > 2)
		read(*(first + 2), max_depth);
}

std::vector<std::string> dpt::get_data() const
{
	return {to_string(depth_meter), to_string(transducer_offset), to_string(max_depth)};
}
}
}
