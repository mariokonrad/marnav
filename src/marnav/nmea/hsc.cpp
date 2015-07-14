#include "hsc.hpp"
#include "io.hpp"
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * hsc::TAG;

hsc::hsc()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

void hsc::set_heading_true(double t)
{
	heading_true = t;
	heading_true_ref = reference::TRUE;
}

void hsc::set_heading_mag(double t)
{
	heading_mag = t;
	heading_mag_ref = reference::MAGNETIC;
}

std::unique_ptr<sentence> hsc::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 4)
		throw std::invalid_argument{"invalid number of fields in hsc::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<hsc>();
	result->set_talker(talker);
	hsc & detail = static_cast<hsc &>(*result);

	read(fields[0], detail.heading_true);
	read(fields[1], detail.heading_true_ref);
	read(fields[2], detail.heading_mag);
	read(fields[3], detail.heading_mag_ref);

	return result;
}

std::vector<std::string> hsc::get_data() const
{
	return {to_string(heading_true), to_string(heading_true_ref), to_string(heading_mag),
		to_string(heading_mag_ref)};
}
}
}
