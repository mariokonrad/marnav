#ifndef __NMEA__MSK__HPP__
#define __NMEA__MSK__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(msk)

/// @brief MSK - Control for a Beacon Receiver
///
/// @code
///        1  2  3  4  5
///        |  |  |  |  |
/// $--MSK,nnn,m,nnn,m,nnn*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Frequency to use
/// 2. Frequency mode
///    - A = auto
///    - M = manual
/// 3. Beacon bit rate
/// 4. Bitrate
///    - A = auto
///    - M = manual
/// 5. Frequency for MSS message status (null for no status)
///
class msk : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(msk)

public:
	constexpr static const sentence_id ID = sentence_id::MSK;
	constexpr static const char * TAG = "MSK";

	msk();
	msk(const msk &) = default;
	msk & operator=(const msk &) = default;

protected:
	msk(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	uint32_t frequency = 0;
	selection_mode frequency_mode = selection_mode::automatic;
	uint32_t bitrate = 0;
	selection_mode bitrate_mode = selection_mode::automatic;
	utils::optional<uint32_t> frequency_mss_status;

public:
	NMEA_GETTER(frequency)
	NMEA_GETTER(frequency_mode)
	NMEA_GETTER(bitrate)
	NMEA_GETTER(bitrate_mode)
	NMEA_GETTER(frequency_mss_status)

	void set_frequency(uint32_t f, selection_mode mode) noexcept;
	void set_bitrate(uint32_t rate, selection_mode mode) noexcept;
	void set_frequency_mss_status(uint32_t t) noexcept { frequency_mss_status = t; }
};
}
}

#endif
