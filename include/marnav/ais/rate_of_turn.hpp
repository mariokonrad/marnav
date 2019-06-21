#ifndef MARNAV__AIS__RATE_OF_TURN__HPP
#define MARNAV__AIS__RATE_OF_TURN__HPP

#include <cstdint>

namespace marnav
{
namespace ais
{
class rate_of_turn
{
public:
	using value_type = int8_t;

	enum : value_type {
		not_turning = 0,
		more_5deg_per_30s_abs = 127,
		more_5deg_per_30s_right = +more_5deg_per_30s_abs,
		more_5deg_per_30s_left = -more_5deg_per_30s_abs,
		no_information_available = -128
	};

	rate_of_turn() = default;

	rate_of_turn(const rate_of_turn &) = default;
	rate_of_turn & operator=(const rate_of_turn &) = default;

	rate_of_turn(rate_of_turn &&) = default;
	rate_of_turn & operator=(rate_of_turn &&) = default;

	explicit rate_of_turn(double deg_per_minute);

	explicit rate_of_turn(value_type raw_value)
		: value_(raw_value)
	{
	}

	double value() const;

	value_type raw() const noexcept { return value_; }

	operator double() const { return value(); }

	bool available() const noexcept { return value_ != no_information_available; }
	bool is_not_turning() const noexcept { return value_ == not_turning; }
	bool is_more_5deg30s_right() const noexcept { return value_ == more_5deg_per_30s_right; }
	bool is_more_5deg30s_left() const noexcept { return value_ == more_5deg_per_30s_left; }

private:
	value_type value_ = no_information_available;
};
}
}

#endif
