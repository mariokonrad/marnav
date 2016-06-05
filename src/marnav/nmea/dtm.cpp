#include "dtm.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * dtm::TAG;

dtm::dtm()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

dtm::dtm(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	if (std::distance(first, last) != 8)
		throw std::invalid_argument{"invalid number of fields in dtm"};

	read(*(first + 0), ref);
	read(*(first + 1), subcode);
	read(*(first + 2), lat_offset);
	read(*(first + 3), lat_hem);
	read(*(first + 4), lon_offset);
	read(*(first + 5), lon_hem);
	read(*(first + 6), altitude);
	read(*(first + 7), name);
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
	return std::unique_ptr<dtm>(new dtm(talker, first, last));
}

std::vector<std::string> dtm::get_data() const
{
	return {to_string(ref), to_string(subcode), format(lat_offset, 4), to_string(lat_hem),
		format(lon_offset, 4), to_string(lon_hem), format(altitude, 1), to_string(name)};
}
}
}
