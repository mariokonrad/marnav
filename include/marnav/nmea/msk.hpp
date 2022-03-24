#ifndef MARNAV_NMEA_MSK_HPP
#define MARNAV_NMEA_MSK_HPP

#include <marnav/nmea/sentence.hpp>
#include <optional>

namespace marnav
{
namespace nmea
{
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
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::MSK;
	constexpr static const char * TAG = "MSK";

	msk();
	msk(const msk &) = default;
	msk & operator=(const msk &) = default;
	msk(msk &&) = default;
	msk & operator=(msk &&) = default;

protected:
	msk(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	uint32_t frequency_ = 0;
	selection_mode frequency_mode_ = selection_mode::automatic;
	uint32_t bitrate_ = 0;
	selection_mode bitrate_mode_ = selection_mode::automatic;
	std::optional<uint32_t> frequency_mss_status_;

public:
	uint32_t get_frequency() const { return frequency_; }
	selection_mode get_frequency_mode() const { return frequency_mode_; }
	uint32_t get_bitrate() const { return bitrate_; }
	selection_mode get_bitrate_mode() const { return bitrate_mode_; }
	std::optional<uint32_t> get_frequency_mss_status() const { return frequency_mss_status_; }

	void set_frequency(uint32_t f, selection_mode mode) noexcept;
	void set_bitrate(uint32_t rate, selection_mode mode) noexcept;
	void set_frequency_mss_status(uint32_t t) noexcept { frequency_mss_status_ = t; }
};
}
}

#endif
