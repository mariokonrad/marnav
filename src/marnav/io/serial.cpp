#include "serial.hpp"
#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

namespace marnav
{
namespace io
{

static tcflag_t get_baud(serial::baud baud_rate)
{
	switch (baud_rate) {
		case serial::baud::BAUD_300:
			return B300;
		case serial::baud::BAUD_600:
			return B600;
		case serial::baud::BAUD_1200:
			return B1200;
		case serial::baud::BAUD_2400:
			return B2400;
		case serial::baud::BAUD_4800:
			return B4800;
		case serial::baud::BAUD_9600:
			return B9600;
		case serial::baud::BAUD_19200:
			return B19200;
		case serial::baud::BAUD_38400:
			return B38400;
		case serial::baud::BAUD_57600:
			return B57600;
		case serial::baud::BAUD_115200:
			return B115200;
		case serial::baud::BAUD_230400:
			return B230400;
		default:
			break;
	};
	return B0;
}

static tcflag_t get_data_bits(serial::databits data_bits)
{
	switch (data_bits) {
		case serial::databits::BIT_5:
			return CS5;
		case serial::databits::BIT_6:
			return CS6;
		case serial::databits::BIT_7:
			return CS7;
		case serial::databits::BIT_8:
			return CS8;
		default:
			break;
	}
	return 0;
}

static tcflag_t get_stop_bits(serial::stopbits stop_bits)
{
	switch (stop_bits) {
		case serial::stopbits::BIT_1:
			return 0;
		case serial::stopbits::BIT_2:
			return CSTOPB;
		default:
			break;
	}
	return 0;
}

static tcflag_t get_parity_cflag(serial::parity par)
{
	switch (par) {
		case serial::parity::NONE:
			return 0;
		case serial::parity::EVEN:
			return PARENB;
		case serial::parity::ODD:
			return PARENB | PARODD;
		case serial::parity::MARK:
			return 0;
	}
	return 0;
}

static tcflag_t get_parity_iflag(serial::parity par)
{
	switch (par) {
		case serial::parity::NONE:
			return IGNPAR;
		case serial::parity::EVEN:
			return INPCK;
		case serial::parity::ODD:
			return INPCK;
		case serial::parity::MARK:
			return PARMRK;
	}
	return 0;
}

serial::serial(const std::string & dev, baud b, databits d, stopbits s, parity p)
	: fd(-1)
	, dev(dev)
	, baud_rate(b)
	, data_bits(d)
	, stop_bits(s)
	, par(p)
{
}

serial::~serial() { close(); }

/// Opens a serial device.
void serial::open()
{
	termios old_tio;
	termios new_tio;

	if (fd >= 0)
		return;

	fd = ::open(dev.c_str(), O_RDWR | O_NOCTTY);
	if (fd < 0)
		throw std::runtime_error{"unable to open device: " + dev};

	tcgetattr(fd, &old_tio);
	memset(&new_tio, 0, sizeof(new_tio));
	new_tio.c_cflag = get_baud(baud_rate) | get_data_bits(data_bits) | get_stop_bits(stop_bits)
		| get_parity_cflag(par) | CLOCAL // ignore modem control lines
		| CREAD // enable receiver
		;
	new_tio.c_iflag = 0 | get_parity_iflag(par);
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
