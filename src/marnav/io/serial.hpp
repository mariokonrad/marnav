#ifndef __IO__SERIAL__HPP__
#define __IO__SERIAL__HPP__

#include "device.hpp"
#include <string>

namespace marnav
{
namespace io
{

/// This class is an abstraction for termios based serial
/// communication.
///
/// Since this is termios based, it is platform dependent.
class serial : public device
{
public:
	enum class baud {
		BAUD_300 = 300,
		BAUD_600 = 600,
		BAUD_1200 = 1200,
		BAUD_2400 = 2400,
		BAUD_4800 = 4800,
		BAUD_9600 = 9600,
		BAUD_19200 = 19200,
		BAUD_38400 = 38400,
		BAUD_57600 = 57600,
		BAUD_115200 = 115200,
		BAUD_230400 = 230400
	};

	enum class databits { BIT_5 = 5, BIT_6 = 6, BIT_7 = 7, BIT_8 = 8 };

	enum class stopbits { BIT_1 = 1, BIT_2 = 2 };

	enum class parity { NONE, EVEN, ODD, MARK };

	serial(const std::string & dev, baud b, databits d, stopbits s, parity p);
	serial(const serial &) = delete;
	serial(serial &&) = default;
	virtual ~serial();
	serial & operator=(const serial &) = delete;

	virtual void open() throw(std::runtime_error) override;
	virtual void close() override;
	virtual int read(char * buffer, uint32_t size) throw(
		std::invalid_argument, std::runtime_error) override;
	virtual int write(const char * buffer, uint32_t size) throw(
		std::invalid_argument, std::runtime_error) override;

protected:
	int fd;

private:
	std::string dev;
	baud baud_rate;
	databits data_bits;
	stopbits stop_bits;
	parity par;
};
}
}

#endif
