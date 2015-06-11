#include "seatalk_reader.hpp"
#include <algorithm>

namespace marnav
{
namespace io
{
seatalk_reader::seatalk_reader(std::unique_ptr<device> && dev)
	: dev(std::move(dev))
{
	std::fill_n(reinterpret_cast<uint8_t *>(&ctx), sizeof(ctx), 0);

	ctx.state = State::READ;
	ctx.remaining = 255;
	ctx.index = 0;
}

seatalk_reader::~seatalk_reader() {}

void seatalk_reader::close()
{
	if (dev)
		dev->close();
	dev.reset();
}

uint8_t seatalk_reader::parity(uint8_t a) const
{
	int c = 0;

	for (int i = 0; i < 8; ++i) {
		if (a & 0x01)
			++c;
		a >>= 1;
	}
	return (c % 2) == 0;
}

void seatalk_reader::write_cmd(uint8_t c)
{
	if (ctx.remaining > 0 && ctx.remaining < 254) {
		++ctx.collisions;
	}

	ctx.data[0] = c;
	ctx.index = 1;
	ctx.remaining = 254;
}

/// Writes data into the read context buffer.
void seatalk_reader::write_data(uint8_t c)
{
	if (ctx.index >= sizeof(ctx.data))
		return;

	if (ctx.remaining == 0)
		return;

	if (ctx.remaining == 255) // not yet in sync
		return;

	if (ctx.remaining == 254) {
		// attribute byte, -1 because cmd is already consumed
		ctx.remaining = 3 + (c & 0x0f) - 1;
	}

	ctx.data[ctx.index] = c;
	++ctx.index;
	--ctx.remaining;
}

/// Processes SeaTalk data read from the device.
///
/// This function contains a state machine, which does the handling
/// of the SeaTalk specific feature: misusing the parity bit as
/// indicator for command bytes.
/// Since termios is in use, which provides parity error information
/// as quoting bytes, a non-trivial implementation is needed to
/// distinguish between normal and command bytes. Also, collision
/// detection on this pseudo-bus (SeaTalk) is handled.
///
/// @exception std::runtime_error Bus read error.
void seatalk_reader::process_seatalk() throw(std::runtime_error)
{
	switch (ctx.state) {
		case State::READ:
			if (ctx.raw == 0xff) {
				ctx.state = State::ESCAPE;
			} else {
				if (parity(ctx.raw)) {
					write_cmd(ctx.raw);
				} else {
					write_data(ctx.raw);
					if (ctx.remaining == 0)
						emit_message();
				}
			}
			break;

		case State::ESCAPE:
			if (ctx.raw == 0x00) {
				ctx.state = State::PARITY;
			} else if (ctx.raw == 0xff) {
				write_data(ctx.raw);
				if (ctx.remaining == 0)
					emit_message();
				ctx.state = State::READ;
			} else {
				throw std::runtime_error{"SeaTalk bus read error."};
			}
			break;

		case State::PARITY:
			if (parity(ctx.raw)) {
				write_data(ctx.raw);
				if (ctx.remaining == 0)
					emit_message();
			} else {
				write_cmd(ctx.raw);
			}
			ctx.state = State::READ;
			break;
	}
}

/// Reads data from the device.
///
/// @retval true  Success.
/// @retval false End of file.
/// @exception std::runtime_error The device was invalid or read error.
bool seatalk_reader::read_data() throw(std::runtime_error)
{
	if (!dev)
		throw std::runtime_error{"device invalid"};
	int rc = dev->read(reinterpret_cast<char *>(&ctx.raw), sizeof(ctx.raw));
	if (rc == 0)
		return false;
	if (rc < 0)
		throw std::runtime_error{"read error"};
	if (rc != sizeof(ctx.raw))
		throw std::runtime_error{"read error"};
	return true;
}

/// Reads data from the device and processes it. If a complete SeaTalk
/// message was received the method process_message will be executed.
/// This method automatcially synchronizes with the SeaTalk bus.
///
/// @retval true  Success.
/// @retval false End of file.
/// @exception std::runtime_error Device or processing error.
bool seatalk_reader::read() throw(std::runtime_error)
{
	if (!read_data())
		return false;
	process_seatalk();
	return true;
}

void seatalk_reader::emit_message()
{
	process_message(std::vector<uint8_t>{ctx.data, ctx.data + ctx.index});
}
}
}
