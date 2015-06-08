#ifndef __MARNAV__IO__DEFAULT_SEATALK_READER__HPP__
#define __MARNAV__IO__DEFAULT_SEATALK_READER__HPP__

#include <marnav/io/seatalk_reader.hpp>

namespace marnav
{
namespace io
{

class default_seatalk_reader : public seatalk_reader
{
public:
	default_seatalk_reader(std::unique_ptr<device> && dev);
	bool read_message(seatalk::raw & data);

protected:
	virtual void process_message(const seatalk::raw & msg) override;

private:
	bool message_received;
	seatalk::raw message;
};
}
}

#endif
