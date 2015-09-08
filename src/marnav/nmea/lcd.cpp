#include "lcd.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * lcd::TAG;

lcd::lcd()
	: sentence(ID, TAG, talker_id::global_positioning_system)
	, gri(0)
	, master({0, 0})
{
}

void lcd::check_index(int index) const
{
	if ((index < 0) || (index >= NUM_DIFFERENCES)) {
		throw std::out_of_range{"time difference index out of range"};
	}
}

utils::optional<lcd::time_difference> lcd::get_time_diff(int index) const
{
	check_index(index);
	return time_diffs[index];
}

void lcd::set_time_diff(int index, time_difference t)
{
	check_index(index);
	time_diffs[index] = t;
}

std::unique_ptr<sentence> lcd::parse(
	const std::string & talker, const std::vector<std::string> & fields)
{
	if (fields.size() != 13)
		throw std::invalid_argument{"invalid number of fields in lcd::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<lcd>();
	result->set_talker(talker);
	lcd & detail = static_cast<lcd &>(*result);

	read(fields[0], detail.gri);
	read(fields[1], detail.master.snr);
	read(fields[2], detail.master.ecd);
	for (int i = 0; i < NUM_DIFFERENCES; ++i) {
		utils::optional<decltype(time_difference::snr)> snr;
		utils::optional<decltype(time_difference::ecd)> ecd;
		read(fields[(i * 2) + 3], snr);
		read(fields[(i * 2) + 3 + 1], ecd);
		if (snr && ecd) {
			detail.time_diffs[i] = utils::make_optional<time_difference>(*snr, *ecd);
		}
	}

	return result;
}

std::vector<std::string> lcd::get_data() const
{
	std::vector<std::string> result;
	result.reserve(13);
	result.push_back(to_string(gri));
	result.push_back(format(master.snr, 3));
	result.push_back(format(master.ecd, 3));
	for (int i = 0; i < NUM_DIFFERENCES; ++i) {
		auto const & t = time_diffs[i];
		if (t) {
			result.push_back(format(t->snr, 3));
			result.push_back(format(t->ecd, 3));
		} else {
			result.push_back("");
			result.push_back("");
		}
	}
	return result;
}
}
}
