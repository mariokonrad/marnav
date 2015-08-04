#include "sfi.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * sfi::TAG;

sfi::sfi()
	: sentence(ID, TAG, talker_id::global_positioning_system)
	, number_of_messages(0)
	, message_number(0)
{
}

void sfi::set_frequencies(const std::vector<scanning_frequency> & v) throw(
	std::invalid_argument)
{
	if (v.size() > MAX_NUMBER_OF_FREQUENCIES)
		throw std::invalid_argument{
			"number of frequencies exceeds max entries in sfi::set_frequencies"};

	frequencies = v;
}

std::unique_ptr<sentence> sfi::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if ((fields.size() < 2) || (fields.size() > 2 + MAX_NUMBER_OF_FREQUENCIES * 2))
		throw std::invalid_argument{"invalid number of fields in sfi::parse"};
	if (fields.size() % 2 != 0)
		throw std::invalid_argument{"invalid number of fields in sfi::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<sfi>();
	result->set_talker(talker);
	sfi & detail = static_cast<sfi &>(*result);

	read(fields[0], detail.number_of_messages);
	read(fields[1], detail.message_number);

	detail.frequencies.clear();
	detail.frequencies.reserve(fields.size() - 2);
	for (size_t i = 2; i < fields.size(); i += 2) {
		uint32_t frequency;
		char mode;
		read(fields[i], frequency);
		read(fields[i], mode);
		detail.frequencies.push_back({frequency, mode});
	}

	return result;
}

std::vector<std::string> sfi::get_data() const
{
	std::vector<std::string> result{to_string(number_of_messages), to_string(message_number)};

	for (auto const & entry : frequencies) {
		result.push_back(to_string(entry.frequency));
		result.push_back(to_string(entry.mode));
	}

	return result;
}
}
}
