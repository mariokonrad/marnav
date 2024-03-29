#ifndef MARNAV_SEATALK_MESSAGE_38_HPP
#define MARNAV_SEATALK_MESSAGE_38_HPP

#include <marnav/seatalk/message.hpp>

namespace marnav::seatalk
{

/// @brief Codelock data
///
/// @code
/// 38 X1 YY yy
/// @endcode
///
/// @todo Implement data of this message
///
class message_38 : public message
{
public:
	constexpr static const message_id ID = message_id::codelock_data;
	constexpr static size_t SIZE = 4;

	message_38();
	message_38(const message_38 &) = default;
	message_38 & operator=(const message_38 &) = default;

	raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);
};
}

#endif
