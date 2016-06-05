#include "vdo.hpp"

namespace marnav
{
namespace nmea
{

constexpr const char * vdo::TAG;

vdo::vdo()
	: vdm(ID, TAG, talker_id::ais_mobile_station)
{
}

vdo::vdo(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: vdm(ID, TAG, talker)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in vdo"};

	read_fields(first);
}

std::unique_ptr<sentence> vdo::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	return std::unique_ptr<vdo>(new vdo(talker, first, last));
}
}
}
