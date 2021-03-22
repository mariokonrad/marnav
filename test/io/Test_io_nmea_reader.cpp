#include <marnav/io/nmea_reader.hpp>
#include <marnav/io/device.hpp>
#include <gtest/gtest.h>
#include <vector>

namespace
{

using namespace marnav;

static const std::string DATA_COMPLETE
	= {"$GPRMC,202451,A,4702.3966,N,00818.3287,E,0.0,312.3,260711,0.6,E,A*19\r\n"
	   "$GPRMC,202452,A,4702.3966,N,00818.3287,E,0.0,312.3,260711,0.6,E,A*1a\r\n"
	   "$GPRMC,202453,A,4702.3966,N,00818.3287,E,0.0,312.3,260711,0.6,E,A*1b\r\n"};

static const std::string DATA_INCOMPLETE
	= {".3287,E,0.0,312.3,260711,0.6,E,A*1a\r\n"
	   "$GPRMC,202453,A,4702.3966,N,00818.3287,E,0.0,312.3,260711,0.6,E,A*1b\r\n"};

static const std::string DATA_MISSING_EOL
	= {".3287,E,0.0,312.3,260711,0.6,E,A*1a"
	   "$GPRMC,202453,A,4702.3966,N,00818.3287,E,0.0,312.3,260711,0.6,E,A*1b\r\n"};

class dummy_device : public ::io::device
{
public:
	dummy_device(const std::string & data)
		: index(0)
		, data(data)
	{
	}

	void open() override {}
	void close() override {}

	/// Just go through the data once.
	virtual int read(char * buffer, uint32_t size) override
	{
		if (size != sizeof(*buffer))
			throw std::invalid_argument{"buffer type not supported"};
		if (index >= data.size())
			return 0; // end of data
		*buffer = data[index];
		++index;
		return 1;
	}

	virtual int write(const char *, uint32_t) override
	{
		throw std::runtime_error{"operation not supported"};
	}

private:
	std::string::size_type index;
	std::string data;
};

class test_device : public ::io::device
{
public:
	test_device(int result)
		: result(result)
	{
	}

	void open() override {}
	void close() override {}

	virtual int read(char *, uint32_t) override { return result; }

	virtual int write(const char *, uint32_t) override { return result; }

private:
	int result;
};

class dummy_reader : public ::io::nmea_reader
{
public:
	dummy_reader(const std::string & data)
		: nmea_reader(std::make_unique<dummy_device>(data))
		, num_sentences(0)
	{
	}

	int get_num_sentences() const { return num_sentences; }

protected:
	virtual void process_sentence(const std::string &) override { ++num_sentences; }

private:
	int num_sentences;
};

class no_device_reader : public ::io::nmea_reader
{
public:
	no_device_reader()
		: nmea_reader(nullptr)
	{
	}

protected:
	virtual void process_sentence(const std::string &) override {}
};

/// Works only in a single threaded context (true for dummuy_device and nmea_reader).
class message_reader : public ::io::nmea_reader
{
public:
	message_reader(const std::string & data)
		: nmea_reader(std::make_unique<dummy_device>(data))
		, sentence_received(false)
	{
	}

	message_reader(std::unique_ptr<::io::device> && dev)
		: nmea_reader(std::move(dev))
		, sentence_received(false)
	{
	}

	bool read_sentence(std::string & s)
	{
		while (read()) {
			if (sentence_received) {
				s = sentence_;
				sentence_received = false;
				return true;
			}
		}
		return false;
	}

protected:
	virtual void process_sentence(const std::string & s) override
	{
		sentence_ = s;
		sentence_received = true;
	}

private:
	bool sentence_received;
	std::string sentence_;
};

class Test_io_nmea_reader : public ::testing::Test
{
};

TEST_F(Test_io_nmea_reader, read_count_sentences)
{
	dummy_reader device{DATA_COMPLETE};

	while (device.read())
		;

	EXPECT_EQ(3, device.get_num_sentences());
}

TEST_F(Test_io_nmea_reader, read_sentence)
{
	message_reader dev{DATA_COMPLETE};

	int num_sentences = 0;
	std::string data;
	while (dev.read_sentence(data))
		++num_sentences;

	EXPECT_EQ(3, num_sentences);
}

TEST_F(Test_io_nmea_reader, read_first_sentence)
{
	message_reader dev{DATA_COMPLETE};
	std::string sentence;
	bool rc = false;

	ASSERT_NO_THROW(rc = dev.read_sentence(sentence));
	ASSERT_TRUE(rc);
	EXPECT_EQ(68u, sentence.size());
}

TEST_F(Test_io_nmea_reader, read_synchronization)
{
	message_reader dev{DATA_INCOMPLETE};
	std::string sentence;
	bool rc = false;

	ASSERT_NO_THROW(rc = dev.read_sentence(sentence));
	ASSERT_TRUE(rc);
	EXPECT_EQ(35u, sentence.size());

	ASSERT_NO_THROW(rc = dev.read_sentence(sentence));
	ASSERT_TRUE(rc);
	EXPECT_EQ(68u, sentence.size());
}

TEST_F(Test_io_nmea_reader, sentence_to_large)
{
	message_reader dev{DATA_MISSING_EOL};
	std::string sentence;

	ASSERT_THROW(dev.read_sentence(sentence), std::length_error);
}

TEST_F(Test_io_nmea_reader, no_device)
{
	no_device_reader dev{};

	ASSERT_THROW(dev.read(), std::runtime_error);
}

TEST_F(Test_io_nmea_reader, read_negative)
{
	message_reader dev{std::unique_ptr<::io::device>(new test_device(-1))};

	ASSERT_THROW(dev.read(), std::runtime_error);
}

TEST_F(Test_io_nmea_reader, read_invalid_size)
{
	message_reader dev{std::unique_ptr<::io::device>(new test_device(12345))};

	ASSERT_THROW(dev.read(), std::runtime_error);
}

TEST_F(Test_io_nmea_reader, read_after_close)
{
	message_reader dev{DATA_COMPLETE};

	ASSERT_NO_THROW(dev.read());

	dev.close();

	ASSERT_THROW(dev.read(), std::runtime_error);
}
}
