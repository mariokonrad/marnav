#include "dtm.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * dtm::TAG;

dtm::dtm()
	: sentence(ID, TAG, talker_id::global_positioning_system)
	, ref("W84")
	, lat_offset(0)
	, lat_hem(direction::north)
	, lon_offset(0)
	, lon_hem(direction::east)
	, altitude(0)
	, name("W84")
{
}

void dtm::set_lat_offset(double t, direction h)
{
	check_value(h, {direction::north, direction::south});
	lat_offset = t;
	lat_hem = h;
}

void dtm::set_lon_offset(double t, direction h)
{
	check_value(h, {direction::east, direction::west});
	lon_offset = t;
	lon_hem = h;
}

void dtm::set_ref(const std::string & t) noexcept
{
	if (t.size() > 5) {
		ref = t.substr(0, 5);
	} else {
		ref = t;
	}
}

void dtm::set_subcode(const std::string & t) noexcept
{
	if (t.size() > 5) {
		subcode = t.substr(0, 5);
	} else {
		subcode = t;
	}
}

void dtm::set_name(const std::string & t) noexcept
{
	if (t.size() > 5) {
		name = t.substr(0, 5);
	} else {
		name = t;
	}
}

std::unique_ptr<sentence> dtm::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 8)
		throw std::invalid_argument{"invalid number of fields in dtm::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<dtm>();
	result->set_talker(talker);
	dtm & detail = static_cast<dtm &>(*result);

	read(*(first + 0), detail.ref);
	read(*(first + 1), detail.subcode);
	read(*(first + 2), detail.lat_offset);
	read(*(first + 3), detail.lat_hem);
	read(*(first + 4), detail.lon_offset);
	read(*(first + 5), detail.lon_hem);
	read(*(first + 6), detail.altitude);
	read(*(first + 7), detail.name);

	return result;
}

std::vector<std::string> dtm::get_data() const
{
	return {to_string(ref), to_string(subcode), format(lat_offset, 4), to_string(lat_hem),
		format(lon_offset, 4), to_string(lon_hem), format(altitude, 1), to_string(name)};
}
}
}
