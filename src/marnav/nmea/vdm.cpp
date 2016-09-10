#include "vdm.hpp"
#include <string>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(vdm)

constexpr const char * vdm::TAG;

vdm::vdm()
	: sentence(ID, TAG, talker_id::ais_mobile_station)
{
}

vdm::vdm(sentence_id id, const std::string & tag, const std::string & talker)
	: sentence(id, tag, talker)
{
}

vdm::vdm(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in vdm"};

	read_fields(first);
}

void vdm::read_fields(fields::const_iterator first)
{
	read(*(first + 0), n_fragments);
	read(*(first + 1), fragment);
	read(*(first + 2), seq_msg_id);
	read(*(first + 3), radio_channel);
	read(*(first + 4), payload);
	read(*(first + 5), n_fill_bits);
}

std::vector<std::string> vdm::get_data() const
{
	return {to_string(n_fragments), to_string(fragment), to_string(seq_msg_id),
		to_string(radio_channel), to_string(payload), to_string(n_fill_bits)};
}
}
}
