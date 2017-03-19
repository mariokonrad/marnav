#include "rsd.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * rsd::TAG;

rsd::rsd()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
	, unknowns({{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}})
{
}

rsd::rsd(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 13)
		throw std::invalid_argument{"invalid number of fields in rsd"};

	for (decltype(unknowns.size()) i = 0; i < unknowns.size(); ++i)
		read(*(first + i), unknowns[i]);
	read(*(first + 8), cursor_range);
	read(*(first + 9), cursor_bearing);
	read(*(first + 10), range_scale);
	read(*(first + 11), range_unit);
	read(*(first + 12), unknown);
}

void rsd::set_cursor(double range, double bearing) noexcept
{
	cursor_range = range;
	cursor_bearing = bearing;
}

void rsd::set_range(double scale, char unit) noexcept
{
	range_scale = scale;
	range_unit = unit;
}

void rsd::append_data_to(std::string & s) const
{
	for (auto const & t : unknowns)
		append(s, to_string(t));
	append(s, to_string(cursor_range));
	append(s, to_string(cursor_bearing));
	append(s, to_string(range_scale));
	append(s, to_string(range_unit));
	append(s, to_string(unknown));
}
}
}
