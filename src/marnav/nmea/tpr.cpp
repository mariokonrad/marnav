#include "tpr.hpp"
#include <marnav/nmea/io.hpp>

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

	read(*(first + 0), range_);
	read(*(first + 1), range_unit_);
	read(*(first + 2), bearing_);
	// separator omitted intentionally
	read(*(first + 4), depth_);
	read(*(first + 5), depth_unit_);
}

void tpr::append_data_to(std::string & s) const
{
	append(s, to_string(range_));
	append(s, to_string(range_unit_));
	append(s, to_string(bearing_));
	append(s, 'P');
	append(s, to_string(depth_));
	append(s, to_string(depth_unit_));
}
}
}
