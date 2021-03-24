// This demo shows how to read NMEA sentences and interpret AIS messages.
// It does not read directly from a specific device, it provides data
// as a demonstration.

#include <marnav/nmea/nmea.hpp>
#include <marnav/nmea/ais_helper.hpp>
#include <marnav/ais/ais.hpp>
#include <marnav/ais/message_01.hpp>
#include <marnav/ais/message_05.hpp>
#include <marnav/io/device.hpp>
#include <marnav/io/default_nmea_reader.hpp>
#include <marnav/utils/unique.hpp>
#include <iostream>

namespace marnav_example
{

// Demo data.
static const char DATA[]
	= {"!AIVDM,1,1,,B,177KQJ5000G?tO`K>RA1wUbN0TKH,0*5C\r\n"
	   "$GPRMC,201034,A,4702.4040,N,00818.3281,E,0.0,328.4,260807,0.6,E,A*17\r\n"
	   "!AIVDM,2,1,3,B,55P5TL01VIaAL@7WKO@mBplU@<PDhh000000001S;AJ::4A80?4i@E53,0*3E\r\n"
	   "$GPRMC,201034,A,4702.4040,N,00818.3281,E,0.0,328.4,260807,0.6,E,A*17\r\n"
	   "!AIVDM,2,2,3,B,1@0000000000000,2*55\r\n"};

// Dummy device to read from 'DATA'.
class dummy_device : public marnav::io::device
{
public:
	dummy_device()
		: index(0)
	{
	}

	void open() override {}
	void close() override {}

	/// Just go through the data once.
	virtual int read(char * buffer, uint32_t size) override
	{
		if (size != sizeof(*buffer))
			throw std::invalid_argument{"buffer type not supported"};
		if (index >= sizeof(DATA))
			return 0; // end of data
		*buffer = static_cast<char>(DATA[index]);
		++index;
		return 1;
	}

	virtual int write(const char *, uint32_t) override
	{
		throw std::runtime_error{"operation not supported"};
	}

private:
	unsigned int index;
};

// NMEA sentence reader which uses the dummy device.
class sentence_reader : public marnav::io::default_nmea_reader
{
public:
	sentence_reader()
		: default_nmea_reader(marnav::utils::make_unique<dummy_device>())
	{
	}
};

// This function finally processes the AIS data... for this demo it does not
// do very much with the data, just showing how to decode NMEA sentences
// into an AIS message.
void process_ais_message(const std::vector<std::unique_ptr<marnav::nmea::sentence>> & sentences)
{
	using namespace marnav;
	using namespace std;

	// create AIS message
	auto payload = nmea::collect_payload(sentences.begin(), sentences.end());
	auto ais_message = ais::make_message(payload);

	// process the message. for this demo, we only do some of them.
	switch (ais_message->type()) {
		case ais::message_id::position_report_class_a:
			std::cout << "AIS: Position report\n";
			break;
		case ais::message_id::static_and_voyage_related_data:
			std::cout << "AIS: Static and voyage related data\n";
			break;
		default:
			// ignore all others
			break;
	}
}
}

int main(int, char **)
{
	using namespace marnav;

	// instance of dummy reader, sufficient for this demo
	marnav_example::sentence_reader reader;

	// sentence collection
	std::vector<std::unique_ptr<nmea::sentence>> sentences;
	std::string raw_sentence;

	// read NMEA sentences
	while (reader.read_sentence(raw_sentence)) {
		auto nmea_sentence = nmea::make_sentence(raw_sentence);

		// we process only VDM messages in this demo
		if (nmea_sentence->id() == nmea::sentence_id::VDM) {

			// since AIS messages may be splitted up in several VDM sentences,
			// we have to collect them. this is a very simple implementation
			// and does not check for sequence or overlapping of messages.
			// it simply assumes all necessary messages are subsequent.
			// there is simply a check, whether or not all parts have arrived.
			const auto vdm = nmea::sentence_cast<nmea::vdm>(nmea_sentence.get());
			const auto n_fragments = vdm->get_n_fragments();
			const auto fragment = vdm->get_fragment();

			// collect sentence
			sentences.push_back(std::move(nmea_sentence));

			// check if all necessary sentences have arrived and if they have,
			// process the AIS message.
			if (fragment == n_fragments) {
				marnav_example::process_ais_message(sentences);
				sentences.clear();
			}
		} else {
			std::cout << nmea_sentence->tag() << ": ignored\n";
		}
	}
}
