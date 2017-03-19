#include "vlw.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * vlw::TAG;

vlw::vlw()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
}

vlw::vlw(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 4)
		throw std::invalid_argument{"invalid number of fields in vlw"};

	read(*(first + 0), distance_cum);
	read(*(first + 1), distance_cum_unit);
	read(*(first + 2), distance_reset);
	read(*(first + 3), distance_reset_unit);
}

void vlw::set_distance_cum_nm(double t) noexcept
{
	distance_cum = t;
	distance_cum_unit = unit::distance::nm;
}

void vlw::set_distance_reset_nm(double t) noexcept
{
	distance_reset = t;
	distance_reset_unit = unit::distance::nm;
}

void vlw::append_data_to(std::string & s) const
{
	append(s, to_string(distance_cum));
	append(s, to_string(distance_cum_unit));
	append(s, to_string(distance_reset));
	append(s, to_string(distance_reset_unit));
}
}
}
