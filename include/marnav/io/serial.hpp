#ifndef MARNAV__IO__SERIAL__HPP
#define MARNAV__IO__SERIAL__HPP

#include <string>
#include <marnav/io/device.hpp>

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
		baud_300,
		baud_600,
		baud_1200,
		baud_2400,
		baud_4800,
		baud_9600,
		baud_19200,
		baud_38400,
		baud_57600,
		baud_115200,
		baud_230400
	};

	enum class databits { bit_5, bit_6, bit_7, bit_8 };

	enum class stopbits { bit_1, bit_2 };

	enum class parity { none, even, odd, mark };

	virtual ~serial();

	serial() = delete;
	serial(const std::string & dv, baud b, databits d, stopbits s, parity p);
	serial(const serial &) = delete;
	serial(serial &&) noexcept = default;
	serial & operator=(const serial &) noexcept = delete;
	serial & operator=(serial &&) = default;

	virtual void open() override;
	virtual void close() override;
	virtual int read(char * buffer, uint32_t size) override;
	virtual int write(const char * buffer, uint32_t size) override;

protected:
	int fd; ///< File descriptor for serial device communication.

private:
	std::string dev_;
	baud baud_rate_;
	databits data_bits_;
	stopbits stop_bits_;
	parity par_;
};
}
}

#endif
