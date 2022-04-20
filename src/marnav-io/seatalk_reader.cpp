#include <marnav-io/seatalk_reader.hpp>
#include <algorithm>
#include <stdexcept>

namespace marnav
{
namespace io
{
seatalk_reader::seatalk_reader(std::unique_ptr<device> && dv)
	: dev_(std::move(dv))
{
	std::fill_n(reinterpret_cast<uint8_t *>(&ctx_), sizeof(ctx_), 0);

	ctx_.state = State::READ;
	ctx_.remaining = 255;
	ctx_.index = 0;
}

void seatalk_reader::close()
{
	if (dev_)
		dev_->close();
	dev_.reset();
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
	if (ctx_.remaining > 0 && ctx_.remaining < 254) {
		++ctx_.collisions;
	}

	ctx_.data[0] = c;
	ctx_.index = 1;
	ctx_.remaining = 254;
}

/// Writes data into the read context buffer.
void seatalk_reader::write_data(uint8_t c)
{
	if (ctx_.index >= sizeof(ctx_.data))
		return;

	if (ctx_.remaining == 0)
		return;

	if (ctx_.remaining == 255) // not yet in sync
		return;

	if (ctx_.remaining == 254) {
		// attribute byte, -1 because cmd is already consumed
		ctx_.remaining = 3 + (c & 0x0f) - 1;
	}

	ctx_.data[ctx_.index] = c;
	++ctx_.index;
	--ctx_.remaining;
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
/// Read more about parity error marking here:
///   http://www.gnu.org/software/libc/manual/html_node/Input-Modes.html
///
/// @exception std::runtime_error Bus read error.
void seatalk_reader::process_seatalk()
{
	switch (ctx_.state) {
		case State::READ:
			if (ctx_.raw == 0xff) {
				ctx_.state = State::ESCAPE;
			} else {
				if (parity(ctx_.raw)) {
					write_cmd(ctx_.raw);
				} else {
					write_data(ctx_.raw);
					if (ctx_.remaining == 0)
						emit_message();
				}
			}
			break;

		case State::ESCAPE:
			if (ctx_.raw == 0x00) {
				ctx_.state = State::PARITY;
			} else if (ctx_.raw == 0xff) {
				write_data(ctx_.raw);
				if (ctx_.remaining == 0)
					emit_message();
				ctx_.state = State::READ;
			} else {
				throw std::runtime_error{"SeaTalk bus read error."};
			}
			break;

		case State::PARITY:
			if (parity(ctx_.raw)) {
				write_data(ctx_.raw);
				if (ctx_.remaining == 0)
					emit_message();
			} else {
				write_cmd(ctx_.raw);
			}
			ctx_.state = State::READ;
			break;
	}
}

/// Reads data from the device.
///
/// @retval true  Success.
/// @retval false End of file.
/// @exception std::runtime_error The device was invalid or read error.
bool seatalk_reader::read_data()
{
	if (!dev_)
		throw std::runtime_error{"device invalid"};
	int rc = dev_->read(reinterpret_cast<char *>(&ctx_.raw), sizeof(ctx_.raw));
	if (rc == 0)
		return false;
	if (rc < 0)
		throw std::runtime_error{"read error"};
	if (rc != sizeof(ctx_.raw))
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
bool seatalk_reader::read()
{
	if (!read_data())
		return false;
	process_seatalk();
	return true;
}

void seatalk_reader::emit_message()
{
	process_message(std::vector<uint8_t>{ctx_.data, ctx_.data + ctx_.index});
}
}
}
