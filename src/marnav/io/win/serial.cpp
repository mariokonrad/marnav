#include "../serial.hpp"

#include <Windows.h>

#include <stdexcept>

namespace marnav
{
namespace io
{

/// @cond DEV
namespace detail
{
static DWORD get_baud(serial::baud baud_rate)
{
	switch (baud_rate) {
		case serial::baud::baud_300:
			return CBR_300;
		case serial::baud::baud_600:
			return CBR_600;
		case serial::baud::baud_1200:
			return CBR_1200;
		case serial::baud::baud_2400:
			return CBR_2400;
		case serial::baud::baud_4800:
			return CBR_4800;
		case serial::baud::baud_9600:
			return CBR_9600;
		case serial::baud::baud_19200:
			return CBR_19200;
		case serial::baud::baud_38400:
			return CBR_38400;
		case serial::baud::baud_57600:
			return CBR_57600;
		case serial::baud::baud_115200:
			return CBR_115200;
		case serial::baud::baud_230400:
			return CBR_256000;
		default:
			break;
	};
	return 0;
}

static BYTE get_data_bits(serial::databits data_bits)
{
	switch (data_bits) {
		case serial::databits::bit_5:
			return 5;
		case serial::databits::bit_6:
			return 6;
		case serial::databits::bit_7:
			return 7;
		case serial::databits::bit_8:
			return 8;
		default:
			break;
	}
	return 0;
}

static BYTE get_stop_bits(serial::stopbits stop_bits)
{
	switch (stop_bits) {
		case serial::stopbits::bit_1:
			return ONESTOPBIT;
		case serial::stopbits::bit_2:
			return TWOSTOPBITS;
		default:
			break;
	}
	return 0;
}

static BYTE get_parity_cflag(serial::parity par)
{
	switch (par) {
		case serial::parity::none:
			return NOPARITY;
		case serial::parity::even:
			return EVENPARITY;
		case serial::parity::odd:
			return ODDPARITY;
		case serial::parity::mark:
			return MARKPARITY;
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
	: fd(INVALID_HANDLE_VALUE)
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
	if (fd != INVALID_HANDLE_VALUE)
		return;

	fd = CreateFile(dev_.c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);

	if (fd == INVALID_HANDLE_VALUE)
		throw std::runtime_error{"unable to open device: " + dev_};

	DCB settings;
	memset(&settings, 0x00, sizeof(settings));
	settings.DCBlength = sizeof(settings);

	if (GetCommState(fd, &settings) == FALSE)
		throw std::runtime_error{"unable to get settings for device: " + dev_};

	settings.BaudRate = detail::get_baud(baud_rate_);
	settings.fBinary = TRUE;
	settings.fParity = (par_ != serial::parity::none);
	settings.fOutxCtsFlow = TRUE;
	settings.fOutxDsrFlow = FALSE;
	settings.fDtrControl = DTR_CONTROL_ENABLE;
	settings.fDsrSensitivity = TRUE;
	settings.fTXContinueOnXoff = FALSE;
	settings.fOutX = FALSE;
	settings.fInX = FALSE;
	settings.fErrorChar = FALSE;
	settings.fNull = FALSE;
	settings.fRtsControl = RTS_CONTROL_HANDSHAKE;
	settings.fAbortOnError = FALSE;
	settings.XoffLim = 1;
	settings.ByteSize = detail::get_data_bits(data_bits_);
	settings.Parity = detail::get_parity_cflag(par_);
	settings.StopBits = detail::get_stop_bits(stop_bits_);

	if (SetCommState(fd, &settings) == 0)
		throw std::runtime_error{"failed to set new settings for device: " + dev_};
}

/// Closes the device, specified by the device handling structure.
void serial::close()
{
	if (fd == INVALID_HANDLE_VALUE)
		return;
	CloseHandle(fd);
	fd = INVALID_HANDLE_VALUE;
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
	if (fd == INVALID_HANDLE_VALUE)
		throw std::runtime_error{"device not open"};

	DWORD bytesRead(0);

	if (ReadFile(fd, buffer, size, &bytesRead, NULL) == FALSE)
		throw std::runtime_error{"failed to read bytes"};

	return bytesRead;
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
	if (fd == INVALID_HANDLE_VALUE)
		throw std::runtime_error{"device not open"};

	DWORD bytesWritten(0);

	if (WriteFile(fd, buffer, size, &bytesWritten, NULL) == FALSE)
		throw std::runtime_error{"failed to write bytes"};

	return bytesWritten;
}
}
}
