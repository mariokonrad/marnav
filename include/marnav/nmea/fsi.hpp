#ifndef MARNAV_NMEA_FSI_HPP
#define MARNAV_NMEA_FSI_HPP

#include <marnav/nmea/sentence.hpp>
#include <optional>

namespace marnav
{
namespace nmea
{
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
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::FSI;
	constexpr static const char * TAG = "FSI";

	fsi();
	fsi(const fsi &) = default;
	fsi & operator=(const fsi &) = default;
	fsi(fsi &&) = default;
	fsi & operator=(fsi &&) = default;

protected:
	fsi(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<uint32_t> tx_frequency_;
	std::optional<uint32_t> rx_frequency_;
	std::optional<char> communications_mode_;
	std::optional<uint32_t> power_level_;
	std::optional<char> sentence_status_;

public:
	std::optional<uint32_t> get_tx_frequency() const { return tx_frequency_; }
	std::optional<uint32_t> get_rx_frequency() const { return rx_frequency_; }
	std::optional<char> get_communications_mode() const { return communications_mode_; }
	std::optional<uint32_t> get_power_level() const { return power_level_; }
	std::optional<char> get_sentence_status() const { return sentence_status_; }

	void set_tx_frequency(uint32_t t) noexcept { tx_frequency_ = t; }
	void set_rx_frequency(uint32_t t) noexcept { rx_frequency_ = t; }
	void set_communications_mode(char t) noexcept { communications_mode_ = t; }
	void set_power_level(uint32_t t);
	void set_sentence_status(char t);
};
}
}

#endif
