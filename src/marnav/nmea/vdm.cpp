#include <marnav/nmea/vdm.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>
#include <stdexcept>
#include <string>

namespace marnav
{
namespace nmea
{
constexpr sentence_id vdm::ID;
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
	read(*(first + 0), n_fragments_);
	read(*(first + 1), fragment_);
	read(*(first + 2), seq_msg_id_);
	read(*(first + 3), radio_channel_);
	read(*(first + 4), payload_);
	read(*(first + 5), n_fill_bits_);
}

void vdm::append_data_to(std::string & s) const
{
	append(s, to_string(n_fragments_));
	append(s, to_string(fragment_));
	append(s, to_string(seq_msg_id_));
	append(s, to_string(radio_channel_));
	append(s, to_string(payload_));
	append(s, to_string(n_fill_bits_));
}
}
}
