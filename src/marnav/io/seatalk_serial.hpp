#ifndef __IO__SEATALK_SERIAL__HPP__
#define __IO__SEATALK_SERIAL__HPP__

#include <marnav/io/device.hpp>
#include <marnav/seatalk/message.hpp>

namespace marnav
{
namespace io
{

/// This class reads SeaTalk messages from a device. Normally this would
/// be a serial character device (e.g. /dev/ttyS0 or /dev/ttyUSB0).
///
/// In order to use this SeaTalk reader, it must be subclassed.
///
/// @example read_seatalk.cpp
class seatalk_serial
{
public:
	seatalk_serial(std::unique_ptr<device> && dev);
	seatalk_serial(const std::string & name);

	void close();
	bool read() throw(std::runtime_error);
	uint32_t get_collisions() const { return ctx.collisions; }

protected:
	virtual void process_message(const seatalk::raw &) = 0;

private:
	enum class State { READ, ESCAPE, PARITY };

	struct context {
		State state;
		uint8_t index;
		uint8_t remaining;
		uint8_t data[seatalk::MAX_MESSAGE_SIZE];

		uint8_t raw;
		uint32_t collisions;
	};

	void emit_message();

	uint8_t parity(uint8_t a) const;
	void write_cmd(uint8_t c);
	void write_data(uint8_t c);
	void process_seatalk() throw(std::runtime_error);
	bool read_data() throw(std::runtime_error);

	context ctx;
	std::unique_ptr<device> dev; ///< Device to read data from.
};
}
}

#endif
