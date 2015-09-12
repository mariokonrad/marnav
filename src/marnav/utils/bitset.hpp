#ifndef __UTILS__BITSET__HPP__
#define __UTILS__BITSET__HPP__

/// Copyright (c) 2015 Mario Konrad <mario.konrad@gmx.net>
/// The code is licensed under the BSD License (see file LICENSE)

#include <vector>
#include <type_traits>
#include <limits>
#include <istream>
#include <stdexcept>

namespace marnav
{
namespace utils
{

/// This is a dynamically growing bitset (theoretically of arbitrary size).
///
/// Bits are stored in blocks, whose data type is configurable.
///
/// This may not be the most performant implementation, but a very flexible one.
///
/// This class suffers the same problems as std::vector<bool> does. Although is
/// provides an interator-like facility, it is not std algorithm compatible, nor
/// claims nor wants to be.
///
/// @tparam Block The data type of the underlying block type.
/// @tparam Container The container type to store blocks.
///
/// **Example:** appending individual bits
/// @code
/// bitset<uint32_t> bits;
/// bits.append(0xff, 8); // append 8 bits
/// bits.append(0xff, 6); // append 6 bits
/// bits.append(1, 1);    // append 1 bit
/// bits.append(1, 1);    // append 1 bit
/// auto result = bits.get<uint16_t>(0); // since all bits were 1, this will be 0xffff
/// @endcode
///
/// **Example:** random access to bits
/// @code
/// bitset<uint32_t> bits;
/// bits.append(0);
/// auto bit = bits[7]; // indexed access (note: read only, unchecked)
/// bits.set(0xff, 3, 2); // set 2 bits (11) at offset 3
/// @endcode
///
/// **Example:** bitset with initial number of bits
/// @code
/// bitset<uint8_t> bits{1024};
/// bits.set(1, 512, 1); // set one bit to 1 at offset 512
/// @endcode
///
template <class Block, class Container = std::vector<Block>,
	class = typename std::enable_if<!std::numeric_limits<Block>::is_signed>::type>
class bitset
{
public:
	using block_type = Block;
	enum {
		/// It is assumed, that a byte has 8 bits. This template will
		/// not work on other architectures.
		BITS_PER_BYTE = 8
	};
	enum { BITS_PER_BLOCK = sizeof(block_type) * BITS_PER_BYTE };

public:
	using size_type = typename Container::size_type;
	using data_const_iterator = typename Container::const_iterator;

	/// This is a non-std conform const iterator. The intention is
	/// to provide a basic iterator functionality without claiming
	/// to be std compliant.
	class const_iterator
	{
		friend class bitset;

	public:
		using value_type = bool;

	private:
		const bitset * bs;
		size_type pos;

	private:
		const_iterator(const bitset * const bs, size_type pos)
			: bs(bs)
			, pos(pos)
		{
		}

	public:
		const_iterator()
			: bs(nullptr)
			, pos(0)
		{
		}

		const_iterator(const const_iterator &) = default;
		const_iterator(const_iterator &&) noexcept = default;

		size_type get_pos() const { return pos; }

		const_iterator & operator=(const const_iterator &) = default;
		const_iterator & operator=(const_iterator &&) noexcept = default;

		bool operator==(const const_iterator & other) const
		{
			return bs == other.bs && pos == other.pos;
		}

		bool operator!=(const const_iterator & other) const
		{
			return bs != other.bs || pos != other.pos;
		}

		bool operator<(const const_iterator & other) const
		{
			return bs == other.bs && pos < other.pos;
		}

		bool operator>(const const_iterator & other) const
		{
			return bs == other.bs && pos > other.pos;
		}

		bool operator<=(const const_iterator & other) const
		{
			return bs == other.bs && pos <= other.pos;
		}

		bool operator>=(const const_iterator & other) const
		{
			return bs == other.bs && pos >= other.pos;
		}

		bool operator*() const
		{
			return bs != nullptr && pos < bs->size() && bs->get_bit(pos) == true;
		}

