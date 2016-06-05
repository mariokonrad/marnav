#include "gsa.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(gsa)

constexpr const char * gsa::TAG;

gsa::gsa()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

gsa::gsa(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	if (std::distance(first, last) != 17)
		throw std::invalid_argument{"invalid number of fields in gsa"};

	read(*(first + 0), sel_mode);
	read(*(first + 1), mode);

	int index = 2;
	for (auto i = 0; i < max_satellite_ids; ++i, ++index) {
		uint32_t id;
		read(*(first + index), id);
		set_satellite_id(i + 1, id);
	}
	read(*(first + 14), pdop);
	read(*(first + 15), hdop);
	read(*(first + 16), vdop);
}

void gsa::check_index(int index) const
{
	if ((index < 1) || (index > 12)) {
		throw std::out_of_range{"satellite id out of range"};
	}
}

void gsa::set_satellite_id(int index, uint32_t t)
{
	check_index(index);
	satellite_id[index - 1] = t;
}

utils::optional<uint32_t> gsa::get_satellite_id(int index) const
{
	check_index(index);
	return satellite_id[index - 1];
}

std::vector<std::string> gsa::get_data() const
{
	return {to_string(sel_mode), to_string(mode), format(satellite_id[0], 2),
		format(satellite_id[1], 2), format(satellite_id[2], 2), format(satellite_id[3], 2),
		format(satellite_id[4], 2), format(satellite_id[5], 2), format(satellite_id[6], 2),
		format(satellite_id[7], 2), format(satellite_id[8], 2), format(satellite_id[9], 2),
		format(satellite_id[10], 2), format(satellite_id[11], 2), to_string(pdop),
		to_string(hdop), to_string(vdop)};
}
}
}
