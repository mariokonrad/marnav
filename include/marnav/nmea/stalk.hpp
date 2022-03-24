#ifndef MARNAV_NMEA_STALK_HPP
#define MARNAV_NMEA_STALK_HPP

#include <marnav/nmea/sentence.hpp>

namespace marnav
{
namespace nmea
{
/// @brief STALK - SeaTalk over NMEA
///
/// @code
///        1
///        |
/// $STALK,xx[,xx]*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Hex coded 8 bit value
///
/// The sentence cannot exceed the maximum length of NMEA sentences,
/// which means up to 24 data bytes are allowed. There must be at least
/// one data byte.
///
class stalk : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::STALK;
	constexpr static const char * TAG = "STALK";

	constexpr static int MIN_FIELDS = 1;
	constexpr static int MAX_FIELDS = 24;

	using raw = std::vector<uint8_t>;

	stalk();
	stalk(const stalk &) = default;
	stalk & operator=(const stalk &) = default;
	stalk(stalk &&) = default;
	stalk & operator=(stalk &&) = default;

protected:
	stalk(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	raw data_;

public:
	raw get_data() const { return data_; }

	void set_data(const raw & t);
};
}
}

#endif
