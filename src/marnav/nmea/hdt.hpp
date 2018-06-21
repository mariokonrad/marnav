#ifndef MARNAV__NMEA__HDT__HPP
#define MARNAV__NMEA__HDT__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief HDM - Heading - True
///
/// Actual vessel heading in degrees true produced by any device or system producing true
/// heading.
///
/// @code
///        1   2
///        |   |
/// $--HDT,x.x,T*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Heading Degrees true
/// 2. Heading Degrees true reference
///    - T = true
///
class hdt : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::HDT;
	constexpr static const char * TAG = "HDT";

	hdt();
	hdt(const hdt &) = default;
	hdt & operator=(const hdt &) = default;
	hdt(hdt &&) = default;
	hdt & operator=(hdt &&) = default;

protected:
	hdt(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<double> heading_;
	utils::optional<reference> heading_true_;

public:
	decltype(heading_) get_heading() const { return heading_; }
	decltype(heading_true_) get_heading_true() const { return heading_true_; }

	void set_heading(double t) noexcept;
};
}
}

#endif
