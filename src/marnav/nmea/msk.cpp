#include "msk.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * msk::TAG;

msk::msk()
	: sentence(ID, TAG, talker_id::global_positioning_system)
	, frequency(0)
	, frequency_mode(selection_mode::automatic)
	, bitrate(0)
	, bitrate_mode(selection_mode::automatic)
{
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

std::unique_ptr<sentence> msk::parse(
	const std::string & talker, const std::vector<std::string> & fields)
{
	if (fields.size() != 5)
		throw std::invalid_argument{"invalid number of fields in msk::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<msk>();
	result->set_talker(talker);
	msk & detail = static_cast<msk &>(*result);

	read(fields[0], detail.frequency);
	read(fields[1], detail.frequency_mode);
	read(fields[2], detail.bitrate);
	read(fields[3], detail.bitrate_mode);
	read(fields[4], detail.frequency_mss_status);

	return result;
}

std::vector<std::string> msk::get_data() const
{
	return {format(frequency, 3), to_string(frequency_mode), format(bitrate, 3),
		to_string(bitrate_mode), format(frequency_mss_status, 3)};
}
}
}
