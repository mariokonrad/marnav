#include "vdo.hpp"
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * vdo::TAG;

vdo::vdo()
	: vdm(ID, TAG, talker_id::ais_mobile_station)
{
}

std::unique_ptr<sentence> vdo::parse(
	const std::string & talker, const std::vector<std::string> & fields)
{
	if (fields.size() != 6)
		throw std::invalid_argument{"invalid number of fields in vdo::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<vdo>();
	result->set_talker(talker);
	vdo & detail = static_cast<vdo &>(*result);

	detail.read_fields(fields);

	return result;
}
}
}
