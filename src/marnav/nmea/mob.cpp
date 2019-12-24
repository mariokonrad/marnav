#include <marnav/nmea/mob.hpp>
#include <marnav/nmea/io.hpp>
#include "convert.hpp"
#include <algorithm>

namespace marnav
{
namespace nmea
{
namespace
{
static mob::mob_status mob_status_mapping(
	typename std::underlying_type<mob::mob_status>::type value)
{
	switch (value) {
		case 'A':
			return mob::mob_status::mob_activated;
		case 'T':
			return mob::mob_status::test_mode;
		case 'M':
			return mob::mob_status::manual_button;
		case 'V':
			return mob::mob_status::mob_not_in_use;
		case 'E':
			return mob::mob_status::error;
	}
	throw std::invalid_argument{"invaild value for conversion to mob::mob_status"};
}

static mob::mob_position_source mob_position_source_mapping(
	typename std::underlying_type<mob::mob_position_source>::type value)
{
	switch (value) {
		case 0:
			return mob::mob_position_source::position_estimated;
		case 1:
			return mob::mob_position_source::position_reported;
		case 2:
		case 3:
		case 4:
		case 5:
			return mob::mob_position_source::reserved;
		case 6:
			return mob::mob_position_source::error;
	}
	throw std::invalid_argument{"invaild value for conversion to mob::mob_position_source"};
}

static mob::battery_status battery_status_mapping(
	typename std::underlying_type<mob::battery_status>::type value)
{
	switch (value) {
		case 0:
			return mob::battery_status::good;
		case 1:
			return mob::battery_status::low;
		case 2:
		case 3:
		case 4:
		case 5:
			return mob::battery_status::reserved;
		case 6:
			return mob::battery_status::error;
	}
	throw std::invalid_argument{"invaild value for conversion to mob::battery_status"};
}
}

std::string to_string(mob::mob_status value)
{
	switch (value) {
		case mob::mob_status::mob_activated:
			return "A";
		case mob::mob_status::test_mode:
			return "T";
		case mob::mob_status::manual_button:
			return "M";
		case mob::mob_status::mob_not_in_use:
			return "V";
		case mob::mob_status::error:
			return "E";
	}
	throw std::invalid_argument{"invaild value for conversion of mob::mob_status"};
}

std::string to_string(mob::mob_position_source value)
{
	switch (value) {
		case mob::mob_position_source::position_estimated:
			return "0";
		case mob::mob_position_source::position_reported:
			return "1";
		case mob::mob_position_source::reserved:
			return "2";
		case mob::mob_position_source::error:
			return "6";
	}
	throw std::invalid_argument{"invaild value for conversion of mob::mob_position_source"};
}

std::string to_string(mob::battery_status value)
{
	switch (value) {
		case mob::battery_status::good:
			return "0";
		case mob::battery_status::low:
			return "1";
		case mob::battery_status::reserved:
			return "2";
		case mob::battery_status::error:
			return "6";
	}
	throw std::invalid_argument{"invaild value for conversion of mob::battery_status"};
}

constexpr sentence_id mob::ID;
constexpr const char * mob::TAG;

mob::mob()
	: sentence(ID, TAG, talker_id::integrated_navigation)
{
}

mob::mob(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 14)
		throw std::invalid_argument{"invalid number of fields in mob"};

	read(*(first + 0), emitter_id_);
	read(*(first + 1), mob_status_, mob_status_mapping);
	read(*(first + 2), mob_activation_utc_);
	read(*(first + 3), mob_position_source_, mob_position_source_mapping);
	read(*(first + 4), position_date_);
	read(*(first + 5), position_utc_);
	read(*(first + 6), lat_);
	read(*(first + 7), lat_hem_);
	read(*(first + 8), lon_);
	read(*(first + 9), lon_hem_);
	read(*(first + 10), cog_);
	read(*(first + 11), sog_);
	read(*(first + 12), mmsi_);
	read(*(first + 13), battery_status_, battery_status_mapping);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	lat_ = correct_hemisphere(lat_, lat_hem_);
	lon_ = correct_hemisphere(lon_, lon_hem_);
}

void mob::append_data_to(std::string & s) const
{
	append(s, to_string(emitter_id_));
	append(s, to_string(mob_status_));
	append(s, to_string(mob_activation_utc_));
	append(s, to_string(mob_position_source_));
	append(s, to_string(position_date_));
	append(s, to_string(position_utc_));
	append(s, to_string(lat_));
	append(s, to_string(lat_hem_));
	append(s, to_string(lon_));
	append(s, to_string(lon_hem_));
	append(s, to_string(cog_));
	append(s, to_string(sog_));
	append(s, format(mmsi_, 9));
	append(s, to_string(battery_status_));
}

geo::latitude mob::get_lat() const
{
	return lat_;
}

geo::longitude mob::get_lon() const
{
	return lon_;
}

utils::mmsi mob::get_mmsi() const
{
	return utils::mmsi{static_cast<utils::mmsi::value_type>(mmsi_)};
}

void mob::set_emitter_id(const std::string & t)
{
	if (t.empty()) {
		emitter_id_.reset();
		return;
	}

	if (t.size() > emitter_id_max)
		throw std::invalid_argument("emitter id max 5 digits");
	if (t.find_first_not_of("0123456789abcdefABCDEF") != std::string::npos)
		throw std::invalid_argument("emitter id only hex digits allowed");

	emitter_id_ = std::string(emitter_id_max, '0');
	std::transform(begin(t), end(t), next(begin(*emitter_id_), emitter_id_max - t.size()),
		[](std::string::value_type c) -> std::string::value_type { return std::toupper(c); });
}

void mob::set_lat(const geo::latitude & t)
{
	lat_ = t;
	lat_hem_ = convert_hemisphere(t);
}

void mob::set_lon(const geo::longitude & t)
{
	lon_ = t;
	lon_hem_ = convert_hemisphere(t);
}

void mob::set_mmsi(const utils::mmsi & t)
{
	mmsi_ = t;
}
}
}
