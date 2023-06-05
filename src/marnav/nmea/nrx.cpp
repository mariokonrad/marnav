#include "marnav/nmea/nrx.hpp"
#include "marnav/nmea/io.hpp"
#include <stdexcept>

namespace marnav::nmea
{
constexpr sentence_id nrx::ID;
constexpr const char * nrx::TAG;

// Holds pre-defined reserved charachters
const std::unordered_map<std::string, std::string> reserved_characters{
	{"\r", "^0D"},
	{"\n", "^0A"},
	{"*", "^2A"},
	{",", "^2C"},
	{"$", "^24"},
	{"!", "^21"},
	{"\\", "^5C"},
	{"^", "^5E"},
	{"~", "^7E"},
	{"<del>", "^7F"},
};

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

std::optional<std::string> nrx::get_parsed_message() const
{
	std::optional<std::string> m;

	if (!message_.has_value())
		return m;

	m = message_;

	size_t start_pos = 0;
	for (const auto & [key, hex] : reserved_characters) {
		start_pos = 0;
		while ((start_pos = m->find(hex, start_pos)) != std::string::npos) {
			m->replace(start_pos, hex.length(), key);
			start_pos += key.length();
		}
	}
	return m;
}

void nrx::set_message(const std::string & m)
{
	constexpr int MAX_NMEA_SENTENCE_LENGTH = 79;
	if (m.length() > MAX_NMEA_SENTENCE_LENGTH)
		throw std::invalid_argument{"Message exceeds max nmea charachters"};

	message_ = m;

	if (!message_.has_value())
		return;

	size_t start_pos = 0;
	for (const auto & [key, hex] : reserved_characters) {
		start_pos = 0;
		while ((start_pos = message_->find(key, start_pos)) != std::string::npos) {
			message_->replace(start_pos, key.length(), hex);
			start_pos += hex.length();
		}
	}
}

std::optional<nrx::message_code> nrx::fill_message_code(const std::string & m) const
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
