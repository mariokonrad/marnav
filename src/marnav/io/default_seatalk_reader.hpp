#ifndef MARNAV__IO__DEFAULT_SEATALK_READER__HPP
#define MARNAV__IO__DEFAULT_SEATALK_READER__HPP

#include <marnav/io/seatalk_reader.hpp>

#include <marnav/marnav_export.h>

namespace marnav
{
namespace io
{
/// Default implementation of a SeaTalk reader.
class MARNAV_EXPORT default_seatalk_reader : public seatalk_reader
{
public:
	default_seatalk_reader() = delete;
	default_seatalk_reader(std::unique_ptr<device> &&);
	default_seatalk_reader(const default_seatalk_reader &) = delete;
	default_seatalk_reader(default_seatalk_reader &&) = default;

	default_seatalk_reader & operator=(const default_seatalk_reader &) = delete;
	default_seatalk_reader & operator=(default_seatalk_reader &&) = default;

	virtual ~default_seatalk_reader() {}

	bool read_message(seatalk::raw & data);

protected:
	virtual void process_message(const seatalk::raw & msg) override;

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif
	bool message_received_;
	seatalk::raw message_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
};
}
}

#endif
