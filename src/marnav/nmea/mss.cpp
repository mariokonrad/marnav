#include "mss.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * mss::TAG;

mss::mss()
	: sentence(ID, TAG, talker_id::global_positioning_system)
	, signal_strength(0)
	, signal_to_noise_ratio(0)
	, beacon_frequency(0)
	, beacon_datarate(0)
	, unknown(0)
{
}

std::unique_ptr<sentence> mss::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 5)
		throw std::invalid_argument{"invalid number of fields in mss::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<mss>();
	result->set_talker(talker);
	mss & detail = static_cast<mss &>(*result);

	read(*(first + 0), detail.signal_strength);
	read(*(first + 1), detail.signal_to_noise_ratio);
	read(*(first + 2), detail.beacon_frequency);
	read(*(first + 3), detail.beacon_datarate);
	read(*(first + 4), detail.unknown);

	return result;
}

std::vector<std::string> mss::get_data() const
{
	return {format(signal_strength, 2), format(signal_to_noise_ratio, 2),
		format(beacon_frequency, 3), format(beacon_datarate, 3), to_string(unknown)};
}
}
}
