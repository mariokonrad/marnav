#include "gsv.hpp"
#include <algorithm>
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(gsv)

namespace
{
inline std::string to_string(const utils::optional<gsv::satellite_info> & data)
{
	if (!data)
		return std::string{",,,"};
	auto const & value = data.value();
	return format(value.id, 2) + "," + format(value.elevation, 2) + ","
		+ format(value.azimuth, 3) + "," + format(value.snr, 2);
}
}

constexpr const char * gsv::TAG;

gsv::gsv()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

gsv::gsv(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	// empty fields for satellite information are not necessary, therefore
	// there are a variable number of fields. however, the first 3 are
	// mandatory and the rest must be a multiple of 4 (the four parts
	// of satellite information).
	const auto size = std::distance(first, last);
	if ((size < 3) || ((size - 3) % 4 != 0)) {
		throw std::invalid_argument{
			std::string{"invalid number of fields in gsv: expected 3+n*4, got "}
			+ std::to_string(size)};
	}

	read(*(first + 0), n_messages);
	read(*(first + 1), message_number);
	read(*(first + 2), n_satellites_in_view);

	const int num_satellite_info = std::min(4, static_cast<int>((size - 3) / 4));
	int index = 3;
	for (int id = 0; id < num_satellite_info; ++id, index += 4) {
		satellite_info info;
		read(*(first + index + 0), info.id);
		read(*(first + index + 1), info.elevation);
		read(*(first + index + 2), info.azimuth);
		read(*(first + index + 3), info.snr);
		set_sat(id, info);
	}
}

void gsv::set_n_messages(uint32_t t)
{
	if (t < 1)
		throw std::invalid_argument{"minimum of 1 for n_messages mandatory"};
	n_messages = t;
}

void gsv::set_message_number(uint32_t t)
{
	if (t < 1)
		throw std::invalid_argument{"minimum of 1 for message_number mandatory"};
	message_number = t;
}

void gsv::check_index(int index) const
{
	if ((index < 0) || (index > 3)) {
		throw std::out_of_range{"satellite id out of range"};
	}
}

void gsv::set_sat(int index, const satellite_info & info)
{
	check_index(index);
	sat[index] = info;
}

utils::optional<gsv::satellite_info> gsv::get_sat(int index) const
{
	check_index(index);
	return sat[index];
}

std::vector<std::string> gsv::get_data() const
{
	return {to_string(n_messages), to_string(message_number), to_string(n_satellites_in_view),
		to_string(sat[0]), to_string(sat[1]), to_string(sat[2]), to_string(sat[3])};
}
}
}
