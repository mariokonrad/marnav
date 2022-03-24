#include <marnav/nmea/vwe.hpp>
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
constexpr sentence_id vwe::ID;
constexpr const char * vwe::TAG;

vwe::vwe()
	: sentence(ID, TAG, talker::integrated_instrumentation)
{
}

vwe::vwe(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 1)
		throw std::invalid_argument{"invalid number of fields in vwe"};

	read(*(first + 0), efficiency_);
}

void vwe::set_efficiency(double t)
{
	if (t < 0.0)
		throw std::invalid_argument{"negative efficiency"};
	if (t > 100.0)
		throw std::invalid_argument{"perpetuum mobile"};
	efficiency_ = t;
}

void vwe::append_data_to(std::string & s, const version &) const
{
	append(s, format(efficiency_, 1));
}
}
}
