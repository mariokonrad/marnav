#include <marnav/nmea/xtr.hpp>
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
constexpr sentence_id xtr::ID;
constexpr const char * xtr::TAG;

xtr::xtr()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

xtr::xtr(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 3)
		throw std::invalid_argument{"invalid number of fields in xtr"};

	read(*(first + 0), cross_track_error_magnitude_);
	read(*(first + 1), direction_to_steer_);
	read(*(first + 2), cross_track_unit_);
}

void xtr::append_data_to(std::string & s, const version &) const
{
	append(s, to_string(cross_track_error_magnitude_));
	append(s, to_string(direction_to_steer_));
	append(s, to_string(cross_track_unit_));
}
}
}
