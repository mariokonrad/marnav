#include <marnav/nmea/nmea.hpp>
#include <marnav/nmea/dpt.hpp>
#include <marnav/seatalk/seatalk.hpp>
#include <marnav/seatalk/message_00.hpp>
#include <marnav-io/default_seatalk_reader.hpp>
#include <marnav-io/default_seatalk_serial.hpp>
#include <boost/asio.hpp>
#include <map>

using namespace marnav;

namespace marnav_example
{
static std::string conv_depth_below_transducer(const seatalk::message & msg)
{
	using namespace marnav::seatalk;

	const auto & m = message_cast<message_00>(msg);

	nmea::dpt dpt;
	// TODO: explicit type unnecessary once seatalk is also using units
	dpt.set_depth_meter(units::meters{m.get_depth_meters()});
	dpt.set_transducer_offset(units::meters{0.0});
	return nmea::to_string(dpt);
}
}

int main(int, char **)
{
	using namespace marnav_example;
	using namespace marnav::io;

	// mapping of conversion functions
	static const std::map<seatalk::message_id,
		std::function<std::string(const seatalk::message &)>>
		CONV = {
			{seatalk::message_id::depth_below_transducer, conv_depth_below_transducer},
		};

	// open output port
	boost::asio::io_service io;
	boost::asio::serial_port serial{io, "/dev/ttyUSB1"};
	serial.set_option(boost::asio::serial_port_base::baud_rate(4800));

	// open input port and reader
	default_seatalk_reader reader{make_default_seatalk_serial("/dev/ttyUSB0")};
	seatalk::raw data;

	while (reader.read_message(data)) {
		// receive message
		auto msg = seatalk::make_message(data);
		if (!msg)
			continue;

		// convert message to NMEA sentence, if known
		std::string nmea;
		auto func = CONV.find(msg->type());
		if (func != CONV.end())
			nmea = func->second(*msg);

		// send NMEA sentence
		if (nmea.size() > 0) {
			nmea += "\r\n";
			boost::asio::write(serial, boost::asio::buffer(nmea.c_str(), nmea.size()));
		}
	}

	return 0;
}
