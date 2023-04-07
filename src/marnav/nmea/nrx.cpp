#include "marnav/nmea/nrx.hpp"
#include "marnav/nmea/io.hpp"
#include <stdexcept>

namespace marnav::nmea
{
constexpr sentence_id nrx::ID;
constexpr const char * nrx::TAG;
constexpr int HEX_LENGTH = 2;

nrx::nrx()
	: sentence(ID, TAG, talker::communications_telex)
	, m_number_sentences(0u)
	, m_sentence_number(0u)
	, m_sequential_id(0)
{
}

nrx::nrx(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	constexpr int NRX_MESSAGE_FIELDS = 13;

	if (std::distance(first, last) != NRX_MESSAGE_FIELDS)
		throw std::invalid_argument{"invalid number of fields in nrx"};

	read(*(first + 0), m_number_sentences);
	read(*(first + 1), m_sentence_number);
	read(*(first + 2), m_sequential_id);

	std::string message_code;
	read(*(first + 3), message_code);
	fill_message_code(message_code);

	read(*(first + 4), m_frequency_index);
	read(*(first + 5), m_time_utc);

	std::optional<uint32_t> d;
	std::optional<uint32_t> m;
	std::optional<uint32_t> y;

	read(*(first + 6), d);
	read(*(first + 7), m);
	read(*(first + 8), y);

	if (d && m && y)
		m_date = nmea::date{*y, to_month(*m), *d};

	read(*(first + 9), m_total_characters);
	read(*(first + 10), m_total_bad_characters);
	read(*(first + 11), m_status);

	std::string message;
	read(*(first + 12), message);
	fill_message_body(message);

	check();
}

inline std::string hex_to_ascii(const std::string & s)
{
	if (s.size() != HEX_LENGTH)
		return {};
	return std::string{static_cast<char>(std::stoul(s.substr(0, HEX_LENGTH), nullptr, 16))};
}

inline std::string to_string(const std::optional<nrx::message_code> & m)
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

	if (m_date) {
		d = m_date->day();
		m = to_numeric(m_date->mon());
		y = m_date->year();
	}

	append(s, format(m_number_sentences, 3));
	append(s, format(m_sentence_number, 3));
	append(s, format(m_sequential_id, 2));
	append(s, to_string(m_message_code));
	append(s, to_string(m_frequency_index));
	append(s, to_string(m_time_utc));
	append(s, format(d, 2));
	append(s, format(m, 2));
	append(s, format(y, 4));
	append(s, to_string(m_total_characters));
	append(s, to_string(m_total_bad_characters));
	append(s, to_string(m_status));
	append(s, to_string(m_message));
}

inline void nrx::fill_message_code(const std::string & m) noexcept
{
	constexpr int MESSAGE_CODE_LENGTH = 4;

	if (m.size() == MESSAGE_CODE_LENGTH) {
		std::string::const_iterator iter = m.cbegin();
		m_message_code->b1_transmitter_identity = *iter++;
		m_message_code->b2_subject_indicator = *iter++;
		m_message_code->b3_b4_serial = std::stol(m.substr(m.size() - 2));
	}
}

inline void nrx::fill_message_body(std::string & message) noexcept
{
	constexpr char HEX_DELIMITER = '^';
	constexpr int TO_REPLACE_LENGTH = HEX_LENGTH + sizeof(HEX_DELIMITER);

	size_t pos = message.find(HEX_DELIMITER);
	while (pos != std::string::npos) {
		const std::string & ascii_str = hex_to_ascii(message.substr(pos + 1, HEX_LENGTH));
		message.replace(pos, TO_REPLACE_LENGTH, ascii_str);
		pos = message.find(HEX_DELIMITER);
	}

	m_message = message;
}

void nrx::check() const
{
	if ((m_number_sentences < 1) || (m_number_sentences > 999))
		throw std::invalid_argument{"invalid number of sentences"};

	if ((m_sentence_number < 1) || (m_sentence_number > 999))
		throw std::invalid_argument{"invalid sentence number"};

	if ((m_sequential_id < 0) || (m_sequential_id > 99))
		throw std::invalid_argument{"invalid sequential message number"};
}
}
