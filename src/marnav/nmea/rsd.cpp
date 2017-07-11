#include "rsd.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * rsd::TAG;

rsd::rsd()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
	, unknowns_({{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}})
{
}

rsd::rsd(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 13)
		throw std::invalid_argument{"invalid number of fields in rsd"};

	for (decltype(unknowns_.size()) i = 0; i < unknowns_.size(); ++i)
		read(*(first + i), unknowns_[i]);
	read(*(first + 8), cursor_range_);
	read(*(first + 9), cursor_bearing_);
	read(*(first + 10), range_scale_);
	read(*(first + 11), range_unit_);
	read(*(first + 12), unknown_);
}

void rsd::set_cursor(double range, double bearing) noexcept
{
	cursor_range_ = range;
	cursor_bearing_ = bearing;
}

void rsd::set_range(double scale, char unit) noexcept
{
	range_scale_ = scale;
	range_unit_ = unit;
}

void rsd::append_data_to(std::string & s) const
{
	for (auto const & t : unknowns_)
		append(s, to_string(t));
	append(s, to_string(cursor_range_));
	append(s, to_string(cursor_bearing_));
	append(s, to_string(range_scale_));
	append(s, to_string(range_unit_));
	append(s, to_string(unknown_));
}
}
}
