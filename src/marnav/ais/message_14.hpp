#ifndef MARNAV__AIS__MESSAGE_14__HPP
#define MARNAV__AIS__MESSAGE_14__HPP

#include <marnav/ais/message.hpp>
#include <marnav/utils/mmsi.hpp>

#include <marnav/marnav_export.h>

namespace marnav
{
namespace ais
{
/// @brief Safety-Related Broadcast Message
class MARNAV_EXPORT message_14 : public message
{
	friend class detail::factory;

public:
	constexpr static message_id ID = message_id::safety_related_broadcast_message;
	constexpr static int SIZE_BITS_HEAD = 40;
	constexpr static int SIZE_BITS_MAX = 1008;
	constexpr static std::size_t SIZE_TEXT_MAX = 161u;

	message_14();
	message_14(const message_14 &) = default;
	message_14 & operator=(const message_14 &) = default;
	message_14(message_14 &&) = default;
	message_14 & operator=(message_14 &&) = default;

protected:
	message_14(const raw & bits);
	void read_data(const raw & bits);
	virtual raw get_data() const override;

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif
	// clang-format off
	bitset_value< 6,  2, uint32_t> repeat_indicator = 0;
	bitset_value< 8, 30, uint32_t> mmsi = 0;
	// clang-format on

	std::string text; // bits 72..1008
#ifdef _MSC_VER
#pragma warning(pop)
#endif

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi}; }
	std::string get_text() const { return text; }

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi = t; }
	void set_text(const std::string & t);
};
}
}

#endif
