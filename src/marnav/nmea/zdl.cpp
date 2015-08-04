#include "zdl.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * zdl::TAG;

zdl::zdl()
	: sentence(ID, TAG, talker_id::global_positioning_system)
	, distance(0.0)
	, type_point(type_of_point::reference)
{
}

std::unique_ptr<sentence> zdl::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 3)
		throw std::invalid_argument{"invalid number of fields in zdl::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<zdl>();
	result->set_talker(talker);
	zdl & detail = static_cast<zdl &>(*result);

	read(fields[0], detail.time_to_point);
	read(fields[1], detail.distance);
	read(fields[2], detail.type_point);

	return result;
}

std::vector<std::string> zdl::get_data() const
{
	return {to_string(time_to_point), format(distance, 1), to_string(type_point)};
}
}
}
