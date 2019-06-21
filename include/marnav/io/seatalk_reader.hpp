#ifndef MARNAV__IO__SEATALK_READER__HPP
#define MARNAV__IO__SEATALK_READER__HPP

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
class seatalk_reader
{
public:
	virtual ~seatalk_reader();

	seatalk_reader() = delete;
	seatalk_reader(std::unique_ptr<device> &&);
	seatalk_reader(const seatalk_reader &) = delete;
	seatalk_reader(seatalk_reader &&) = default;

	seatalk_reader & operator=(const seatalk_reader &) = delete;
	seatalk_reader & operator=(seatalk_reader &&) = default;

	void close();
	bool read();
	uint32_t get_collisions() const { return ctx_.collisions; }

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
	void process_seatalk();
	bool read_data();

	context ctx_;
	std::unique_ptr<device> dev_; ///< Device to read data from.
};
}
}

#endif
