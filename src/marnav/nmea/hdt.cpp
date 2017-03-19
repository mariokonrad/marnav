#include "hdt.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * hdt::TAG;

hdt::hdt()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
}

hdt::hdt(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 2)
		throw std::invalid_argument{"invalid number of fields in hdt"};

	read(*(first + 0), heading);
	read(*(first + 1), heading_true);
}

void hdt::set_heading(double t) noexcept
{
	heading = t;
	heading_true = reference::TRUE;
}

void hdt::append_data_to(std::string & s) const
{
	append(s, to_string(heading));
	append(s, to_string(heading_true));
}
}
}
