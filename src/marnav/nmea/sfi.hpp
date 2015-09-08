#ifndef __NMEA__SFI__HPP__
#define __NMEA__SFI__HPP__

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
public:
	struct scanning_frequency {
		uint32_t frequency; // [kHz]
		char mode;
	};

	constexpr static const sentence_id ID = sentence_id::SFI;
	constexpr static const char * TAG = "SFI";
	constexpr static const unsigned int MAX_NUMBER_OF_FREQUENCIES = 10;

	sfi();
	sfi(const sfi &) = default;
	sfi & operator=(const sfi &) = default;

	static std::unique_ptr<sentence> parse(
		const std::string & talker, const std::vector<std::string> & fields);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	uint32_t number_of_messages;
	uint32_t message_number;
	std::vector<scanning_frequency> frequencies;

public:
	NMEA_GETTER(number_of_messages)
	NMEA_GETTER(message_number)
	NMEA_GETTER(frequencies)

	void set_number_of_messages(uint32_t t) noexcept { number_of_messages = t; }
	void set_message_number(uint32_t t) noexcept { message_number = t; }
	void set_frequencies(const std::vector<scanning_frequency> & v);
};
}
}

#endif
