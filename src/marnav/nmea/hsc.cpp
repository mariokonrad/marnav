#include "hsc.hpp"
#include <marnav/nmea/io.hpp>
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

void hsc::set_heading_true(double t) noexcept
{
	heading_true = t;
	heading_true_ref = reference::TRUE;
}

void hsc::set_heading_mag(double t) noexcept
{
	heading_mag = t;
	heading_mag_ref = reference::MAGNETIC;
}

std::unique_ptr<sentence> hsc::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 4)
		throw std::invalid_argument{"invalid number of fields in hsc::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<hsc>();
	result->set_talker(talker);
	hsc & detail = static_cast<hsc &>(*result);

	read(*(first + 0), detail.heading_true);
	read(*(first + 1), detail.heading_true_ref);
	read(*(first + 2), detail.heading_mag);
	read(*(first + 3), detail.heading_mag_ref);

	return result;
}

std::vector<std::string> hsc::get_data() const
{
	return {to_string(heading_true), to_string(heading_true_ref), to_string(heading_mag),
		to_string(heading_mag_ref)};
}
}
}
