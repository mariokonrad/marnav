#include <marnav/nmea/zdl.hpp>
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
constexpr sentence_id zdl::ID;
constexpr const char * zdl::TAG;

zdl::zdl()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

zdl::zdl(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 3)
		throw std::invalid_argument{"invalid number of fields in zdl"};

	read(*(first + 0), time_to_point_);
	read(*(first + 1), distance_);
	read(*(first + 2), type_point_);
}

void zdl::append_data_to(std::string & s, const version &) const
{
	append(s, to_string(time_to_point_));
	append(s, format(distance_, 1));
	append(s, to_string(type_point_));
}
}
}
