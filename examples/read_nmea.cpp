#include <marnav/io/nmea_serial.hpp>
#include <marnav/nmea/nmea.hpp>
#include <marnav/nmea/rmc.hpp>
#include <marnav/nmea/io.hpp>
#include <iostream>

using namespace marnav;

/// Works only in a single threaded context (true for serial and nmea_serial).
///
/// This class is implemented inline, for easier handling within this example.
class sentence_reader : public io::nmea_serial
{
public:
	sentence_reader(const std::string & device_name)
		: nmea_serial(device_name)
		, sentence_received(false)
	{
	}

	/// Reads synchronously messages from the device.
	///
	/// @param[out] s The received sentence.
	/// @retval true  Success.
	/// @retval false End of file.
	/// @exception std::runtime_error
	bool read_sentence(std::string & s)
	{
		// reads as long as the sentence is not complete.
		while (read()) {

			// the sentence was received, return it and reset the 'semaphore'.
			// please note: this works only in single threaded environment,
			// since the 'semaphore' isn't really one.
			if (sentence_received) {
				s = sentence;
				sentence_received = false;
				return true;
			}
		}
		return false;
	}

protected:
	/// Processes the received sentence. Uses the data member 'sentence_received'
	/// as poor-mans semaphore to signal the receipt.
	///
	/// After the reception, the message will be stored temporarily.
	virtual void process_sentence(const std::string & s) override
	{
		sentence = s;
		sentence_received = true;
	}

private:
	bool sentence_received;
	std::string sentence;
};

int main(int, char **)
{
	// create and open the device for reading.
	sentence_reader reader{"/dev/ttyUSB0"};

	std::string data;

	// read and process NMEA sentences, bus synchronization is done automatically.
	while (reader.read_sentence(data)) {
		// data was successfully read from the NMEA bus, inclusive synchronization
		// of NMEA sentences. This means it is possible to begin to listen on the
		// bus at any time.
		auto sentence = nmea::make_sentence(data);

		// do something with the sentence, for example dump the position
		if (sentence->id() == nmea::sentence_id::RMC) {
			auto rmc = nmea::sentence_cast<nmea::rmc>(sentence);
			std::cout << "latitude : " << nmea::to_string(rmc->get_lat()) << "\n";
			std::cout << "longitude: " << nmea::to_string(rmc->get_lon()) << "\n";
		}
	}
}
