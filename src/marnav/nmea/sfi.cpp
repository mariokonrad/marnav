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

void sfi::set_frequencies(const std::vector<scanning_frequency> & v)
{
	if (v.size() > max_number_of_frequencies)
		throw std::invalid_argument{
			"number of frequencies exceeds max entries in sfi::set_frequencies"};

	frequencies = v;
}

std::unique_ptr<sentence> sfi::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	const auto size = std::distance(first, last);
	if ((size < 2) || (size > 2 + max_number_of_frequencies * 2))
		throw std::invalid_argument{"invalid number of fields in sfi::parse"};
	if (size % 2 != 0)
		throw std::invalid_argument{"invalid number of fields in sfi::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<sfi>();
	result->set_talker(talker);
	sfi & detail = static_cast<sfi &>(*result);

	read(*(first + 0), detail.number_of_messages);
	read(*(first + 1), detail.message_number);

	detail.frequencies.clear();
	detail.frequencies.reserve(size - 2);
	for (auto i = 2; i < size; i += 2) {
		uint32_t frequency;
		char mode;
		read(*(first + i + 0), frequency);
		read(*(first + i + 1), mode);
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