		const_iterator & operator+=(size_type ofs)
		{
			if (bs != nullptr && pos < bs->size()) {
				pos += ofs;
				if (pos > bs->size())
					pos = bs->size();
			}
			return *this;
		}

		const_iterator & operator-=(size_type ofs)
		{
			if (bs != nullptr) {
				pos = (ofs > pos) ? 0 : pos - ofs;
			}
			return *this;
		}

		const_iterator & operator++() // ++const_iterator
		{
			if (bs != nullptr && pos < bs->size()) {
				++pos;
			}
			return *this;
		}

		const_iterator & operator--() // --const_iterator
		{
			if (bs != nullptr && pos > 0) {
				--pos;
			}
			return *this;
		}

		const_iterator operator++(int) // const_iterator++
		{
			const_iterator res(*this);
			if (bs != nullptr && pos < bs->size()) {
				++pos;
			}
			return res;
		}

		const_iterator operator--(int) // const_iterator--
		{
			const_iterator res(*this);
			if (bs != nullptr && pos > 0) {
				--pos;
			}
			return res;
		}

		template <typename T> void peek(T & v, size_type bits = sizeof(T) * BITS_PER_BYTE) const
		{
			if (bs == nullptr)
				return;
			if (pos + bits > bs->size())
				throw std::out_of_range{
					"out of range, not possible to peek beyond available bits"};
			bs->get(v, pos, bits);
		}

		template <typename T> void read(T & v, size_type bits = sizeof(T) * BITS_PER_BYTE)
		{
			peek(v, bits);
			*this += bits;
		}
	};

private:
	size_type pos; // number of bits contained within the set
	Container data;

private:
	/// Extends the container by the specified number of bits.
	/// Extension is always one block.
	void extend(size_type bits)
	{
		if (bits <= 0)
			return;
		size_type n_blocks = (pos + bits + BITS_PER_BLOCK - 1) / BITS_PER_BLOCK;
		if (n_blocks > data.capacity()) {
			data.reserve(n_blocks);
			while (bits > capacity() - pos) {
				data.push_back(block_type{});
			}
		}
	}

	/// Appends the specified block to the data. The bitset is automatically extended
	/// to hold all the data.
	///
	/// @param[in] v The data to append to the bitset.
	/// @param[in] bits The number of bits to append. This value must be
	///            between 0 and BITS_PER_BLOCK. If not all bits are being
	///            appended, only the least significant bits are being taken.
	void append_block(block_type v, size_type bits = BITS_PER_BLOCK)
	{
		if (bits <= 0)
			return;
		extend(bits);
		size_type i = pos / BITS_PER_BLOCK; // index of current block

		// number of bits unused within the current block
		size_type u_bits = BITS_PER_BLOCK - (pos % BITS_PER_BLOCK);

		if (u_bits >= bits) {
			// enough room within current block
			data[i] |= v << (u_bits - bits);
		} else {
			// not enough room, split value to current and next block
			data[i + 0] |= v >> (bits - u_bits);
			data[i + 1] |= v << (BITS_PER_BLOCK - (bits - u_bits));
		}
		pos += bits;
	}

	/// Sets the specified block within the bit set. The bitset is automatically
	/// extended to hold the data.
	///
	/// @param[in] v The data to be set.
	/// @param[in] ofs The offset in bits at which the data has to be written.
	/// @param[in] bits The number of bits of the data to be written
	///            If not all bits are being written, only the least significant bits are being
	///            taken.
	/// @note This function does not extend the data container. It is assumed, that
	///       this function runs in the context of another, which takes care of the
	///       container (e.g. set_impl). This behaviour is intentional, because
	///       this function runs potentially often, and therefore it is desired to
	///       avoid additional runtime checks which can easily be done in the calling
	///       environment.
	void set_block(block_type v, size_type ofs, size_type bits = BITS_PER_BLOCK)
	{
		size_type i = ofs / BITS_PER_BLOCK; // index of current block

		// number of bits unused within the current block
		size_type u_bits = BITS_PER_BLOCK - (ofs % BITS_PER_BLOCK);

		if (u_bits >= bits) {
			// enough room within current block
			block_type mask0 = -1;
			mask0 <<= u_bits;
			block_type mask1 = -1;
			mask1 <<= u_bits - bits;
			mask0 |= ~mask1;
			v <<= u_bits - bits;
			v &= ~mask0;
			data[i] = (data[i] & mask0) | v;
		} else {
			// not enough room, split value to current and next block
			block_type mask0 = ~((1 << (bits - u_bits)) - 1);
			block_type mask1 = (1 << (BITS_PER_BLOCK - (bits - u_bits))) - 1;

			data[i + 0] = (data[i + 0] & mask0) | v >> (bits - u_bits);
			data[i + 1] = (data[i + 1] & mask1) | v << (BITS_PER_BLOCK - (bits - u_bits));
		}
		if (ofs + bits > pos)
			pos = ofs + bits;
	}

