#include <io/seatalk_serial.hpp>
#include <seatalk/seatalk.hpp>
#include <seatalk/message_00.hpp>
#include <iostream>

using namespace marnav;

/// Works only in a single threaded context (true for serial and seatalk_serial).
///
/// This class is implemented inline, for easier handling within this example.
class message_reader : public io::seatalk_serial
{
public:
	message_reader(const std::string & device_name)
		: seatalk_serial(device_name)
		, message_received(false)
	{
	}

	/// Reads synchronously messages from the device.
	///
	/// @return The received message.
	/// @exception std::runtime_error
	seatalk::raw read_message()
	{
		// reads as long as the message is not complete.
		while (true) {

			// the message was received, return it and reset the 'semaphore'.
			// please note: this works only in single threaded environment,
			// since the 'semaphore' isn't really one.
			if (message_received) {
				message_received = false;
				return message;
			}

			// read data from the device. if this fails, there is not much
			// else to do, than to give up.
			read();
		}
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
	// create and open the device for reading.
	message_reader reader{"/dev/ttyUSB0"};

	// read and process SeaTalk messages forever, this is ok for this demo.
	while (true) {
		// read data from the SeaTalk bus and return it. bus synchronization is done
		// automatically.
		auto data = reader.read_message();

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
