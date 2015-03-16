#include "vdm.hpp"
#include "unique.hpp"
#include "io.hpp"
#include <string>

namespace nmea
{

vdm::vdm()
	: sentence(ID, "VDM", talker_id::ais_mobile_station)
	, n_fragments(0)
	, fragment(0)
	, radio_channel(ais_channel::B)
	, n_fill_bits(0)
{
}

std::unique_ptr<sentence>
vdm::parse(const std::string& talker,
		   const std::vector<std::string>& fields) throw(std::invalid_argument)
{
	if (fields.size() != 6)
		throw std::invalid_argument{"invalid number of fields in vdm::parse"};

	std::unique_ptr<sentence> result = std::make_unique<vdm>();
	result->set_talker(talker);
	vdm& detail = static_cast<vdm&>(*result);

	read(fields[0], detail.n_fragments);
	read(fields[1], detail.fragment);
	read(fields[2], detail.seq_msg_id);
	read(fields[3], detail.radio_channel);
	read(fields[4], detail.payload);
	read(fields[5], detail.n_fill_bits);

	return result;
}

std::vector<std::string> vdm::get_data() const
{
	return {to_string(n_fragments),   to_string(fragment), to_string(seq_msg_id),
			to_string(radio_channel), to_string(payload),  to_string(n_fill_bits)};
}

}
