#ifndef __AIS__MESSAGE_10__HPP__
#define __AIS__MESSAGE_10__HPP__

#include "message.hpp"
#include <marnav/geo/angle.hpp>

namespace marnav
{
namespace ais
{

class message_10 : public message
{
public:
	constexpr static const message_id ID = message_id::utc_and_date_inquiry;
	constexpr static const int SIZE_BITS = 72;

	message_10();
	message_10(const message_10 &) = default;
	message_10 & operator=(const message_10 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & bits) throw(std::invalid_argument);

protected:
	void read_data(const raw & bits);

private:
	unsigned int repeat_indicator;
	uint32_t mmsi;
	uint32_t dest_mmsi;

public:
	unsigned int get_repeat_indicator() const { return repeat_indicator; }
	uint32_t get_mmsi() const { return mmsi; }
	uint32_t get_dest_mmsi() const { return dest_mmsi; }

	void set_repeat_indicator(unsigned int t) { repeat_indicator = t; }
	void set_mmsi(uint32_t t) { mmsi = t; }
	void set_dest_mmsi(uint32_t t) { mmsi = t; }
};
}
}

#endif
