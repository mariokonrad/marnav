#include "gsa.hpp"
#include <limits>
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr sentence_id gsa::ID;
constexpr const char * gsa::TAG;

constexpr int gsa::max_satellite_ids;

gsa::gsa()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

gsa::gsa(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 17)
		throw std::invalid_argument{"invalid number of fields in gsa"};

	read(*(first + 0), sel_mode_);
	read(*(first + 1), mode_);

	constexpr uint32_t init_val = std::numeric_limits<uint32_t>::max();

	int index = 2;
	for (auto i = 0; i < max_satellite_ids; ++i, ++index) {
		uint32_t id = init_val;
		read(*(first + index), id);
		if (id != init_val)
			set_satellite_id(i, id);
	}
	read(*(first + 14), pdop_);
	read(*(first + 15), hdop_);
	read(*(first + 16), vdop_);
}

void gsa::check_index(int index) const
{
	if ((index < 0) || (index >= max_satellite_ids)) {
		throw std::out_of_range{"satellite id out of range"};
	}
}

void gsa::set_satellite_id(int index, uint32_t t)
{
	check_index(index);
	satellite_id_[index] = t;
}

utils::optional<uint32_t> gsa::get_satellite_id(int index) const
{
	check_index(index);
	return satellite_id_[index];
}

void gsa::append_data_to(std::string & s) const
{
	append(s, to_string(sel_mode_));
	append(s, to_string(mode_));
	append(s, format(satellite_id_[0], 2));
	append(s, format(satellite_id_[1], 2));
	append(s, format(satellite_id_[2], 2));
	append(s, format(satellite_id_[3], 2));
	append(s, format(satellite_id_[4], 2));
	append(s, format(satellite_id_[5], 2));
	append(s, format(satellite_id_[6], 2));
	append(s, format(satellite_id_[7], 2));
	append(s, format(satellite_id_[8], 2));
	append(s, format(satellite_id_[9], 2));
	append(s, format(satellite_id_[10], 2));
	append(s, format(satellite_id_[11], 2));
	append(s, to_string(pdop_));
	append(s, to_string(hdop_));
	append(s, to_string(vdop_));
}
}
}
