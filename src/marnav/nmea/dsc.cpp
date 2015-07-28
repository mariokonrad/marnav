#include "dsc.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * dsc::TAG;

dsc::dsc()
	: sentence(ID, TAG, talker_id::communications_dsc)
{
}

std::unique_ptr<sentence> dsc::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 11)
		throw std::invalid_argument{"invalid number of fields in dsc::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<dsc>();
	result->set_talker(talker);
	dsc & detail = static_cast<dsc &>(*result);

	// TODO: read fields

	return result;
}

std::vector<std::string> dsc::get_data() const
{
	return {}; // TODO: stringify fields
}
}
}