	template <typename T>
	void set_impl(T v, size_type ofs, size_type bits = sizeof(T) * BITS_PER_BYTE)
	{
		if (bits <= 0)
			return;
		if (bits > sizeof(v) * BITS_PER_BYTE)
			throw std::invalid_argument{"number of bit exceed number of available bits"};
		if (ofs + bits > capacity())
			extend(ofs + bits - capacity());

		// fraction of the first block
		size_type u_bits = BITS_PER_BLOCK - (ofs % BITS_PER_BLOCK); // part of the first block
		if (u_bits > 0) {
			if (bits <= u_bits) {
				set_block(v, ofs, bits);
				ofs += bits;
				bits = 0;
			} else {
				set_block(v >> (bits - u_bits), ofs, u_bits);
				ofs += u_bits;
				bits -= u_bits;
			}
		}

		// all complete blocks
		for (; bits > BITS_PER_BLOCK; bits -= BITS_PER_BLOCK, ofs += BITS_PER_BLOCK) {
			set_block(v >> (bits - BITS_PER_BLOCK), ofs);
		}

		// fraction of the last block
		if (bits > 0) {
			set_block(v << (BITS_PER_BLOCK - bits), ofs);
		}
	}

	template <typename T> void set_dispatch(T v, size_type ofs, size_type bits, std::true_type)
	{
		set_impl(v, ofs, bits);
	}

	template <typename T> void set_dispatch(T v, size_type ofs, size_type bits, std::false_type)
	{
		set_impl(static_cast<typename std::underlying_type<T>::type>(v), ofs, bits);
	}

	/// Reads a block from the bit set.
	///
	/// @param[out] v The container to hold the data.
	/// @param[in] ofs The offset in bits at which the data has to be read.
	/// @param[in] bits Number of bits to be read.
	///            If the number of bits is smaller than what the specified data can
	///            hold, only the least significant bits are being set.
	/// @exception std::out_of_range There are not enough bits to read, offset and number
	///            of bits exceed the total number of available bits. It is not possible
	///            to read past the end.
	void get_block(block_type & v, size_type ofs, size_type bits = BITS_PER_BLOCK) const
	{
		if (bits <= 0)
			return;
		if (ofs + bits > size())
			throw std::out_of_range{"offset and requested bits out of range of available bits"};
		size_type i = ofs / BITS_PER_BLOCK; // index of current block

		// number of bits unused within the current block
		size_type u_bits = BITS_PER_BLOCK - (ofs % BITS_PER_BLOCK);

		if (u_bits >= bits) {
			// desired data fully within the current block
			block_type mask = (1 << u_bits) - 1;
			v = (data[i] & mask) >> (u_bits - bits);
		} else {
			// desired value is part from current block and part from next
			block_type mask0 = (1 << u_bits) - 1;
			block_type mask1 = ((1 << (BITS_PER_BLOCK - (bits - u_bits))) - 1)
				<< (bits - u_bits);
			v = (data[i + 0] & mask0) << (bits - u_bits)
				| (data[i + 1] & mask1) >> (BITS_PER_BLOCK - (bits - u_bits));
		}
	}

public:
	// ---- constructors

	/// Copy constructor
	bitset(const bitset &) = default;

	/// Move constructor.
	bitset(bitset &&) = default;

