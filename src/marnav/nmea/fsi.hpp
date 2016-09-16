#ifndef __NMEA__FSI__HPP__
#define __NMEA__FSI__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(fsi)

/// @brief FSI - Frequency Set Information
///
/// @code
///         1      2      3 4 5
///         |      |      | | |
///  $--FSI,xxxxxx,xxxxxx,c,x,a*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Transmitting Frequency in 100Hz increments
/// 2. Receiving Frequency in 100Hz increments
/// 3. Mode of operation
/// 4. Power Level
///    - 0 = standby
///    - 1..9 = intensity (1=lowest, 9=highest)
/// 5. Sentence Status Flag
///    - R = Report of current settings
///    - C = Configuration command to change settings
///
class fsi : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(fsi)

public:
	constexpr static const sentence_id ID = sentence_id::FSI;
	constexpr static const char * TAG = "FSI";

	virtual ~fsi() {}

	fsi();
	fsi(const fsi &) = default;
	fsi & operator=(const fsi &) = default;

protected:
	fsi(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<uint32_t> tx_frequency;
	utils::optional<uint32_t> rx_frequency;
	utils::optional<char> communications_mode;
	utils::optional<uint32_t> power_level;
	utils::optional<char> sentence_status;

public:
	MARNAV_NMEA_GETTER(tx_frequency)
	MARNAV_NMEA_GETTER(rx_frequency)
	MARNAV_NMEA_GETTER(communications_mode)
	MARNAV_NMEA_GETTER(power_level)
	MARNAV_NMEA_GETTER(sentence_status)

	void set_tx_frequency(uint32_t t) noexcept { tx_frequency = t; }
	void set_rx_frequency(uint32_t t) noexcept { rx_frequency = t; }
	void set_communications_mode(char t) noexcept { communications_mode = t; }
	void set_power_level(uint32_t t);
	void set_sentence_status(char t);
};
}
}

#endif
