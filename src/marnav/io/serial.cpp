#include "serial.hpp"
#include <stdexcept>
#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

namespace marnav
{
namespace io
{

/// @cond DEV
namespace detail
{
static tcflag_t get_baud(serial::baud baud_rate)
{
	switch (baud_rate) {
		case serial::baud::baud_300:
			return B300;
		case serial::baud::baud_600:
			return B600;
		case serial::baud::baud_1200:
			return B1200;
		case serial::baud::baud_2400:
			return B2400;
		case serial::baud::baud_4800:
			return B4800;
		case serial::baud::baud_9600:
			return B9600;
		case serial::baud::baud_19200:
			return B19200;
		case serial::baud::baud_38400:
			return B38400;
		case serial::baud::baud_57600:
			return B57600;
		case serial::baud::baud_115200:
			return B115200;
		case serial::baud::baud_230400:
			return B230400;
		default:
			break;
	};
	return B0;
}

static tcflag_t get_data_bits(serial::databits data_bits)
{
	switch (data_bits) {
		case serial::databits::bit_5:
			return CS5;
		case serial::databits::bit_6:
			return CS6;
		case serial::databits::bit_7:
			return CS7;
		case serial::databits::bit_8:
			return CS8;
		default:
			break;
	}
	return 0;
}

static tcflag_t get_stop_bits(serial::stopbits stop_bits)
{
	switch (stop_bits) {
		case serial::stopbits::bit_1:
			return 0;
		case serial::stopbits::bit_2:
			return CSTOPB;
		default:
			break;
	}
	return 0;
}

static tcflag_t get_parity_cflag(serial::parity par)
{
	switch (par) {
		case serial::parity::none:
			return 0;
		case serial::parity::even:
			return PARENB;
		case serial::parity::odd:
			return PARENB | PARODD;
		case serial::parity::mark:
			return 0;
	}
	return 0;
}

static tcflag_t get_parity_iflag(serial::parity par)
{
	switch (par) {
		case serial::parity::none:
			return IGNPAR;
		case serial::parity::even:
			return INPCK;
		case serial::parity::odd:
			return INPCK;
		case serial::parity::mark:
			return PARMRK;
	}
	return 0;
}
}
/// @endcond

serial::~serial()
{
	close();
}

serial::serial(const std::string & dv, baud b, databits d, stopbits s, parity p)
	: fd(-1)
	, dev_(dv)
	, baud_rate_(b)
	, data_bits_(d)
	, stop_bits_(s)
	, par_(p)
{
}

/// Opens a serial device.
void serial::open()
{
	termios old_tio;
	termios new_tio;

	if (fd >= 0)
		return;

	fd = ::open(dev_.c_str(), O_RDWR | O_NOCTTY);
	if (fd < 0)
		throw std::runtime_error{"unable to open device: " + dev_};

	tcgetattr(fd, &old_tio);
	memset(&new_tio, 0, sizeof(new_tio));
	new_tio.c_cflag = detail::get_baud(baud_rate_) | detail::get_data_bits(data_bits_)
		| detail::get_stop_bits(stop_bits_) | detail::get_parity_cflag(par_)
		| CLOCAL // ignore modem control lines
		| CREAD // enable receiver
		;
	new_tio.c_iflag = 0 | detail::get_parity_iflag(par_);
	new_tio.c_oflag = 0;
	new_tio.c_lflag = 0;

	new_tio.c_cc[VMIN] = 1;
	new_tio.c_cc[VTIME] = 0;

	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &new_tio);
}

/// Closes the device, specified by the device handling structure.
void serial::close()
{
	if (fd < 0)
		return;
	::close(fd);
	fd = -1;
}

/// Reads the specified amount of bytes from the serial line into the
/// provided buffer.
///
/// @param[out] buffer The buffer to hold the data.
/// @param[in] size The size of the buffer in bytes.
/// @return Number of read bytes (might be 0).
/// @exception std::invalid_argument
/// @exception std::runtime_error
int serial::read(char * buffer, uint32_t size)
{
	if ((buffer == nullptr) || (size == 0))
		throw std::invalid_argument{"invalid buffer or size"};
	if (fd < 0)
		throw std::runtime_error{"device not open"};
	return ::read(fd, buffer, size);
}

/// Writes the speicified buffer to the serial line.
///
/// @param[in] buffer The data to write.
/// @param[in] size Number of bytes to write from the buffer to the serial line.
/// @return Number of written bytes.
/// @exception std::invalid_argument
/// @exception std::runtime_error
int serial::write(const char * buffer, uint32_t size)
{
	if ((buffer == nullptr) || (size == 0))
		throw std::invalid_argument{"invalid buffer or size"};
	if (fd < 0)
		throw std::runtime_error{"device not open"};
	return ::write(fd, buffer, size);
}
}
}
