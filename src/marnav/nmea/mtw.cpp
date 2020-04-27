#include <marnav/nmea/mtw.hpp>
#include <marnav/nmea/io.hpp>
#include "checks.hpp"

namespace marnav
{
namespace nmea
{
constexpr sentence_id mtw::ID;
constexpr const char * mtw::TAG;

mtw::mtw()
	: sentence(ID, TAG, talker::integrated_instrumentation)
{
}

mtw::mtw(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 2)
		throw std::invalid_argument{"invalid number of fields in mtw"};

	unit::temperature temperature_unit;

	read(*(first + 0), temperature_);
	read(*(first + 1), temperature_unit);

	check_value(temperature_unit, {unit::temperature::celsius}, "temperature unit");
}

void mtw::set_temperature(units::temperature t) noexcept
{
	temperature_ = t.get<units::celsius>();
}

void mtw::append_data_to(std::string & s) const
{
	append(s, to_string(temperature_));
	append(s, to_string(unit::temperature::celsius));
}
}
}
