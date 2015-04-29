#include <gtest/gtest.h>
#include <marnav/io/seatalk_serial.hpp>
#include <marnav/io/device.hpp>

namespace
{

using namespace marnav;

static const uint8_t DATA[] =
{
	// preliminary garbage
	0x01,             // bit=0 parity=0 : no error : ?
	0xff, 0x00, 0x00, // bit=0 parity=1 : error    : ?
	0x01,             // bit=0 parity=0 : no error : ?
	0x01,             // bit=0 parity=0 : no error : ?
	0xff, 0xff,       // bit=0 parity=1 : error    : ?
	0xff, 0xff,       // bit=0 parity=1 : error    : ?
	0x01,             // bit=0 parity=0 : no error : ?

	// depth
	0x00,             // bit=1 parity=1 : no error : cmd
	0x02,             // bit=0 parity=0 : no error : data
	0xff, 0x00, 0x60, // bit=0 parity=1 : error    : data
	0xff, 0x00, 0x65, // bit=0 parity=1 : error    : data
	0xff, 0x00, 0x00, // bit=0 parity=1 : error    : data

	// speed through water */
	0xff, 0x00, 0x26, // bit=1 parity=0 : error    : cmd
	0x04,             // bit=0 parity=0 : no error : data
	0xff, 0x00, 0x00, // bit=0 parity=1 : error    : data
	0xff, 0x00, 0x00, // bit=0 parity=1 : error    : data
	0xff, 0x00, 0x00, // bit=0 parity=1 : error    : data
	0xff, 0x00, 0x00, // bit=0 parity=1 : error    : data
	0xff, 0x00, 0x00, // bit=0 parity=1 : error    : data

	// water temperature
	0x27,             // bit=1 parity=1 : no error : cmd
	0x01,             // bit=0 parity=0 : no error : data
	0x64,             // bit=0 parity=0 : no error : data
	0xff, 0x00, 0x00, // bit=0 parity=1 : error    : data

	// apparent wind speed
	0x11,             // bit=1 parity=1 : no error : cmd
	0x01,             // bit=0 parity=0 : no error : data
	0xff, 0x00, 0x06, // bit=0 parity=1 : error    : data
	0x01,             // bit=0 parity=0 : no error : data

	// speed through water
	0xff, 0x00, 0x20, // bit=1 parity=0 : error    : cmd
	0x01,             // bit=0 parity=0 : no error : data
	0xff, 0x00, 0x00, // bit=0 parity=1 : error    : data
	0xff, 0x00, 0x00, // bit=0 parity=1 : error    : data

	// water temperature
	0xff, 0x00, 0x23, // bit=1 parity=0 : error    : cmd
	0x01,             // bit=0 parity=0 : no error : data
	0xff, 0x00, 0x33, // bit=0 parity=1 : error    : data
	0x5b,             // bit=0 parity=0 : no error : data

	// apparent wind angle
	0xff, 0x00, 0x10, // bit=1 parity=0 : error    : cmd
	0x01,             // bit=0 parity=0 : no error : data
	0xff, 0x00, 0x00, // bit=0 parity=1 : error    : data
	0xff, 0x00, 0x14, // bit=0 parity=1 : error    : data

	// depth
	0x00,             // bit=1 parity=1 : no error : cmd
	0x02,             // bit=0 parity=0 : no error : data
	0xff, 0x00, 0x60, // bit=0 parity=1 : error    : data
	0xff, 0x00, 0x65, // bit=0 parity=1 : error    : data
	0xff, 0x00, 0x00, // bit=0 parity=1 : error    : data

	// depth, collision
	0x00,             // bit=1 parity=1 : no error : cmd
	0x02,             // bit=0 parity=0 : no error : data
	0xff, 0x00, 0x60, // bit=0 parity=1 : error    : data
	// collision here, two bytes lost

	// apparent wind angle
	0xff, 0x00, 0x10, // bit=1 parity=0 : error    : cmd
	0x01,             // bit=0 parity=0 : no error : data
	0xff, 0x00, 0x00, // bit=0 parity=1 : error    : data
	0xff, 0x00, 0x14, // bit=0 parity=1 : error    : data
};

class dummy_device : public ::io::device
{
public:
	dummy_device()
		: index(0)
	{
	}

	void open() throw(std::runtime_error) override {}
	void close() override {}

	/// Just go through the data once.
	virtual int read(char * buffer, uint32_t size) throw(
		std::invalid_argument, std::runtime_error) override
	{
		if (size != sizeof(*buffer))
			throw std::invalid_argument{"buffer type not supported"};
		if (index >= sizeof(DATA))
			return 0; // end of data
		*buffer = static_cast<char>(DATA[index]);
		++index;
		return 1;
	}

	virtual int write(const char *, uint32_t) throw(
		std::invalid_argument, std::runtime_error) override
	{
		throw std::runtime_error{"operation not supported"};
	}

private:
	uint32_t index;
};

class dummy_reader : public ::io::seatalk_serial
{
public:
	dummy_reader()
		: seatalk_serial(utils::make_unique<dummy_device>())
		, num_messages(0)
	{
	}

	int get_num_messages() const { return num_messages; }

protected:
	virtual void process_message(const seatalk::raw &) override { ++num_messages; }

private:
	int num_messages;
};

/// Works only in a single threaded context (true for dummuy_device and seatalk_serial).
class message_reader : public ::io::seatalk_serial
{
public:
	message_reader()
		: seatalk_serial(utils::make_unique<dummy_device>())
		, message_received(false)
	{
	}

	bool read_message(seatalk::raw & data)
	{
		while (read()) {
			if (message_received) {
				data = message;
				message_received = false;
				return true;
			}
		}
		return false;
	}

protected:
	virtual void process_message(const seatalk::raw & msg) override
	{
		message = msg;
		message_received = true;
	}

private:
	bool message_received;
	seatalk::raw message;
};

class Test_io_seatalk_serial : public ::testing::Test
{
};

TEST_F(Test_io_seatalk_serial, read_count_messages_and_collisions)
{
	dummy_reader device;

	while (device.read());

	EXPECT_EQ(9, device.get_num_messages());
	EXPECT_EQ(1u, device.get_collisions());
}

TEST_F(Test_io_seatalk_serial, read_message)
{
	message_reader dev;
	seatalk::raw msg;

	int num_messages = 0;
	seatalk::raw data;

	while (dev.read_message(data))
		++num_messages;

	EXPECT_EQ(9, num_messages);
}

TEST_F(Test_io_seatalk_serial, read_first_message__depth)
{
	message_reader dev;
	seatalk::raw msg;

	ASSERT_NO_THROW(dev.read_message(msg));
	EXPECT_EQ(5u, msg.size());
	EXPECT_EQ(0x00u, msg[0]);
	EXPECT_EQ(0x02u, msg[1]);
	EXPECT_EQ(0x60u, msg[2]);
	EXPECT_EQ(0x65u, msg[3]);
	EXPECT_EQ(0x00u, msg[4]);
}

TEST_F(Test_io_seatalk_serial, read_third_message__water_temperature)
{
	message_reader dev;
	seatalk::raw msg;

	ASSERT_NO_THROW(dev.read_message(msg));
	ASSERT_NO_THROW(dev.read_message(msg));
	ASSERT_NO_THROW(dev.read_message(msg));
	EXPECT_EQ(4u, msg.size());
	EXPECT_EQ(0x27u, msg[0]);
	EXPECT_EQ(0x01u, msg[1]);
	EXPECT_EQ(0x64u, msg[2]);
	EXPECT_EQ(0x00u, msg[3]);
}
}
