#ifndef MARNAV__NMEA__STALK__HPP
#define MARNAV__NMEA__STALK__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/seatalk/message.hpp>

namespace marnav
{
namespace nmea
{
/// @brief STALK - Multiple Data ID
///
/// @code
///        1
///        |
/// $--ALK,x.x*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Talker ID Number
///
class stalk : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::STALK;
	constexpr static const char * TAG = "STALK";

	stalk();
	stalk(const stalk &) = default;
	stalk & operator=(const stalk &) = default;
	stalk(stalk &&) = default;
	stalk & operator=(stalk &&) = default;

protected:
	stalk(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	seatalk::raw data_;

public:
//	decltype(number_) get_number() const { return number_; }
//	void set_number(uint32_t t) noexcept { number_ = t; }

        decltype(data_) get_raw() const { return data_; }
        void set_raw(seatalk::raw d) noexcept { data_ = d; }


};
}
}

#endif
