#include <marnav/nmea/dpt.hpp>
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr sentence_id dpt::ID;
constexpr const char * dpt::TAG;

dpt::dpt()
	: dpt(talker_id::integrated_instrumentation)
{
}

dpt::dpt(talker talk)
	: sentence(ID, TAG, talk)
{
}

dpt::dpt(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	const auto size = std::distance(first, last);
	if ((size < 2) || (size > 3))
		throw std::invalid_argument{"invalid number of fields in dpt"};

	read(*(first + 0), depth_meter_);
	read(*(first + 1), transducer_offset_);

	if (size > 2)
		read(*(first + 2), max_depth_);
}

void dpt::append_data_to(std::string & s) const
{
	append(s, to_string(depth_meter_));
	append(s, to_string(transducer_offset_));
	append(s, to_string(max_depth_));
}
}
}
