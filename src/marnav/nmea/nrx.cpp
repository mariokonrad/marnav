#include "marnav/nmea/nrx.hpp"
#include "marnav/nmea/io.hpp"
#include <stdexcept>

namespace marnav::nmea
{
constexpr sentence_id nrx::ID;
constexpr const char * nrx::TAG;

nrx::nrx()
	: sentence(ID, TAG, talker::communications_telex)
	, number_sentences_(0u)
	, sentence_number_(0u)
	, sequential_id_(0)
{
}

nrx::nrx(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	constexpr int NRX_MESSAGE_FIELDS = 13;

	if (std::distance(first, last) != NRX_MESSAGE_FIELDS)
		throw std::invalid_argument{"invalid number of fields in nrx"};

	read(*(first + 0), number_sentences_);
	read(*(first + 1), sentence_number_);
	read(*(first + 2), sequential_id_);

	std::string message_code;
	read(*(first + 3), message_code);
	message_code_ = fill_message_code(message_code);

	read(*(first + 4), frequency_index_);
	read(*(first + 5), time_utc_);

	std::optional<uint32_t> d;
	std::optional<uint32_t> m;
	std::optional<uint32_t> y;

	read(*(first + 6), d);
	read(*(first + 7), m);
	read(*(first + 8), y);

	if (d && m && y)
		date_ = nmea::date{*y, to_month(*m), *d};

	read(*(first + 9), total_characters_);
	read(*(first + 10), total_bad_characters_);
	read(*(first + 11), status_);
	read(*(first + 12), message_);
	check();
}

std::string to_string(const std::optional<nrx::message_code> & m)
{
	if (!m.has_value())
		return {};

	std::string r;
	r.push_back(m->b1_transmitter_identity);
	r.push_back(m->b2_subject_indicator);
	r += format(m->b3_b4_serial, 2);
	return r;
}

void nrx::append_data_to(std::string & s, const version &) const
{
	std::optional<uint32_t> d;
	std::optional<uint32_t> m;
	std::optional<uint32_t> y;

	if (date_) {
		d = date_->day();
		m = to_numeric(date_->mon());
		y = date_->year();
	}

	append(s, format(number_sentences_, 3));
	append(s, format(sentence_number_, 3));
	append(s, format(sequential_id_, 2));
	append(s, to_string(message_code_));
	append(s, to_string(frequency_index_));
	append(s, to_string(time_utc_));
	append(s, format(d, 2));
	append(s, format(m, 2));
	append(s, format(y, 4));
	append(s, to_string(total_characters_));
	append(s, to_string(total_bad_characters_));
	append(s, to_string(status_));
	append(s, to_string(message_));
}

inline std::optional<nrx::message_code> nrx::fill_message_code(const std::string & m) noexcept
{
	constexpr int MESSAGE_CODE_LENGTH = 4;
	if (m.size() != MESSAGE_CODE_LENGTH)
		return {};

	std::string::const_iterator iter = m.cbegin();
	nrx::message_code code;
	code.b1_transmitter_identity = *iter++;
	code.b2_subject_indicator = *iter++;
	code.b3_b4_serial = std::stol(m.substr(m.size() - 2));
	return code;
}

void nrx::check() const
{
	if ((number_sentences_ < 1) || (number_sentences_ > 999))
		throw std::invalid_argument{"invalid number of sentences"};

	if ((sentence_number_ < 1) || (sentence_number_ > 999))
		throw std::invalid_argument{"invalid sentence number"};

	if ((sequential_id_ < 0) || (sequential_id_ > 99))
		throw std::invalid_argument{"invalid sequential message number"};
}
}