	/// Copy assignment
	bitset & operator=(const bitset &) = default;

	/// Move assignment
	bitset & operator=(bitset &&) = default;

	/// Default construction
	bitset()
		: pos(0)
	{
	}

	/// Construction with number of bits present (and usable) in the bitset.
	/// All bits are initialized to the default constructed Block type..
	///
	/// @param[in] bits Number of bits (default initialized to 0) in the bitset.
	explicit bitset(size_type bits)
		: pos(0)
	{
		extend(bits);
		pos = bits;
	}

	/// Construction with content from a specified container.
	///
	/// @param[in] begin Start position of the data (inclusive)
	/// @param[in] end End position of the data (exclusive)
	bitset(typename Container::const_iterator begin, typename Container::const_iterator end)
		: pos((end - begin) * BITS_PER_BLOCK)
		, data(begin, end)
	{
	}

	/// Construction with move of the container, this does not copy any data.
	explicit bitset(Container && container)
		: pos(container.size() * BITS_PER_BLOCK)
		, data(std::move(container))
	{
	}

	// ---- container operations

	/// Returns the capacity of this bit set. Note: not all bits must have
	/// been occupied.
	size_type capacity() const { return data.size() * BITS_PER_BLOCK; }

	/// Returns the number of used bits.
	size_type size() const { return pos; }

	/// Reserves the number of blocks within this set.
	///
	/// @note This method reserves blocks, not bits.
	void reserve(size_type blocks) { extend(blocks * BITS_PER_BLOCK); }

	/// Clears the bit set.
	void clear()
	{
		data.clear();
		pos = 0;
	}

	// ---- iterators

	/// Returns a const iterator to the beginning of the data itself.
	/// Note: this iterator accesses the data up to capacity(), some bits
	/// may be unused at the end of the set.
	data_const_iterator data_begin() const { return data.begin(); }

	/// Returns a const iterator to the end of the data itself.
	data_const_iterator data_end() const { return data.end(); }

	const_iterator begin() const { return const_iterator(this, 0); }

	const_iterator end() const { return const_iterator(this, size()); }

	// ---- append

	/// Appends another bitset to this one.
	///
	/// @param[in] bs The bitset to be appended to this one.
	///
	/// @note It is not allowed to append a bitself to itself.
	/// @note This algorithm is not efficient.
	template <class U> void append(const bitset<U> & bs)
	{
		if (reinterpret_cast<const void *>(this) == reinterpret_cast<const void *>(&bs))
			return;
		for (const auto & bit : bs)
			append(bit, 1);
	}

	/// Reads blocks from the stream and appends them to the bitset.
	///
	/// @param[in] is Stream to read block from.
	/// @param[in] blocks Number of blocks to read.
	/// @return Number of blocks read from the stream.
	size_type append(std::istream & is, size_type blocks)
	{
		size_type i = 0;
		block_type block;
		while (is.good() && !is.eof() && i < blocks) {
			is.read(reinterpret_cast<char *>(&block), sizeof(block));
			append_block(block);
			++i;
		}
		return i;
	}

	/// Appends the lowest significant bits of the specified data to the
	/// bit set. The set will be extended if necessary.
	/// The second parameter specifies the number of bits to be used from
	/// the given data, beginning at the lowest signnificant bit.
	/// A size of 0 bits will have no effect.
	///
	/// @param[in] v The value to append to the bitset.
	/// @param[in] bits Number of bits from the specified value. This must not
	///            exceed the number of bits provided by the specified data,
	///            padding is not supported.
	/// @exception std::invalid_argument Number of bites exceed the number of
	///            bit provided by the parameter v. padding is not implemented.
	///            Example: type of v is uint32_t, bits is 40.
	template <typename T> void append(T v, size_type bits = sizeof(T) * BITS_PER_BYTE)
	{
		if (bits <= 0)
			return;
		if (bits > sizeof(v) * BITS_PER_BYTE)
			throw std::invalid_argument{"number of bits exceed number of available bits"};
		size_type n_bits = bits % BITS_PER_BLOCK; // incomplete blocks
		if (n_bits != 0) {
			append_block(v >> (bits - n_bits), n_bits);
			bits -= n_bits;
		}
		for (; bits > 0; bits -= BITS_PER_BLOCK) {
			append_block(v >> (bits - BITS_PER_BLOCK));
		}
	}

