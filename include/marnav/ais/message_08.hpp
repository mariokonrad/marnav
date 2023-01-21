#ifndef MARNAV_AIS_MESSAGE_08_HPP
#define MARNAV_AIS_MESSAGE_08_HPP

#include <marnav/ais/message.hpp>
#include <marnav/utils/mmsi.hpp>

namespace marnav::ais
{
class binary_001_11; // forward
class binary_200_10; // forward

/// @brief Binary Broadcast Message
class message_08 : public message
{
	friend class detail::factory;

public:
	constexpr static message_id ID = message_id::binary_broadcast_message;
	constexpr static std::size_t SIZE_BITS_HEAD = 56u;
	constexpr static std::size_t SIZE_BITS_MAX = 1008u;

	message_08();
	message_08(const message_08 &) = default;
	message_08 & operator=(const message_08 &) = default;
	message_08(message_08 &&) = default;
	message_08 & operator=(message_08 &&) = default;

protected:
	message_08(const raw & bits);
	void read_data(const raw & bits);
	raw get_data() const override;

private:
	// clang-format off
	bitset_value< 6,  2, uint32_t> repeat_indicator_ = 0;
	bitset_value< 8, 30, uint32_t> mmsi_ = 0;
	bitset_value<40, 10, uint32_t> dac_ = 0; ///< Designate Area Cod3
	bitset_value<50,  6, uint32_t> fid_ = 0; ///< Functional ID
	// clang-format on

	// unfortuanately std::variant is C++17, therefore we need to store
	// the binary payload and parse it later.
	raw payload_;

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator_; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi_}; }
	uint32_t get_dac() const noexcept { return dac_; }
	uint32_t get_fid() const noexcept { return fid_; }

	// payload
	void read_binary(binary_001_11 & m) const;
	void read_binary(binary_200_10 & m) const;

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator_ = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi_ = t; }
	void set_dac(uint32_t t) noexcept { dac_ = t; }
	void set_fid(uint32_t t) noexcept { fid_ = t; }

	// payload
	void write_binary(const binary_001_11 & m);
	void write_binary(const binary_200_10 & m);
};
}

#endif
