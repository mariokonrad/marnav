#include <marnav/nmea/tpr.hpp>
#include <marnav/nmea/io.hpp>
#include "checks.hpp"

namespace marnav
{
namespace nmea
{
constexpr sentence_id tpr::ID;
constexpr const char * tpr::TAG;

tpr::tpr()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

tpr::tpr(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in tpr"};

	unit::distance range_unit;
	unit::distance depth_unit;

	read(*(first + 0), range_);
	read(*(first + 1), range_unit);
	read(*(first + 2), bearing_);
	// separator omitted intentionally
	read(*(first + 4), depth_);
	read(*(first + 5), depth_unit);

	check_value(range_unit, {unit::distance::meter}, "range_unit");
	check_value(depth_unit, {unit::distance::meter}, "depth_unit");
}

void tpr::append_data_to(std::string & s) const
{
	append(s, to_string(range_));
	append(s, to_string(unit::distance::meter));
	append(s, to_string(bearing_));
	append(s, 'P');
	append(s, to_string(depth_));
	append(s, to_string(unit::distance::meter));
}
}
}
