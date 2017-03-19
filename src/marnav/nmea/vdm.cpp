#include "vdm.hpp"
#include <string>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * vdm::TAG;

vdm::vdm()
	: sentence(ID, TAG, talker_id::ais_mobile_station)
{
}

vdm::vdm(sentence_id id, const std::string & tag, talker talk)
	: sentence(id, tag, talk)
{
}

vdm::vdm(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
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

void vdm::append_data_to(std::string & s) const
{
	append(s, to_string(n_fragments));
	append(s, to_string(fragment));
	append(s, to_string(seq_msg_id));
	append(s, to_string(radio_channel));
	append(s, to_string(payload));
	append(s, to_string(n_fill_bits));
}
}
}
