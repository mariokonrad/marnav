#ifndef MARNAV_NMEA_ACK_HPP
#define MARNAV_NMEA_ACK_HPP

#include <marnav/nmea/sentence.hpp>

namespace marnav
{
namespace nmea
{
/// @brief ACK - Acklowledge Alarm
///
/// @code
///        1
///        |
/// $--ACK,xxx*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Alarm number (identifier) at alarm source
///
class ack : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::ACK;
	constexpr static const char * TAG = "ACK";

	ack();
	ack(talker talk);
	ack(const ack &) = default;
	ack & operator=(const ack &) = default;
	ack(ack &&) = default;
	ack & operator=(ack &&) = default;

protected:
	ack(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	uint32_t number_ = 0u;

public:
	uint32_t get_number() const { return number_; }

	void set_number(uint32_t n) { number_ = n; }
};
}
}

#endif
