#include <marnav/nmea/sfi.hpp>
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav::nmea
{
constexpr sentence_id sfi::ID;
constexpr const char * sfi::TAG;
constexpr int sfi::max_number_of_frequencies;

sfi::sfi()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

sfi::sfi(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	const auto size = std::distance(first, last);
	if ((size < 2) || (size > 2 + max_number_of_frequencies * 2))
		throw std::invalid_argument{"invalid number of fields in sfi"};
	if (size % 2 != 0)
		throw std::invalid_argument{"invalid number of fields in sfi"};

	read(*(first + 0), number_of_messages_);
	read(*(first + 1), message_number_);

	frequencies_.clear();
	frequencies_.reserve(size - 2);
	for (auto i = 2; i < size; i += 2) {
		uint32_t frequency;
		char mode;
		read(*(first + i + 0), frequency);
		read(*(first + i + 1), mode);
		frequencies_.push_back({frequency, mode});
	}
}

void sfi::set_frequencies(const std::vector<scanning_frequency> & v)
{
	if (v.size() > max_number_of_frequencies)
		throw std::invalid_argument{
			"number of frequencies exceeds max entries in sfi::set_frequencies"};

	frequencies_ = v;
}

void sfi::append_data_to(std::string & s, const version &) const
{
	append(s, to_string(number_of_messages_));
	append(s, to_string(message_number_));
	for (auto const & entry : frequencies_) {
		append(s, to_string(entry.frequency));
		append(s, to_string(entry.mode));
	}
}
}
