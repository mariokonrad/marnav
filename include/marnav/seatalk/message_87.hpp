#ifndef MARNAV__SEATALK__MESSAGE_87__HPP
#define MARNAV__SEATALK__MESSAGE_87__HPP

#include <marnav/seatalk/message.hpp>

namespace marnav
{
namespace seatalk
{
/// @brief Set Response Level
///
/// @code
///  87 00 0X
///
///  X=1  Response level 1: Automatic Deadband
///  X=2  Response level 2: Minimum Deadband
/// @endcode
///
class message_87 : public message
{
public:
	constexpr static const message_id ID = message_id::response_level;
	constexpr static size_t SIZE = 3;

	enum class response_level { invalid = 0, automatic = 1, minimum = 2 };

	message_87();
	message_87(const message_87 &) = default;
	message_87 & operator=(const message_87 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);

private:
	response_level level_;

public:
	response_level get_level() const { return level_; }

	void set_level(response_level t) { level_ = t; }
};
}
}

#endif
