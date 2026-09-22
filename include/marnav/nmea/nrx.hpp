#ifndef MARNAV_NMEA_NRX_HPP
#define MARNAV_NMEA_NRX_HPP

#include "marnav/nmea/date.hpp"
#include "marnav/nmea/sentence.hpp"
#include "marnav/nmea/time.hpp"

#include <optional>

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
		char b1_transmitter_identity = '\0';
		char b2_subject_indicator = '\0';
		uint32_t b3_b4_serial = 0u;
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
	uint32_t number_sentences_;
	uint32_t sentence_number_;
	int sequential_id_;
	std::optional<message_code> message_code_;
	std::optional<frequency_index> frequency_index_;
	std::optional<time> time_utc_;
	std::optional<date> date_;
	std::optional<uint32_t> total_characters_;
	std::optional<uint32_t> total_bad_characters_;
	std::optional<status> status_;
	std::optional<std::string> message_;

public:
	uint32_t get_number_sentences() const { return number_sentences_; };
	uint32_t get_sentence_number() const { return sentence_number_; };
	uint32_t get_sequential_id() const { return sequential_id_; };
	std::optional<message_code> get_message_code() const { return message_code_; };
	std::optional<frequency_index> get_frequency_index() const { return frequency_index_; };
	std::optional<time> get_time_utc() const { return time_utc_; };
	std::optional<date> get_utc_date() const { return date_; };
	std::optional<uint32_t> get_total_characters() const { return total_characters_; };
	std::optional<uint32_t> get_total_bad_characters() const { return total_bad_characters_; };
	std::optional<status> get_status() const { return status_; };
	std::optional<std::string> get_message() const { return message_; };

	/**
	 * @brief Return parsed reserved charachters which is showable (on screen)
	 * @return 
	 */
	std::optional<std::string> get_parsed_message() const;

	void set_number_sentences(uint32_t value) { number_sentences_ = value; }
	void set_sentence_number(uint32_t value) { sentence_number_ = value; }
	void set_sequential_id(uint32_t value) { sequential_id_ = value; }
	void set_message_code(const message_code & t) noexcept { message_code_ = t; }
	void set_frequency_index(frequency_index t) noexcept { frequency_index_ = t; }
	void set_time_utc(const time & t) noexcept { time_utc_ = t; }
	void set_date(const date & t) noexcept { date_ = t; }
	void set_total_characters(uint32_t t) noexcept { total_characters_ = t; }
	void set_total_bad_characters(uint32_t t) noexcept { total_bad_characters_ = t; }
	void set_status(status s) noexcept { status_ = s; }
	void set_message(const std::string & m);

private:
	std::optional<message_code> fill_message_code(const std::string & m) const;
	void check() const;
};
}
#endif // MARNAV_NMEA_NRX_HPP
