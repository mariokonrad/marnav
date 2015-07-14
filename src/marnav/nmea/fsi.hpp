#ifndef __NMEA__FSI__HPP__
#define __NMEA__FSI__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief FSI - Frequency Set Information
///
/// @code
///         1      2      3 4 5
///         |      |      | | |
///  $--FSI,xxxxxx,xxxxxx,c,x*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Transmitting Frequency
/// 2. Receiving Frequency
/// 3. Communications Mode (NMEA Syntax 2)
/// 4. Power Level
/// 5. Checksum
///
class fsi : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::FSI;
	constexpr static const char * TAG = "FSI";

	fsi();
	fsi(const fsi &) = default;
	fsi & operator=(const fsi &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<uint32_t> tx_frequency; // [kHz]
	utils::optional<uint32_t> rx_frequency; // [kHz]
	utils::optional<char> communications_mode;
	utils::optional<uint32_t> power_level;

public:
	decltype(tx_frequency) get_tx_frequency() const { return tx_frequency; }
	decltype(rx_frequency) get_rx_frequency() const { return rx_frequency; }
	decltype(communications_mode) get_communications_mode() const
	{
		return communications_mode;
	}
	decltype(power_level) get_power_level() const { return power_level; }

	void set_tx_frequency(uint32_t t) { tx_frequency = t; }
	void set_rx_frequency(uint32_t t) { rx_frequency = t; }
	void set_communications_mode(char t) { communications_mode = t; }
	void set_power_level(uint32_t t) { power_level = t; }
};
}
}

#endif
