#include "fsi.hpp"
#include "io.hpp"
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * fsi::TAG;

fsi::fsi()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

std::unique_ptr<sentence> fsi::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 4)
		throw std::invalid_argument{"invalid number of fields in fsi::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<fsi>();
	result->set_talker(talker);
	fsi & detail = static_cast<fsi &>(*result);

	read(fields[0], detail.tx_frequency);
	read(fields[1], detail.rx_frequency);
	read(fields[2], detail.communications_mode);
	read(fields[3], detail.power_level);

	return result;
}

std::vector<std::string> fsi::get_data() const
{
	return {to_string(tx_frequency), to_string(rx_frequency), to_string(communications_mode),
		to_string(power_level)};
}
}
}
