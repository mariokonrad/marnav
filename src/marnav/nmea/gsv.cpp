#include <marnav/nmea/gsv.hpp>
#include <marnav/nmea/io.hpp>
#include <algorithm>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
namespace
{
inline std::string to_string(const std::optional<gsv::satellite_info> & data)
{
	if (!data)
		return std::string{",,,"};
	auto const & value = data.value();
	return format(value.prn, 2) + "," + format(value.elevation, 2) + ","
		+ format(value.azimuth, 3) + "," + format(value.snr, 2);
}
}

constexpr sentence_id gsv::ID;
constexpr const char * gsv::TAG;

gsv::gsv()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

gsv::gsv(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	// empty fields for satellite information are not necessary, therefore
	// there are a variable number of fields. however, the first 3 are
	// mandatory and the rest must be a multiple of 4 (the four parts
	// of satellite information).
	const auto size = std::distance(first, last);
	if ((size < 3) || ((size - 3) % 4 != 0)) {
		throw std::invalid_argument{
			std::string{"invalid number of fields in gsv: expected 3+n*4, got "}
			+ std::to_string(size)};
	}

	read(*(first + 0), n_messages_);
	read(*(first + 1), message_number_);
	read(*(first + 2), n_satellites_in_view_);

	const int num_satellite_info = std::min(4, static_cast<int>((size - 3) / 4));
	int index = 3;
	for (int i = 0; i < num_satellite_info; ++i, index += 4) {
		satellite_info info;

		// test PRN field whether it is empty or not,
		// the satellite info is invalid/non-present if ther is no PRN
		//
		// this might not be the desired solution, looks clunky.
		// maybe the `nmea::read()` functions should be refactored.
		//
		std::optional<decltype(info.prn)> prn;
		read(*(first + index + 0), prn);
		if (!prn)
			continue;
		info.prn = *prn;

		read(*(first + index + 1), info.elevation);
		read(*(first + index + 2), info.azimuth);
		read(*(first + index + 3), info.snr);
		set_sat(i, info);
	}
}

void gsv::set_n_messages(uint32_t t)
{
	if (t < 1)
		throw std::invalid_argument{"minimum of 1 for n_messages mandatory"};
	n_messages_ = t;
}

void gsv::set_message_number(uint32_t t)
{
	if (t < 1)
		throw std::invalid_argument{"minimum of 1 for message_number mandatory"};
	message_number_ = t;
}

void gsv::check_index(int index) const
{
	if ((index < 0) || (index > 3)) {
		throw std::out_of_range{"satellite index out of range"};
	}
}

void gsv::set_sat(int index, const satellite_info & info)
{
	check_index(index);
	sat_[index] = info;
}

std::optional<gsv::satellite_info> gsv::get_sat(int index) const
{
	check_index(index);
	return sat_[index];
}

void gsv::append_data_to(std::string & s) const
{
	append(s, to_string(n_messages_));
	append(s, to_string(message_number_));
	append(s, to_string(n_satellites_in_view_));
	append(s, to_string(sat_[0]));
	append(s, to_string(sat_[1]));
	append(s, to_string(sat_[2]));
	append(s, to_string(sat_[3]));
}
}
}
