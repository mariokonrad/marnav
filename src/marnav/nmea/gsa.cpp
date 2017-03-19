#include "gsa.hpp"
#include <limits>
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * gsa::TAG;

gsa::gsa()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

gsa::gsa(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 17)
		throw std::invalid_argument{"invalid number of fields in gsa"};

	read(*(first + 0), sel_mode);
	read(*(first + 1), mode);

	constexpr uint32_t init_val = std::numeric_limits<uint32_t>::max();

	int index = 2;
	for (auto i = 0; i < max_satellite_ids; ++i, ++index) {
		uint32_t id = init_val;
		read(*(first + index), id);
		if (id != init_val)
			set_satellite_id(i, id);
	}
	read(*(first + 14), pdop);
	read(*(first + 15), hdop);
	read(*(first + 16), vdop);
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
	satellite_id[index] = t;
}

utils::optional<uint32_t> gsa::get_satellite_id(int index) const
{
	check_index(index);
	return satellite_id[index];
}

void gsa::append_data_to(std::string & s) const
{
	append(s, to_string(sel_mode));
	append(s, to_string(mode));
	append(s, format(satellite_id[0], 2));
	append(s, format(satellite_id[1], 2));
	append(s, format(satellite_id[2], 2));
	append(s, format(satellite_id[3], 2));
	append(s, format(satellite_id[4], 2));
	append(s, format(satellite_id[5], 2));
	append(s, format(satellite_id[6], 2));
	append(s, format(satellite_id[7], 2));
	append(s, format(satellite_id[8], 2));
	append(s, format(satellite_id[9], 2));
	append(s, format(satellite_id[10], 2));
	append(s, format(satellite_id[11], 2));
	append(s, to_string(pdop));
	append(s, to_string(hdop));
	append(s, to_string(vdop));
}
}
}
