#include "msk.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr sentence_id msk::ID;
constexpr const char * msk::TAG;

msk::msk()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

msk::msk(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 5)
		throw std::invalid_argument{"invalid number of fields in msk"};

	read(*(first + 0), frequency_);
	read(*(first + 1), frequency_mode_);
	read(*(first + 2), bitrate_);
	read(*(first + 3), bitrate_mode_);
	read(*(first + 4), frequency_mss_status_);
}

void msk::set_frequency(uint32_t f, selection_mode mode) noexcept
{
	frequency_ = f;
	frequency_mode_ = mode;
}

void msk::set_bitrate(uint32_t rate, selection_mode mode) noexcept
{
	bitrate_ = rate;
	bitrate_mode_ = mode;
}

void msk::append_data_to(std::string & s) const
{
	append(s, format(frequency_, 3));
	append(s, to_string(frequency_mode_));
	append(s, format(bitrate_, 3));
	append(s, to_string(bitrate_mode_));
	append(s, format(frequency_mss_status_, 3));
}
}
}
