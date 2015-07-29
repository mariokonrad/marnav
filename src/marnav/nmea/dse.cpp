#include "dse.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * dse::TAG;

dse::dse()
	: sentence(ID, TAG, talker_id::communications_dsc)
{
}

std::unique_ptr<sentence> dse::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 6)
		throw std::invalid_argument{"invalid number of fields in dse::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<dse>();
	result->set_talker(talker);
	dse & detail = static_cast<dse &>(*result);

	// TODO: read fields

	return result;
}

std::vector<std::string> dse::get_data() const
{
	return {}; // TODO: stringify fields
}
}
}
