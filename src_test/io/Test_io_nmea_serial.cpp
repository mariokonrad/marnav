#include <gtest/gtest.h>
#include <io/nmea_serial.hpp>
#include <io/device.hpp>
#include <utils/unique.hpp>

namespace
{
static const char DATA[] =
{
	"$GPRMC,202451,A,4702.3966,N,00818.3287,E,0.0,312.3,260711,0.6,E,A*19\r\n"
	"$GPRMC,202452,A,4702.3966,N,00818.3287,E,0.0,312.3,260711,0.6,E,A*1a\r\n"
	"$GPRMC,202453,A,4702.3966,N,00818.3287,E,0.0,312.3,260711,0.6,E,A*1b\r\n"
};

class dummy_device : public ::io::device
{
public:
	dummy_device()
		: index(0)
	{}

	void open() throw(std::runtime_error) override {}
	void close() override {}

	/// Just go through the data once.
	virtual int read(char* buffer, uint32_t size) throw(std::invalid_argument,
														std::runtime_error) override
	{
		if (size != sizeof(*buffer))
			throw std::invalid_argument{"buffer type not supported"};
		if (index >= sizeof(DATA))
			return 0; // end of data
		*buffer = static_cast<char>(DATA[index]);
		++index;
		return 1;
	}

private:
	uint32_t index;
};

class dummy_reader : public ::io::nmea_serial
{
public:
	dummy_reader()
		: nmea_serial(utils::make_unique<dummy_device>())
		, num_sentences(0)
	{
	}

	int get_num_sentences() const { return num_sentences; }

protected:
	virtual void process_sentence(const std::string&) override
	{
		++num_sentences;
	}

private:
	int num_sentences;
};

/// Works only in a single threaded context (true for dummuy_device and nmea_serial).
class message_reader : public ::io::nmea_serial
{
public:
	message_reader()
		: nmea_serial(utils::make_unique<dummy_device>())
		, sentence_received(false)
	{}

	std::string read_sentence()
	{
		while (true) {
			if (sentence_received) {
				sentence_received = false;
				return sentence;
			}
			read();
		}
	}

protected:
	virtual void process_sentence(const std::string& s) override
	{
		sentence = s;
		sentence_received = true;
	}

private:
	bool sentence_received;
	std::string sentence;
};

class Test_io_nmea_serial : public ::testing::Test
{
};

TEST_F(Test_io_nmea_serial, read_count_sentences)
{
	dummy_reader device;

	try {
		while (true)
			device.read();
	} catch (...) {
	}

	EXPECT_EQ(3, device.get_num_sentences());
}

TEST_F(Test_io_nmea_serial, read_sentence)
{
	message_reader dev;
	std::string sentence;

	int num_sentences = 0;

	try {
		while (true) {
			auto data = dev.read_sentence();
			++num_sentences;
		}
	} catch (...) {
	}

	EXPECT_EQ(3, num_sentences);
}

TEST_F(Test_io_nmea_serial, read_first_sentence)
{
	message_reader dev;
	std::string sentence;

	ASSERT_NO_THROW(sentence = dev.read_sentence());
	EXPECT_EQ(68u, sentence.size());
}
}
