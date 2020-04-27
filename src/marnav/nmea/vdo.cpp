#include <marnav/nmea/vdo.hpp>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
constexpr sentence_id vdo::ID;
constexpr const char * vdo::TAG;

vdo::vdo()
	: vdm(ID, TAG, talker::ais_mobile_station)
{
}

vdo::vdo(talker talk, fields::const_iterator first, fields::const_iterator last)
	: vdm(ID, TAG, talk)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in vdo"};

	read_fields(first);
}
}
}
