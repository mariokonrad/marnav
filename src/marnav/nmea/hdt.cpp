#include <marnav/nmea/hdt.hpp>
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr sentence_id hdt::ID;
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

	read(*(first + 0), heading_);
	read(*(first + 1), heading_true_);
}

void hdt::set_heading(double t) noexcept
{
	heading_ = t;
	heading_true_ = reference::TRUE;
}

void hdt::append_data_to(std::string & s) const
{
	append(s, to_string(heading_));
	append(s, to_string(heading_true_));
}
}
}
