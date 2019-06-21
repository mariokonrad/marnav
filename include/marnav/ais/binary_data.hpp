#ifndef MARNAV__AIS__BINARY_DATA__HPP
#define MARNAV__AIS__BINARY_DATA__HPP

#include <string>
#include <marnav/utils/bitset.hpp>

namespace marnav
{
namespace ais
{
/// Type for raw AIS data.
using raw = utils::bitset<uint8_t>;

/// @{

char decode_sixbit_ascii(uint8_t value);
uint8_t encode_sixbit_ascii(char c);

/// @}

std::string trim_ais_string(const std::string & s);

/// Empty baseclass for binary data, provides protected functions to read and
/// write binary data from/to bitsets.
class binary_data
{
protected:
	/// Represents data to be read from / written to a bitset.
	/// The offset and number of bits (or sixbits) is encoded in the
	/// template signature.
	///
	/// This template is used to specify the mapping (offset, count) of
	/// a specific datum within the bitset, without the need of repeating
	/// the mapping for read and write operations.
	///
	/// @tparam Offset The offset of the value within the bitset.
	/// @tparam Count Number of bits of the value within the bitset.
	/// @tparam T Data type to be used.
	template <std::size_t Offset, std::size_t Count, typename T> struct bitset_value final {
		friend class binary_data;

	public:
		static constexpr std::size_t offset = Offset;
		static constexpr std::size_t count = Count;
		using value_type = T;

		bitset_value(value_type t)
			: value(t)
		{
		}

		bitset_value(const bitset_value &) = default;
		bitset_value & operator=(const bitset_value &) = default;

		bitset_value(bitset_value &&) = default;
		bitset_value & operator=(bitset_value &&) = default;

		value_type get() const { return value; }

		operator value_type() const { return value; }

		bitset_value & operator=(value_type t)
		{
			value = t;
			return *this;
		}

	private:
		value_type value;
	};

	/// @{

	static std::string read_string(
		const raw & bits, raw::size_type ofs, raw::size_type count_sixbits);

	static void write_string(
		raw & bits, raw::size_type ofs, raw::size_type count_sixbits, const std::string & s);

	/// @}

	/// @{

	/// Reads data from the AIS message (bitset).
	/// This is the `enum` variant.
	///
	/// @tparam T `bitset_value` type.
	/// @param[in] bits The AIS message to read from.
	/// @param[out] t The data read from the message.
	///
	template <typename T,
		typename std::enable_if<std::is_enum<typename T::value_type>::value, int>::type = 0>
	static void get(const raw & bits, T & t)
	{
		typename std::underlying_type<typename T::value_type>::type tmp;
		bits.get(tmp, T::offset, T::count);
		t.value = static_cast<typename T::value_type>(tmp);
	}

	/// The `bool` variant of `get`.
	/// @see get
	template <typename T,
		typename std::enable_if<std::is_same<typename T::value_type, bool>::value, int>::type
		= 0>
	static void get(const raw & bits, T & t)
	{
		t = bits.get_bit(T::offset);
	}

	/// The non `enum` and non `string` variant of `get`.
	/// @see get
	template <typename T, typename std::enable_if<!std::is_enum<typename T::value_type>::value
								  && !std::is_same<typename T::value_type, bool>::value
								  && !std::is_same<typename T::value_type, std::string>::value,
							  int>::type
		= 0>
	static void get(const raw & bits, T & t)
	{
		bits.get(t.value, T::offset, T::count);
	}

	/// The `string` variant of `get`.
	/// @see get
	template <typename T, typename std::enable_if<!std::is_enum<typename T::value_type>::value
								  && !std::is_same<typename T::value_type, bool>::value
								  && std::is_same<typename T::value_type, std::string>::value,
							  int>::type
		= 0>
	static void get(const raw & bits, T & t)
	{
		t.value = read_string(bits, T::offset, T::count);
	}

	/// @}

	/// @{

	/// Writes data to the AIS message (bitset).
	/// This is the `enum` variant.
	///
	/// @tparam T `bitset_value` type.
	/// @param[in] bits The AIS message to write to.
	/// @param[out] t The data to write into the message.
	///
	template <typename T,
		typename std::enable_if<std::is_enum<typename T::value_type>::value, int>::type = 0>
	static void set(raw & bits, const T & t)
	{
		bits.set(
			static_cast<typename std::underlying_type<typename T::value_type>::type>(t.value),
			T::offset, T::count);
	}

	/// The `bool` variant of `set`.
	/// @see set
	template <typename T,
		typename std::enable_if<std::is_same<typename T::value_type, bool>::value, int>::type
		= 0>
	static void set(raw & bits, const T & t)
	{
		bits.set_bit(T::offset, t.value);
	}

	/// The non `enum` and non `string` variant of `set`.
	/// @see set
	template <typename T, typename std::enable_if<!std::is_enum<typename T::value_type>::value
								  && !std::is_same<typename T::value_type, bool>::value
								  && !std::is_same<typename T::value_type, std::string>::value,
							  int>::type
		= 0>
	static void set(raw & bits, const T & t)
	{
		bits.set(t.value, T::offset, T::count);
	}

	/// The `string` variant of `set`.
	/// @see set
	template <typename T, typename std::enable_if<!std::is_enum<typename T::value_type>::value
								  && !std::is_same<typename T::value_type, bool>::value
								  && std::is_same<typename T::value_type, std::string>::value,
							  int>::type
		= 0>
	static void set(raw & bits, const T & t)
	{
		write_string(bits, T::offset, T::count, t.value);
	}

	/// @}
};
}
}

#endif
