#ifndef MARNAV_NMEA_GSV_HPP
#define MARNAV_NMEA_GSV_HPP

#include <marnav/nmea/sentence.hpp>
#include <array>
#include <optional>

namespace marnav
{
namespace nmea
{
/// @brief GSV - Satellites in view
///
/// These sentences describe the sky position of a UPS satellite in view. Typically they’re
/// shipped in a group of 2 or 3.
///
/// @code
///        1 2 3 4 5 6 7     8
///        | | | | | | |     |
/// $--GSV,x,x,x,x,x,x,x,...*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Total number of GSV messages to be transmitted in this group
/// 2. 1-origin number of this GSV message within current group
/// 3. Total number of satellites in view (leading zeros sent)
/// 4. Satellite PRN (pseudo random noise) number (leading zeros sent)
/// 5. Elevation in degrees (00-90) (leading zeros sent)
/// 6. Azimuth in degrees to true north (000-359) (leading zeros sent)
/// 7. SNR (signal to noise ratio) in dB (00-99) (leading zeros sent),
///    apparently this may be not defined.
/// 8. checksum
///
/// after 7: more satellite info quadruples like 4-7
///
/// Example:
/// @code
/// $GPGSV,3,1,11,03,03,111,00,04,15,270,00,06,01,010,00,13,06,292,00*74
/// $GPGSV,3,2,11,14,25,170,00,16,57,208,39,18,67,296,40,19,40,246,00*74
/// $GPGSV,3,3,11,22,42,067,42,24,14,311,43,27,05,244,00,,,,*4D
/// @endcode
///
/// @note Although null fields for unused satellite info are not required,
///       this class will write them in any case.
class gsv : public sentence
{
	friend class detail::factory;

public:
	struct satellite_info {
		uint32_t prn;
		uint32_t elevation;
		uint32_t azimuth; // azimuth against true
		std::optional<uint32_t> snr;
	};

	constexpr static sentence_id ID = sentence_id::GSV;
	constexpr static const char * TAG = "GSV";

	gsv();
	gsv(const gsv &) = default;
	gsv & operator=(const gsv &) = default;
	gsv(gsv &&) = default;
	gsv & operator=(gsv &&) = default;

protected:
	gsv(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	uint32_t n_messages_ = 1;
	uint32_t message_number_ = 1;
	uint32_t n_satellites_in_view_ = 0;
	std::array<std::optional<satellite_info>, 4> sat_;

	void check_index(int index) const;

public:
	uint32_t get_n_messages() const { return n_messages_; }
	uint32_t get_message_number() const { return message_number_; }
	uint32_t get_n_satellites_in_view() const { return n_satellites_in_view_; }
	std::optional<satellite_info> get_sat(int index) const;

	void set_n_messages(uint32_t t);
	void set_message_number(uint32_t t);
	void set_n_satellites_in_view(uint32_t t) noexcept { n_satellites_in_view_ = t; }
	void set_sat(int index, const satellite_info & info);
};
}
}

#endif
