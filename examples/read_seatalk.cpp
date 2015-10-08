#include <iostream>
#include <marnav/io/seatalk_reader.hpp>
#include <marnav/io/default_seatalk_serial.hpp>
#include <marnav/seatalk/seatalk.hpp>
#include <marnav/seatalk/message_00.hpp>

using namespace marnav;

/// Works only in a single threaded context (true for serial and seatalk_reader).
///
/// This class is implemented inline, for easier handling within this example.
class message_reader : public io::seatalk_reader
{
public:
	message_reader(std::unique_ptr<io::device> && dev)
		: seatalk_reader(std::move(dev))
		, message_received(false)
	{
	}

	/// Reads synchronously messages from the device.
	///
	/// @param[out] data The received message.
	/// @retval true  Success.
	/// @retval false End of file.
	/// @exception std::runtime_error
	bool read_message(seatalk::raw & data)
	{
		// reads as long as the message is not complete.
		while (read()) {
			// the message was received, return it and reset the 'semaphore'.
			// please note: this works only in single threaded environment,
			// since the 'semaphore' isn't really one.
			if (message_received) {
				data = message;
				message_received = false;
				return true;
			}
		}
		return false;
	}

protected:
	/// Processes the received message. Uses the data member 'message_received'
	/// as poor-mans semaphore to signal the receipt.
	///
	/// After the reception, the message will be stored temporarily.
	virtual void process_message(const seatalk::raw & msg) override
	{
		message = msg;
		message_received = true;
	}

private:
	bool message_received;
	seatalk::raw message;
};

int main(int, char **)
{
	using namespace marnav::io;

	// create and open the device for reading.
	message_reader reader{make_default_seatalk_serial("/dev/ttyUSB0")};

	seatalk::raw data;

	// read and process SeaTalk messages, bus synchronization is done automatically.
	while (reader.read_message(data)) {
		// data was successfully read from the SeaTalk bus, inclusive synchronization
		// of SeaTalk messages. This means it is possible to begin to listen on the
		// bus at any time.
		auto msg = seatalk::make_message(data);

		// do something with the message, for example dump the depth and ignore all
		// other messages.
		if (msg->type() == seatalk::message_id::depth_below_transducer) {
			auto depth = seatalk::message_cast<seatalk::message_00>(msg);
			std::cout << "depth below transducer: " << depth->get_depth() << "\n";
		}
	}
}