	// ---- set

	/// Sets the specified bitset at the offset within this bitset.
	///
	/// @param[in] bs The bitset to copy.
	/// @param[in] ofs The offset within the bitset to copy the bitset
	///            to. The entire specified bitset will be set.
	///
	/// @note It is not allowed to set a bitself to itself.
	/// @note This algorithm is not efficient.
	template <class U> void set(const bitset<U> & bs, size_type ofs)
	{
		if (reinterpret_cast<const void *>(this) == reinterpret_cast<const void *>(&bs))
			return;
		for (const auto & bit : bs) {
			set(bit, ofs, 1);
			++ofs;
		}
	}

	/// Sets bits within the set. The bitset is automatically exteneded to hold the data.
	///
	/// @param[in] v The value to set.
	/// @param[in] ofs The offset (in bits) at which position the value has to be written.
	/// @param[in] bits The number of bits to write. This must not exceed the number of bits
	///            provided by the specified data, padding is not supported.
	/// @exception std::invalid_argument Number of bites exceed the number of
	///            bit provided by the parameter v. padding is not implemented.
	///            Example: type of v is uint32_t, bits is 40.
	template <typename T>
	void set(T v, size_type ofs, size_type bits = sizeof(T) * BITS_PER_BYTE)
	{
		set_dispatch(v, ofs, bits, std::is_integral<T>{});
	}

	/// Resets the bit at the speficied index.
	void reset(size_type index)
	{
		if (index >= size())
			throw std::out_of_range{"index out of range in reset(index)"};
		set(0, index, 1);
	}

	/// Sets all bits within the bitset to 0.
	void reset() noexcept
	{
		for (auto & block : data)
			block = 0;
	}

	/// Sets a single bit at a specified position to the specified value.
	/// This method accesses the bitset as direct as possible and therefore does not
	/// extend the set if the index is out of range.
	///
	/// @exception std::out_of_range Specified index is out of range.
	void set_bit(size_type i, bool value)
	{
		if (i >= size())
			throw std::out_of_range{"index out of range"};

		// bit within the block to be read
		size_type n_bit = BITS_PER_BLOCK - (i % BITS_PER_BLOCK) - 1;
		if (value) {
			data[i / BITS_PER_BLOCK] |= (1u << n_bit);
		} else {
			data[i / BITS_PER_BLOCK] &= ~(1u << n_bit);
		}
	}

	// ---- get

	/// Returns the bit at the specified position. If the index is larger
	/// than the actual number of bits, 'false' will rturn.
	///
	/// @exception std::out_of_range Specified index is out of range.
	bool get_bit(size_type i) const
	{
		if (i >= size())
			throw std::out_of_range{"index out of range"};

		// bit within the block to be read
		size_type n_bit = BITS_PER_BLOCK - (i % BITS_PER_BLOCK) - 1;
		return ((data[i / BITS_PER_BLOCK] >> n_bit) & 1) ? true : false;
	}

	/// Simply an other name for get_bit.
	bool test(size_type i) const { return get_bit(i); }

