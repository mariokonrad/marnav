#ifndef MARNAV_NMEA_NRX_HPP
#define MARNAV_NMEA_NRX_HPP

#include <optional>

#include "marnav/nmea/date.hpp"
#include "marnav/nmea/sentence.hpp"
#include "marnav/nmea/time.hpp"

namespace marnav::nmea
{
/// @brief NRX - Navtex message: global maritime safety information
///
/// @code
///        1   2   3  4    56789 10  11  12 13
///        |   |   |  |    ||||| |   |   |  |
/// $--NRX,XXX,XXX,XX,aaXX,X,,,,,X.X,X.X,A,c-----c*hh<CR> <LF>
/// @endcode
///
/// Field Number:
/// 1. Number of sentences 001 – 999
/// 2. Sentence number 001 – 999
/// 3. Sequential message number 00 – 99 ( used to uniquely identify messages of same ID )
/// 4. NAVTEX message ID characters (B1, B2 , B3 , B4)
///	   - B1 = Transmitter identity (alphabet)
///    - B2 = Subject indicator (alphabet)
///    - B3&B4 = Serial number of the subject indicator (integeral)
/// 5. Frequency index
///    - 0 = Not received over air
///    - 1 = 490 kHz
///    - 2 = 518 kHz
///    - 3 = 4209.5 kHz
/// 6. UTC
/// 7. Day
/// 8. Month
/// 9. Year
/// 10. Total number of characters in this series of NRX sentences
/// 11. Total number of bad characters
/// 12. Status
///    - A = Data Valid
///    - V = Invalid
/// 13. Message body (first line o f message text characters)
///
/// Example:
/// @code
/// $CRNRX,007,001,00,TD02,1,135600,27,06,2001,241,3,A,==========================*18
///	$CRNRX,007,002,00,,,,,,,,,,========^0D^0AISSUED ON SATURDAY 06 JANUARY 2001.*29
///	$CRNRX,007,003,00,,,,,,,,,,^0D^0AINSHORE WATERS FORECAST TO 12 MILES^0D^0AOFF*0D
///	$CRNRX,007,004,00,,,,,,,,,,SHORE FROM 1700 UTC TO 0500 UTC.^0D^0A^0D^0ANORT*1E
///	$CRNRX,007,005,00,,,,,,,,,,H FORELAND TO SELSEY BILL.^0D^0A12 HOURS FOREC*09
///	$CRNRX,007,006,00,,,,,,,,,,AST:^0D^0A^0ASHOWERY WINDS^2C STRONGEST IN NORTH.^0D*16
///	$CRNRX,007,007,00,,,,,,,,,,^0A^0A*79
/// @endcode
///
/// @note The data characters in fields 4 to 12 are output in the first message
///		  line only; they are null fields in the subsequent message lines

class nrx : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::NRX;
	constexpr static const char * TAG = "NRX";

	struct message_code {
		char b1_transmitter_identity;
		char b2_subject_indicator;
		uint8_t b3_b4_serial;
	};

	nrx();
	nrx(const nrx &) = default;
	nrx & operator=(const nrx &) = default;
	nrx(nrx &&) = default;
	nrx & operator=(nrx &&) = default;

protected:
	nrx(talker talk, fields::const_iterator first, fields::const_iterator last);
	void append_data_to(std::string &, const version &) const override;

private:
	uint16_t m_number_sentences;
	uint16_t m_sentence_number;
	int m_sequential_id;
	std::optional<message_code> m_message_code;
	std::optional<frequency_index> m_frequency_index;
	std::optional<time> m_time_utc;
	std::optional<date> m_date;
	std::optional<uint32_t> m_total_characters;
	std::optional<uint32_t> m_total_bad_characters;
	std::optional<status> m_status;
	std::optional<std::string> m_message;

public:
	uint16_t get_number_sentences() const { return m_number_sentences; };
	uint16_t get_sentence_number() const { return m_sentence_number; };
	uint8_t get_sequential_id() const { return m_sequential_id; };
	std::optional<message_code> get_message_code() const { return m_message_code; };
	std::optional<frequency_index> get_frequency_index() const { return m_frequency_index; };
	std::optional<time> get_time_utc() const { return m_time_utc; };
	std::optional<date> get_utc_date() const { return m_date; };
	std::optional<uint32_t> get_total_characters() const { return m_total_characters; };
	std::optional<uint32_t> get_total_bad_characters() const { return m_total_bad_characters; };
	std::optional<status> get_status() const { return m_status; };
	std::optional<std::string> get_message() const { return m_message; };

	void set_number_sentences(uint16_t value) { m_number_sentences = value; }
	void set_sentence_number(uint16_t value) { m_sentence_number = value; }
	void set_sequential_id(uint8_t value) { m_sequential_id = value; }
	void set_message_code(const message_code & t) noexcept { m_message_code = t; }
	void set_frequency_index(frequency_index t) noexcept { m_frequency_index = t; }
	void set_time_utc(const time & t) noexcept { m_time_utc = t; }
	void set_date(const date & t) noexcept { m_date = t; }
	void set_total_characters(uint32_t t) noexcept { m_total_characters = t; }
	void set_total_bad_characters(uint32_t t) noexcept { m_total_bad_characters = t; }
	void set_status(status s) noexcept { m_status = s; }
	void set_message(const std::string & m) noexcept { m_message = m; }

private:
	inline std::optional<message_code> fill_message_code(const std::string & m) noexcept;
	inline void fill_message_body(std::string & message) noexcept;
	inline void check() const;
};
}
#endif // MARNAV_NMEA_NRX_HPP
