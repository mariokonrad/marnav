#include "rot.hpp"
#include "io.hpp"
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * rot::TAG;

rot::rot()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

std::unique_ptr<sentence> rot::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 2)
		throw std::invalid_argument{"invalid number of fields in rot::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<rot>();
	result->set_talker(talker);
	rot & detail = static_cast<rot &>(*result);

	read(fields[0], detail.deg_per_minute);
	read(fields[1], detail.data_valid);

	return result;
}

std::vector<std::string> rot::get_data() const
{
	return {format(deg_per_minute, 1), to_string(data_valid)};
}
}
}