	/// Reads data from the bit set. There must be enough capacity in either the
	/// bitset to be read as well as the provided data type to contain the desired
	/// number of bits.
	///
	/// @param[in] ofs The offset in bits at which position the data is to be read.
	/// @param[in] bits Number of bits to be read. This must not exceeed the number of
	///            bits the specified data type can hold.
	///            If the number of bits is smaller than what the specified data can
	///            hold, only the least significant bits are being set.
	/// @return The data read from the bitset.
	/// @exception std::invalid_argument Number of bites exceed the number of
	///            bit provided by the return value. padding is not implemented.
	///            Example: return value is of type uint32_t, bits is 40.
	/// @exception std::out_of_range Offset and bits exceed the number of available
	///            bits. It is not possible to read beyond the end.
	template <class T>
	typename std::enable_if<std::is_integral<T>::value, T>::type get(
		size_type ofs, size_type bits = sizeof(T) * BITS_PER_BYTE) const
	{
		if (bits <= 0)
			return T{};
		if (bits > sizeof(T) * BITS_PER_BYTE)
			throw std::invalid_argument{"number of bits (" + std::to_string(bits)
				+ ") exceed number of available bits ("
				+ std::to_string(sizeof(T) * BITS_PER_BYTE) + ")"};
		if (ofs + bits > pos)
			throw std::out_of_range{"offset (" + std::to_string(ofs) + ") and bits ("
				+ std::to_string(bits) + ") exceed available number of bits ("
				+ std::to_string(pos) + ")"};

		T value = 0;

		// number of bits unused within the current block
		size_type u_bits = BITS_PER_BLOCK - (ofs % BITS_PER_BLOCK);

		block_type block{};

		// fraction of the first block
		if (u_bits > 0) {
			get_block(block, ofs, u_bits);
			if (bits < u_bits) {
				block >>= (u_bits - bits);
				bits = 0;
			} else {
				bits -= u_bits;
			}
			value = +block;
			ofs += u_bits;
		}

		// all complete blocks inbetween, only possible if sizeof(T) exceeds
		// the block size (mupltiple blocks in one T).
		// since this check is possible at compile time, modern compilers
		// probably will eliminated it completely.
		if (sizeof(T) * BITS_PER_BYTE > BITS_PER_BLOCK) {
			for (; bits >= BITS_PER_BLOCK; bits -= BITS_PER_BLOCK) {
				get_block(block, ofs);
				value <<= BITS_PER_BLOCK;
				value += block;
				ofs += BITS_PER_BLOCK;
			}
		}

		// fraction of the last block
		if (bits > 0) {
			get_block(block, ofs, bits);
			value <<= bits;
			value += block;
		}

		return value;
	}

	template <class T>
	typename std::enable_if<std::is_enum<T>::value, T>::type get(
		size_type ofs, size_type bits = sizeof(T) * BITS_PER_BYTE) const
	{
		return static_cast<T>(get<typename std::underlying_type<T>::type>(ofs, bits));
	}

	template <class T>
	void get(T & value, size_type ofs, size_type bits = sizeof(T) * BITS_PER_BYTE) const
	{
		value = get<T>(ofs, bits);
	}

	bool get(size_type index) const { return get<bool>(index, 1); }

	// ---- operators

	/// Returns the bit at the specified position.
	bool operator[](size_type i) const { return get_bit(i); }

	/// Comparison operator for the same bitset type.
	bool operator==(const bitset & other) const { return this == &other || data == other.data; }

	/// Comparison operator for the same bitset type.
	bool operator!=(const bitset & other) const { return !(*this == other); }

	// ---- other

	/// Flips the bit at the specified index.
	///
	/// @exception std::out_of_range Specified index is out of range.
	void flip(size_type i) { set(!get_bit(i), i, 1); }

	/// Returns true if all bits are true.
	///
	/// @note This is implemented for readablility, not max performance.
	bool all() const noexcept
	{
		for (auto i = begin(); i != end(); ++i)
			if (*i == false)
				return false;
		return true;
	}

	/// Returns true if any of the bits are true.
	///
	/// @note This is implemented for readablility, not max performance.
	bool any() const noexcept
	{
		for (auto i = begin(); i != end(); ++i)
			if (*i == true)
				return true;
		return false;
	}

	/// Returns true if none of the bits are true.
	///
	/// @note This is implemented for readablility, not max performance.
	bool none() const noexcept
	{
		for (auto i = begin(); i != end(); ++i)
			if (*i == true)
				return false;
		return true;
	}

	/// Returns the number of bits set to true.
	///
	/// @note This is implemented for readablility, not max performance.
	size_type count() const noexcept
	{
		size_type n = 0;
		for (auto i = begin(); i != end(); ++i)
			if (*i == true)
				++n;
		return n;
	}
};
}
}

#endif
