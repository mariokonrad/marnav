#include <marnav/seatalk/seatalk.hpp>
#include <marnav/seatalk/message_00.hpp>

namespace marnav_example
{
void seatalk_encode_message()
{
	//! [Getting raw data from message]
	marnav::seatalk::message_00 msg;
	msg.set_depth(10);

	marnav::seatalk::raw data = marnav::seatalk::encode_message(msg);
	//! [Getting raw data from message]
}
}

int main(int, char **)
{
	marnav_example::seatalk_encode_message();
	return 0;
}
