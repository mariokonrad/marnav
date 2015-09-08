#include "gsv.hpp"
#include <algorithm>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

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
	, n_messages(1)
	, message_number(1)
	, n_satellites_in_view(0)
{
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

std::unique_ptr<sentence> gsv::parse(
	const std::string & talker, const std::vector<std::string> & fields)
{
	// empty fields for satellite information are not necessary, therefore
	// there are a variable number of fields. however, the first 3 are
	// mandatory and the rest must be a multiple of 4 (the four parts
	// of satellite information).
	if ((fields.size() < 3) || ((fields.size() - 3) % 4 != 0)) {
		throw std::invalid_argument{
			std::string{"invalid number of fields in gsv::parse: expected 3+n*4, got "}
			+ std::to_string(fields.size())};
	}

	std::unique_ptr<sentence> result = utils::make_unique<gsv>();
	result->set_talker(talker);
	gsv & detail = static_cast<gsv &>(*result);

	read(fields[0], detail.n_messages);
	read(fields[1], detail.message_number);
	read(fields[2], detail.n_satellites_in_view);

	const int num_satellite_info = std::min(4, static_cast<int>((fields.size() - 3) / 4));
	int index = 3;
	for (int id = 0; id < num_satellite_info; ++id, index += 4) {
		satellite_info info;
		read(fields[index + 0], info.id);
		read(fields[index + 1], info.elevation);
		read(fields[index + 2], info.azimuth);
		read(fields[index + 3], info.snr);
		detail.set_sat(id, info);
	}

	return result;
}

std::vector<std::string> gsv::get_data() const
{
	return {to_string(n_messages), to_string(message_number), to_string(n_satellites_in_view),
		to_string(sat[0]), to_string(sat[1]), to_string(sat[2]), to_string(sat[3])};
}
}
}

