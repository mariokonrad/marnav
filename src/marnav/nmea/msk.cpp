#include "msk.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(msk)

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

	read(*(first + 0), frequency);
	read(*(first + 1), frequency_mode);
	read(*(first + 2), bitrate);
	read(*(first + 3), bitrate_mode);
	read(*(first + 4), frequency_mss_status);
}

void msk::set_frequency(uint32_t f, selection_mode mode) noexcept
{
	frequency = f;
	frequency_mode = mode;
}

void msk::set_bitrate(uint32_t rate, selection_mode mode) noexcept
{
	bitrate = rate;
	bitrate_mode = mode;
}

std::vector<std::string> msk::get_data() const
{
	return {format(frequency, 3), to_string(frequency_mode), format(bitrate, 3),
		to_string(bitrate_mode), format(frequency_mss_status, 3)};
}
}
}
