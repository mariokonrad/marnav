#include "sfi.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(sfi)

constexpr const char * sfi::TAG;

sfi::sfi()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

sfi::sfi(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	const auto size = std::distance(first, last);
	if ((size < 2) || (size > 2 + max_number_of_frequencies * 2))
		throw std::invalid_argument{"invalid number of fields in sfi"};
	if (size % 2 != 0)
		throw std::invalid_argument{"invalid number of fields in sfi"};

	read(*(first + 0), number_of_messages);
	read(*(first + 1), message_number);

	frequencies.clear();
	frequencies.reserve(size - 2);
	for (auto i = 2; i < size; i += 2) {
		uint32_t frequency;
		char mode;
		read(*(first + i + 0), frequency);
		read(*(first + i + 1), mode);
		frequencies.push_back({frequency, mode});
	}
}

void sfi::set_frequencies(const std::vector<scanning_frequency> & v)
{
	if (v.size() > max_number_of_frequencies)
		throw std::invalid_argument{
			"number of frequencies exceeds max entries in sfi::set_frequencies"};

	frequencies = v;
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
