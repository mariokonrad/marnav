#include <marnav/nmea/stalk.hpp>
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
constexpr sentence_id stalk::ID;
constexpr const char * stalk::TAG;

constexpr int stalk::MIN_FIELDS;
constexpr int stalk::MAX_FIELDS;

stalk::stalk()
	: sentence(ID, TAG, talker_id::none)
{
}

stalk::stalk(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	const auto d = std::distance(first, last);
	if ((d < MIN_FIELDS) || (d > MAX_FIELDS))
		throw std::invalid_argument{"invalid number of fields in stalk"};

	data_ = raw{};
	data_.reserve(d);
	for (int i = 0; i < d; ++i) {
		const auto & s = *(first + i);
		if (s.size() != 2u)
			throw std::invalid_argument{"invalid format of payload"};
		uint8_t b;
		read(s, b, data_format::hex);
		data_.push_back(b);
	}
}

void stalk::append_data_to(std::string & s) const
{
	if (data_.empty())
		throw std::runtime_error{"invalid number of bytes in data"};
	for (const auto a : data_)
		append(s, format(a, 2, data_format::hex));
}

void stalk::set_data(const raw & t)
{
	if ((t.size() < MIN_FIELDS) || (t.size() > MAX_FIELDS))
		throw std::invalid_argument{"invalid number of bytes in data"};
	data_ = t;
}
}
}
