#include "gsv.hpp"
#include "io.hpp"
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

gsv::gsv()
	: sentence(ID, "GSV", talker_id::global_positioning_system)
{
}

void gsv::check_index(int index) const throw(std::out_of_range)
{
	if ((index < 0) || (index > 3)) {
		throw std::out_of_range{"satellite id out of range"};
	}
}

void gsv::set_sat(int index, const satellite_info & info) throw(std::out_of_range)
{
	check_index(index);
	sat[index] = info;
}

utils::optional<gsv::satellite_info> gsv::get_sat(int index) const throw(std::out_of_range)
{
	check_index(index);
	return sat[index];
}

std::unique_ptr<sentence> gsv::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 19) {
		throw std::invalid_argument{
			std::string{"invalid number of fields in gsv::parse: expected 19, got "}
			+ std::to_string(fields.size())};
	}

	std::unique_ptr<sentence> result = utils::make_unique<gsv>();
	result->set_talker(talker);
	gsv & detail = static_cast<gsv &>(*result);

	read(fields[0], detail.n_messages);
	read(fields[1], detail.message_number);
	read(fields[2], detail.n_satellites_in_view);

	int index = 3;
	for (int id = 0; id < 4; ++id, index += 4) {
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

