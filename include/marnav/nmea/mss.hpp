#ifndef MARNAV_NMEA_MSS_HPP
#define MARNAV_NMEA_MSS_HPP

#include <marnav/nmea/sentence.hpp>
#include <optional>

namespace marnav
{
namespace nmea
{
/// @brief MSS - Beacon Receiver Status
///
/// @code
///        1  2  3  4    5
///        |  |  |  |    |
/// $--MSS,nn,nn,fff,bbb,xxx*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Signal strength (dB 1uV)
/// 2. Signal to noise ratio (dB)
/// 3. Beacon frequency (kHz)
/// 4. Beacon data rate (BPS)
/// 5. Unknown integer value
///
class mss : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::MSS;
	constexpr static const char * TAG = "MSS";

	mss();
	mss(const mss &) = default;
	mss & operator=(const mss &) = default;
	mss(mss &&) = default;
	mss & operator=(mss &&) = default;

protected:
	mss(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	uint32_t signal_strength_ = 0;
	uint32_t signal_to_noise_ratio_ = 0;
	uint32_t beacon_frequency_ = 0;
	uint32_t beacon_datarate_ = 0;
	int32_t unknown_ = 0;

public:
	uint32_t get_signal_strength() const { return signal_strength_; }
	uint32_t get_signal_to_noise_ratio() const { return signal_to_noise_ratio_; }
	uint32_t get_beacon_frequency() const { return beacon_frequency_; }
	uint32_t get_beacon_datarate() const { return beacon_datarate_; }
	int32_t get_unknown() const { return unknown_; }

	void set_signal_strength(uint32_t t) noexcept { signal_strength_ = t; }
	void set_signal_to_noise_ratio(uint32_t t) noexcept { signal_to_noise_ratio_ = t; }
	void set_beacon_frequency(uint32_t t) noexcept { beacon_frequency_ = t; }
	void set_beacon_datarate(uint32_t t) noexcept { beacon_datarate_ = t; }
	void set_unknown(int32_t t) noexcept { unknown_ = t; }
};
}
}

#endif
