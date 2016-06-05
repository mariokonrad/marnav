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

mtw::mtw(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
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

std::unique_ptr<sentence> mtw::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	return std::unique_ptr<mtw>(new mtw(talker, first, last));
}

std::vector<std::string> mtw::get_data() const
{
	return {to_string(temperature), to_string(temperature_unit)};
}
}
}
