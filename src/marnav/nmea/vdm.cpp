#include "vdm.hpp"
#include "io.hpp"
#include <marnav/utils/unique.hpp>
#include <string>

namespace marnav
{
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

vdm::vdm(sentence_id id, const std::string & tag, const std::string & talker)
	: sentence(id, tag, talker)
	, n_fragments(0)
	, fragment(0)
	, radio_channel(ais_channel::B)
	, n_fill_bits(0)
{
}

void vdm::read_fields(const std::vector<std::string> & fields)
{
	read(fields[0], n_fragments);
	read(fields[1], fragment);
	read(fields[2], seq_msg_id);
	read(fields[3], radio_channel);
	read(fields[4], payload);
	read(fields[5], n_fill_bits);
}

std::unique_ptr<sentence> vdm::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 6)
		throw std::invalid_argument{"invalid number of fields in vdm::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<vdm>();
	result->set_talker(talker);
	vdm & detail = static_cast<vdm &>(*result);

	detail.read_fields(fields);

	return result;
}

std::vector<std::string> vdm::get_data() const
{
	return {to_string(n_fragments), to_string(fragment), to_string(seq_msg_id),
		to_string(radio_channel), to_string(payload), to_string(n_fill_bits)};
}
}
}
