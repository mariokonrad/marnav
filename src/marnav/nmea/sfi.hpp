#ifndef MARNAV__NMEA__SFI__HPP
#define MARNAV__NMEA__SFI__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief SFI - Scanning Frequency Information
///
/// @code
///        1   2   3      4
///        |   |   |      |
/// $--SFI,x.x,x.x,xxxxxx,c .......... xxxxxx,c*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Total Number Of Messages
/// 2. Message Number
/// 3. Frequency 1
/// 4. Mode 1
///
class sfi : public sentence
{
	friend class detail::factory;

public:
	struct scanning_frequency {
		uint32_t frequency; // [kHz]
		char mode;
	};

	constexpr static sentence_id ID = sentence_id::SFI;
	constexpr static const char * TAG = "SFI";
	constexpr static int max_number_of_frequencies = 10;

	sfi();
	sfi(const sfi &) = default;
	sfi & operator=(const sfi &) = default;
	sfi(sfi &&) = default;
	sfi & operator=(sfi &&) = default;

protected:
	sfi(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	uint32_t number_of_messages_ = 0;
	uint32_t message_number_ = 0;
	std::vector<scanning_frequency> frequencies_;

public:
	decltype(number_of_messages_) get_n_messages() const { return number_of_messages_; }
	decltype(message_number_) get_message_number() const { return message_number_; }
	decltype(frequencies_) get_frequencies() const { return frequencies_; }

	void set_number_of_messages(uint32_t t) noexcept { number_of_messages_ = t; }
	void set_message_number(uint32_t t) noexcept { message_number_ = t; }
	void set_frequencies(const std::vector<scanning_frequency> & v);
};
}
}

#endif
