#include <marnav/nmea/dtm.hpp>
#include "checks.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav::nmea
{
constexpr sentence_id dtm::ID;
constexpr const char * dtm::TAG;

dtm::dtm()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

dtm::dtm(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 8)
		throw std::invalid_argument{"invalid number of fields in dtm"};

	read(*(first + 0), ref_);
	read(*(first + 1), subcode_);
	read(*(first + 2), lat_offset_);
	read(*(first + 3), lat_hem_);
	read(*(first + 4), lon_offset_);
	read(*(first + 5), lon_hem_);
	read(*(first + 6), altitude_);
	read(*(first + 7), name_);
}

void dtm::set_lat_offset(double t, direction h)
{
	check_value(h, {direction::north, direction::south});
	lat_offset_ = t;
	lat_hem_ = h;
}

void dtm::set_lon_offset(double t, direction h)
{
	check_value(h, {direction::east, direction::west});
	lon_offset_ = t;
	lon_hem_ = h;
}

void dtm::set_ref(const std::string & t) noexcept
{
	if (t.size() > 5) {
		ref_ = t.substr(0, 5);
	} else {
		ref_ = t;
	}
}

void dtm::set_subcode(const std::string & t) noexcept
{
	if (t.size() > 5) {
		subcode_ = t.substr(0, 5);
	} else {
		subcode_ = t;
	}
}

void dtm::set_name(const std::string & t) noexcept
{
	if (t.size() > 5) {
		name_ = t.substr(0, 5);
	} else {
		name_ = t;
	}
}

void dtm::append_data_to(std::string & s, const version &) const
{
	append(s, to_string(ref_));
	append(s, to_string(subcode_));
	append(s, format(lat_offset_, 4));
	append(s, to_string(lat_hem_));
	append(s, format(lon_offset_, 4));
	append(s, to_string(lon_hem_));
	append(s, format(altitude_, 1));
	append(s, to_string(name_));
}
}
