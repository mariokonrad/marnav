#include <fstream>
#include <string>
#include <iostream>
#include <marnav/nmea/nmea.hpp>
#include <marnav/nmea/ais_helper.hpp>
#include <marnav/ais/ais.hpp>

namespace stackoverflow
{
// source:
// http://stackoverflow.com/questions/6089231/getting-std-ifstream-to-handle-lf-cr-and-crlf
//
// changes:
// - old-style C type cast changed to c++ cast
// - reformatting
// - renaming and put into the namespace
// - break inserted for the default option of switch
std::istream & getline(std::istream & is, std::string & t)
{
	t.clear();

	// The characters in the stream are read one-by-one using a std::streambuf.
	// That is faster than reading them one-by-one using the std::istream.
	// Code that uses streambuf this way must be guarded by a sentry object.
	// The sentry object performs various tasks,
	// such as thread synchronization and updating the stream state.

	std::istream::sentry se(is, true);
	std::streambuf * sb = is.rdbuf();

	for (;;) {
		int c = sb->sbumpc();
		switch (c) {
			case '\n':
				return is;
			case '\r':
				if (sb->sgetc() == '\n')
					sb->sbumpc();
				return is;
			case EOF:
				// Also handle the case when the last line has no line ending
				if (t.empty())
					is.setstate(std::ios::eofbit);
				return is;
			default:
				t += static_cast<char>(c);
				break;
		}
	}
}
}

namespace marnav_test
{
void process_ais_message(const std::vector<std::unique_ptr<marnav::nmea::sentence>> & sentences)
{
	using namespace marnav;
	using namespace std;

	// create AIS message
	std::unique_ptr<ais::message> message;
	try {
		message = ais::make_message(nmea::collect_payload(sentences.begin(), sentences.end()));
	} catch (ais::unknown_message & e) {
		std::cout << "AIS unknown: " << e.what() << "\n";
		return;
	} catch (std::invalid_argument & e) {
		std::cout << "AIS error: " << e.what() << "\n";
		return;
	}

	// process the message. for this test, we only do some of them.
	switch (message->type()) {
		case ais::message_id::position_report_class_a:
			std::cout << "AIS: Position report class A\n";
			break;
		case ais::message_id::position_report_class_a_assigned_schedule:
			std::cout << "AIS: Position report class A (assigned schedule)\n";
			break;
		case ais::message_id::position_report_class_a_response_to_interrogation:
			std::cout << "AIS: Position report class A (response to interrogation)\n";
			break;
		case ais::message_id::base_station_report:
			std::cout << "AIS: Base Station Report\n";
			break;
		case ais::message_id::static_and_voyage_related_data:
			std::cout << "AIS: Static and voyage related data\n";
			break;
		case ais::message_id::standard_sar_aircraft_position_report:
			std::cout << "AIS: Standard SAR Aircraft Position Report\n";
			break;
		case ais::message_id::utc_and_date_inquiry:
			std::cout << "AIS: UTC/Date Inquiry\n";
			break;
		case ais::message_id::utc_and_date_response:
			std::cout << "AIS: UTC/Date Response\n";
			break;
		case ais::message_id::standard_class_b_cs_position_report:
			std::cout << "AIS: Standard class B CS position report\n";
			break;
		case ais::message_id::extended_class_b_equipment_position_report:
			std::cout << "AIS: Extended class B equipment position report\n";
			break;
		case ais::message_id::aid_to_navigation_report:
			std::cout << "AIS: Aid-to-Navigation report\n";
			break;
		case ais::message_id::static_data_report:
			std::cout << "AIS: Static Data Report\n";
			break;
		default:
			// ignore all others
			std::cout << "AIS: ignored, message type: " << static_cast<int>(message->type())
					  << "\n";
			break;
	}
}
}

int main(int, char **)
{
	using namespace marnav;

	std::ifstream ifs{"ais-sample.txt"};
	std::string line;
	std::vector<std::unique_ptr<nmea::sentence>> sentences;

	// this function implements almost the same as examples/read_ais.cpp

	while (stackoverflow::getline(ifs, line)) {
		try {
			auto sentence = nmea::make_sentence(line);
			if (sentence->id() == nmea::sentence_id::VDM) {
				const auto vdm = nmea::sentence_cast<nmea::vdm>(sentence.get());
				const auto n_fragments = vdm->get_n_fragments();
				const auto fragment = vdm->get_fragment();
				sentences.push_back(std::move(sentence));
				if (fragment == n_fragments) {
					marnav_test::process_ais_message(sentences);
					sentences.clear();
				}
			} else {
				std::cout << "NMEA/AIS ignored: " << line << "\n";
			}
		} catch (nmea::unknown_sentence & e) {
			std::cout << "NMEA unknown: " << e.what() << "\n";
		} catch (std::runtime_error & e) {
			std::cout << "NMEA/AIS runtime_error: " << e.what() << " for sentence: [" << line
					  << "]\n";
		} catch (std::out_of_range & e) {
			std::cout << "NMEA/AIS out_of_range: " << e.what() << " for sentence: [" << line
					  << "]\n";
		} catch (std::exception & e) {
			std::cout << "NMEA/AIS error: " << e.what() << " for sentence: [" << line << "]\n";
		}
	}

	return 0;
}
