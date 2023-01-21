#ifndef MARNAV_AIS_MESSAGE_06_HPP
#define MARNAV_AIS_MESSAGE_06_HPP

#include <marnav/ais/message.hpp>
#include <marnav/utils/mmsi.hpp>

namespace marnav::ais
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
	raw get_data() const override;

private:
	// clang-format off
	bitset_value< 6,  2, uint32_t> repeat_indicator_ = 0;
	bitset_value< 8, 30, uint32_t> mmsi_ = 0;
	bitset_value<38,  2, uint32_t> sequence_no_ = 0;
	bitset_value<40, 30, uint32_t> dest_mmsi_ = 0;
	bitset_value<70,  1, bool    > retransmit_flag_ = false;
	bitset_value<72, 10, uint32_t> dac_ = 0; ///< Designate Area Cod3
	bitset_value<82,  6, uint32_t> fid_ = 0; ///< Functional ID
	// clang-format on

	// unfortuanately std::variant is C++17, therefore we need to store
	// the binary payload and parse it later.
	raw payload_;

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator_; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi_}; }
	uint32_t get_sequnce_no() const noexcept { return sequence_no_; }
	utils::mmsi get_dest_mmsi() const noexcept { return utils::mmsi{dest_mmsi_}; }
	bool get_retransmit_flag() const noexcept { return retransmit_flag_; }
	uint32_t get_dac() const noexcept { return dac_; }
	uint32_t get_fid() const noexcept { return fid_; }

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator_ = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi_ = t; }
	void set_sequnce_no(uint32_t t) noexcept { sequence_no_ = t; }
	void set_dest_mmsi(const utils::mmsi & t) noexcept { dest_mmsi_ = t; }
	void set_retransmit_flag(bool t) noexcept { retransmit_flag_ = t; }
	void set_dac(uint32_t t) noexcept { dac_ = t; }
	void set_fid(uint32_t t) noexcept { fid_ = t; }
};
}

#endif
