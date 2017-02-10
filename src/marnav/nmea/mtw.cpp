#include "mtw.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * mtw::TAG;

mtw::mtw()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
}

mtw::mtw(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 2)
		throw std::invalid_argument{"invalid number of fields in mtw"};

	read(*(first + 0), temperature);
	read(*(first + 1), temperature_unit);
}

void mtw::set_temperature(double t) noexcept
{
	temperature = t;
	temperature_unit = unit::temperature::celsius;
}

std::vector<std::string> mtw::get_data() const
{
	return {to_string(temperature), to_string(temperature_unit)};
}
}
}
