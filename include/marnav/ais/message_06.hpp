#ifndef MARNAV__AIS__MESSAGE_06__HPP
#define MARNAV__AIS__MESSAGE_06__HPP

#include <marnav/ais/message.hpp>
#include <marnav/utils/mmsi.hpp>

namespace marnav
{
namespace ais
{
/// @brief Binary Addressed Message
class message_06 : public message
{
	friend class detail::factory;

public:
	constexpr static message_id ID = message_id::binary_addressed_message;
	constexpr static std::size_t SIZE_BITS_HEAD = 88u;
	constexpr static std::size_t SIZE_BITS_MAX = 1008u;

	message_06();
	message_06(const message_06 &) = default;
	message_06 & operator=(const message_06 &) = default;
	message_06(message_06 &&) = default;
	message_06 & operator=(message_06 &&) = default;

protected:
	message_06(const raw & bits);
	void read_data(const raw & bits);
	virtual raw get_data() const override;

private:
	// clang-format off
	bitset_value< 6,  2, uint32_t> repeat_indicator = 0;
	bitset_value< 8, 30, uint32_t> mmsi = 0;
	bitset_value<38,  2, uint32_t> sequence_no = 0;
	bitset_value<40, 30, uint32_t> dest_mmsi = 0;
	bitset_value<70,  1, bool    > retransmit_flag = false;
	bitset_value<72, 10, uint32_t> dac = 0; ///< Designate Area Cod3
	bitset_value<82,  6, uint32_t> fid = 0; ///< Functional ID
	// clang-format on

	// unfortuanately std::variant is C++17, therefore we need to store
	// the binary payload and parse it later.
	raw payload;

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi}; }
	uint32_t get_sequnce_no() const noexcept { return sequence_no; }
	utils::mmsi get_dest_mmsi() const noexcept { return utils::mmsi{dest_mmsi}; }
	bool get_retransmit_flag() const noexcept { return retransmit_flag; }
	uint32_t get_dac() const noexcept { return dac; }
	uint32_t get_fid() const noexcept { return fid; }

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi = t; }
	void set_sequnce_no(uint32_t t) noexcept { sequence_no = t; }
	void set_dest_mmsi(const utils::mmsi & t) noexcept { dest_mmsi = t; }
	void set_retransmit_flag(bool t) noexcept { retransmit_flag = t; }
	void set_dac(uint32_t t) noexcept { dac = t; }
	void set_fid(uint32_t t) noexcept { fid = t; }
};
}
}

#endif
