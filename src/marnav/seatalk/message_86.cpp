#include <marnav/seatalk/message_86.hpp>
#include <stdexcept>

namespace marnav
{
namespace seatalk
{
message_86::message_86()
	: message(ID)
	, org_(origin::st1000)
	, k_(key::key_standby)
{
}

std::unique_ptr<message> message_86::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = utils::make_unique<message_86>();
	message_86 & msg = static_cast<message_86 &>(*result);

	//  86 X1 YY yy
	// raw  1  2  3

	const uint8_t kn = data[2];
	const uint8_t ki = ~data[3];

	if (kn != ki)
		throw std::invalid_argument{"data error in SeaTalk message 86"};

	msg.org_ = static_cast<message_86::origin>((data[1] >> 4) & 0x0f);
	msg.k_ = static_cast<key>(data[2]);

	return result;
}

raw message_86::get_data() const
{
	const uint8_t vn = static_cast<uint8_t>(k_);
	const uint8_t vi = ~vn;
	const uint8_t o = static_cast<uint8_t>(org_) & 0x0f;
	return raw{static_cast<uint8_t>(ID), static_cast<uint8_t>(0x01 | (o << 4)), vn, vi};
}
}
}
