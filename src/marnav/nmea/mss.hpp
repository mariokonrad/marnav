#ifndef __NMEA__MSS__HPP__
#define __NMEA__MSS__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

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
public:
	constexpr static const sentence_id ID = sentence_id::MSS;
	constexpr static const char * TAG = "MSS";

	mss();
	mss(const mss &) = default;
	mss & operator=(const mss &) = default;

	static std::unique_ptr<sentence> parse(
		const std::string & talker, const std::vector<std::string> & fields);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	uint32_t signal_strength;
	uint32_t signal_to_noise_ratio;
	uint32_t beacon_frequency;
	uint32_t beacon_datarate;
	int32_t unknown;

public:
	NMEA_GETTER(signal_strength)
	NMEA_GETTER(signal_to_noise_ratio)
	NMEA_GETTER(beacon_frequency)
	NMEA_GETTER(beacon_datarate)
	NMEA_GETTER(unknown)

	void set_signal_strength(uint32_t t) noexcept { signal_strength = t; }
	void set_signal_to_noise_ratio(uint32_t t) noexcept { signal_to_noise_ratio = t; }
	void set_beacon_frequency(uint32_t t) noexcept { beacon_frequency = t; }
	void set_beacon_datarate(uint32_t t) noexcept { beacon_datarate = t; }
	void set_unknown(int32_t t) noexcept { unknown = t; }
};
}
}

#endif
