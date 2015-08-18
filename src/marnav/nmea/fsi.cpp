#include "fsi.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
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

void fsi::set_power_level(uint32_t t) throw(std::invalid_argument)
{
	if (t > 9)
		throw std::invalid_argument{"invalid value for power_level (0..9)"};
	power_level = t;
}

void fsi::set_sentence_status(char t) throw(std::invalid_argument)
{
	check_value(t, {'R', 'C'}, "sentence_status");
	sentence_status = t;
}

std::unique_ptr<sentence> fsi::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument, std::runtime_error)
{
	if (fields.size() != 5)
		throw std::invalid_argument{"invalid number of fields in fsi::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<fsi>();
	result->set_talker(talker);
	fsi & detail = static_cast<fsi &>(*result);

	read(fields[0], detail.tx_frequency);
	read(fields[1], detail.rx_frequency);
	read(fields[2], detail.communications_mode);
	read(fields[3], detail.power_level);
	read(fields[4], detail.sentence_status);

	return result;
}

std::vector<std::string> fsi::get_data() const
{
	return {to_string(tx_frequency), to_string(rx_frequency), to_string(communications_mode),
		to_string(power_level), to_string(sentence_status)};
}
}
}
