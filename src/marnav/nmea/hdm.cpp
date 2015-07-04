#include "hdm.hpp"
#include "io.hpp"
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * hdm::TAG;

hdm::hdm()
	: sentence(ID, TAG, talker_id::magnetic_compass)
{
}

void hdm::set_heading(double t)
{
	heading = t;
	heading_mag = reference::MAGNETIC;
}

std::unique_ptr<sentence> hdm::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 2)
		throw std::invalid_argument{"invalid number of fields in hdm::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<hdm>();
	result->set_talker(talker);
	hdm & detail = static_cast<hdm &>(*result);

	read(fields[0], detail.heading);
	read(fields[1], detail.heading_mag);

	return result;
}

std::vector<std::string> hdm::get_data() const
{
	return {to_string(heading), to_string(heading_mag)};
}
}
}
