#ifndef MARNAV__UTILS__BITSET__HPP
#define MARNAV__UTILS__BITSET__HPP

/// Copyright (c) 2017 Mario Konrad <mario.konrad@gmx.net>
/// The code is licensed under the BSD License (see file LICENSE)

#include <limits>
#include <stdexcept>
#include <type_traits>
#include <vector>
#include <cassert>

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
/// bitset<uint8_t> bits(1024);
/// bits.set(1, 512, 1); // set one bit to 1 at offset 512
/// @endcode
///
template <class Block,
	class = typename std::enable_if<!std::numeric_limits<Block>::is_signed>::type>
class bitset
{
public:
	using block_type = Block;

	/// It is assumed, that a byte has 8 bits. This template will
	/// not work on other architectures.
	static constexpr auto bits_per_byte = 8u;

	static constexpr auto bits_per_block = sizeof(block_type) * bits_per_byte;

public:
	using container = std::vector<block_type>;
	using size_type = typename container::size_type;
	using data_const_iterator = typename container::const_iterator;

	/// This is a non-std conform const iterator. The intention is
	/// to provide a basic iterator functionality without claiming
	/// to be std compliant.
	class const_iterator
	{
		friend class bitset;

	public:
		using difference_type = long long;
		using value_type = bool;
		using iterator_category = std::random_access_iterator_tag;

	private:
		const bitset * bs; ///< Associated bitset.
		size_type pos; ///< Position (bit) within the bitset.

	private:
		const_iterator(const bitset * const b, size_type p)
			: bs(b)
			, pos(p)
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

		bool operator==(const const_iterator & other) const noexcept
		{
			return bs == other.bs && pos == other.pos;
		}

		bool operator!=(const const_iterator & other) const noexcept
		{
			return bs != other.bs || pos != other.pos;
		}

		bool operator<(const const_iterator & other) const noexcept
		{
			return bs == other.bs && pos < other.pos;
		}

		bool operator>(const const_iterator & other) const noexcept
		{
			return bs == other.bs && pos > other.pos;
		}

		bool operator<=(const const_iterator & other) const noexcept
		{
			return bs == other.bs && pos <= other.pos;
		}

		bool operator>=(const const_iterator & other) const noexcept
		{
			return bs == other.bs && pos >= other.pos;
		}

		bool operator*() const
		{
			return bs != nullptr && pos < bs->size() && bs->get_bit(pos) == true;
		}

		const_iterator operator+(size_type n) const noexcept
		{
			return const_iterator{*this} += n;
		}

		const_iterator operator-(size_type n) const noexcept
		{
			return const_iterator{*this} -= n;
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

		/// Peeks from the bitset, but does not advance the iterator.
		template <typename T> void peek(T & v, size_type bits = sizeof(T) * bits_per_byte) const
		{
			if (bs == nullptr)
				return;
			if (pos + bits > bs->size())
				throw std::out_of_range{
					"out of range, not possible to peek beyond available bits"};
			bs->get(v, pos, bits);
		}

		/// Reads from the bitset and advances the iterator the number of read bits.
		template <typename T> void read(T & v, size_type bits = sizeof(T) * bits_per_byte)
		{
			peek(v, bits);
			*this += bits;
		}
	};

private:
	size_type pos; // number of bits contained within the set
	container data;

private:
	/// Extends the container by the specified number of bits.
	/// Extension is always one block.
	void extend(size_type bits)
	{
		assert(bits > 0);
		size_type n_blocks = (pos + bits + bits_per_block - 1) / bits_per_block;
		if (n_blocks > data.size()) {
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
	///            between 0 and bits_per_block. If not all bits are being
	///            appended, only the least significant bits are being taken.
	void append_block(block_type v, size_type bits = bits_per_block)
	{
		assert(bits > 0);
		extend(bits);
		size_type i = pos / bits_per_block; // index of current block

		// number of bits unused within the current block
		size_type u_bits = bits_per_block - (pos % bits_per_block);

		if (u_bits >= bits) {
			// enough room within current block
			data[i] |= v << (u_bits - bits);
		} else {
			// not enough room, split value to current and next block
			data[i + 0] |= v >> (bits - u_bits);
			data[i + 1] |= v << (bits_per_block - (bits - u_bits));
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
	void set_block(block_type v, size_type ofs, size_type bits = bits_per_block)
	{
		size_type i = ofs / bits_per_block; // index of current block

		// number of bits unused within the current block
		size_type u_bits = bits_per_block - (ofs % bits_per_block);

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
			block_type mask1 = (1 << (bits_per_block - (bits - u_bits))) - 1;

			data[i + 0] = (data[i + 0] & mask0) | v >> (bits - u_bits);
			data[i + 1] = (data[i + 1] & mask1) | v << (bits_per_block - (bits - u_bits));
		}
		if (ofs + bits > pos)
			pos = ofs + bits;
	}

	template <typename T>
	void set_impl(T v, size_type ofs, size_type bits = sizeof(T) * bits_per_byte)
	{
		assert(bits > 0);
		if (bits > sizeof(v) * bits_per_byte)
			throw std::invalid_argument{"number of bit exceed number of available bits"};
		if (ofs + bits > capacity())
			extend(ofs + bits - capacity());

		// fraction of the first block
		size_type u_bits = bits_per_block - (ofs % bits_per_block); // part of the first block
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
		for (; bits > bits_per_block; bits -= bits_per_block, ofs += bits_per_block) {
			set_block(v >> (bits - bits_per_block), ofs);
		}

		// fraction of the last block
		if (bits > 0) {
			set_block(v << (bits_per_block - bits), ofs);
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
	/// @return    The container to hold the data.
	/// @param[in] ofs The offset in bits at which the data has to be read.
	/// @param[in] bits Number of bits to be read.
	///            If the number of bits is smaller than what the specified data can
	///            hold, only the least significant bits are being set.
	/// @exception std::out_of_range There are not enough bits to read, offset and number
	///            of bits exceed the total number of available bits. It is not possible
	///            to read past the end.
	block_type get_block(size_type ofs, size_type bits = bits_per_block) const noexcept
	{
		assert(bits > 0);
		const size_type i = ofs / bits_per_block; // index of current block

		// number of bits unused within the current block
		const size_type u_bits = bits_per_block - (ofs % bits_per_block);

		if (u_bits >= bits) {
			// desired data fully within the current block
			block_type mask = (1 << u_bits) - 1;
			return (data[i] & mask) >> (u_bits - bits);
		} else {
			// desired value is part from current block and part from next
			block_type mask0 = (1 << u_bits) - 1;
			block_type mask1 = ((1 << (bits_per_block - (bits - u_bits))) - 1)
				<< (bits - u_bits);
			return (data[i + 0] & mask0) << (bits - u_bits)
				| (data[i + 1] & mask1) >> (bits_per_block - (bits - u_bits));
		}
	}

	/// Copies a block from source to destination offsets.
	///
	/// This is the equivalent of `set_block(get_block(...), ...)`
	void copy_block(size_type r_ofs, size_type w_ofs, size_type bits = bits_per_block)
	{
		set_block(get_block(r_ofs, bits), w_ofs, bits);
	}

public: // constructors
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
	bitset(typename container::const_iterator begin, typename container::const_iterator end)
		: pos((end - begin) * bits_per_block)
		, data(begin, end)
	{
	}

	/// Construction with move of the container, this does not copy any data.
	explicit bitset(container && container)
		: pos(container.size() * bits_per_block)
		, data(std::move(container))
	{
	}

	/// Constructs a bitset from the specified range.
	///
	/// It tries to copy blockwise.
	bitset(const_iterator first, const_iterator last)
		: pos(0)
	{
		if (last <= first)
			return;
		if (!first.bs)
			return;

		const size_type distance = last.pos - first.pos;
		const size_type n_blocks = distance / bits_per_block;
		const size_type u_bits = distance % bits_per_block;

		if (u_bits > 0) {
			data.reserve(n_blocks + 1);
		} else {
			data.reserve(n_blocks);
		}

		size_type r_ofs = first.pos;
		for (size_type i = 0; i < n_blocks; ++i, r_ofs += bits_per_block)
			data.push_back(first.bs->get_block(r_ofs, bits_per_block));
		pos = n_blocks * bits_per_block;

		if (u_bits > 0)
			append(first.bs->get_block(r_ofs, u_bits), u_bits);
	}

	/// Constructs a bitset using the provided blocks.
	bitset(std::initializer_list<Block> init_list)
		: pos(0)
	{
		data.assign(init_list);
		pos = data.size() * bits_per_block;
	}

public: // container operations
	/// Returns the capacity of this bit set. Note: not all bits must have
	/// been occupied.
	size_type capacity() const noexcept { return data.size() * bits_per_block; }

	/// Returns the number of used bits.
	size_type size() const noexcept { return pos; }

	/// Reserves the number of blocks within this set.
	///
	/// @note This method reserves blocks, not bits.
	void reserve(size_type blocks) { extend(blocks * bits_per_block); }

	/// Clears the bit set.
	void clear()
	{
		data.clear();
		pos = 0;
	}

public: // iterators
	/// Returns a const iterator to the beginning of the data itself.
	/// Note: this iterator accesses the data up to capacity(), some bits
	/// may be unused at the end of the set.
	data_const_iterator data_begin() const { return data.begin(); }

	/// Returns a const iterator to the end of the data itself.
	data_const_iterator data_end() const { return data.end(); }

	const_iterator begin() const { return const_iterator(this, 0); }

	const_iterator end() const { return const_iterator(this, size()); }

	const_iterator cbegin() const { return const_iterator(this, 0); }

	const_iterator cend() const { return const_iterator(this, size()); }

public: // append
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
	template <typename T> void append(T v, size_type bits = sizeof(T) * bits_per_byte)
	{
		if (bits <= 0)
			return;
		if (bits > sizeof(v) * bits_per_byte)
			throw std::invalid_argument{"number of bits exceed number of available bits"};
		size_type n_bits = bits % bits_per_block; // incomplete blocks
		if (n_bits != 0) {
			append_block(v >> (bits - n_bits), n_bits);
			bits -= n_bits;
		}
		for (; bits > 0; bits -= bits_per_block) {
			append_block(v >> (bits - bits_per_block));
		}
	}

public: // set
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
	void set(T v, size_type ofs, size_type bits = sizeof(T) * bits_per_byte)
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
		size_type n_bit = bits_per_block - (i % bits_per_block) - 1;
		if (value) {
			data[i / bits_per_block] |= (1u << n_bit);
		} else {
			data[i / bits_per_block] &= ~(1u << n_bit);
		}
	}

public: // get
	/// Returns the bit at the specified position. If the index is larger
	/// than the actual number of bits, 'false' will rturn.
	///
	/// @exception std::out_of_range Specified index is out of range.
	bool get_bit(size_type i) const
	{
		if (i >= size())
			throw std::out_of_range{"index out of range"};

		// bit within the block to be read
		size_type n_bit = bits_per_block - (i % bits_per_block) - 1;
		return ((data[i / bits_per_block] >> n_bit) & 1) ? true : false;
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
	typename std::enable_if<std::is_integral<T>::value && !std::is_same<T, bool>::value,
		T>::type
	get(size_type ofs, size_type bits = sizeof(T) * bits_per_byte) const
	{
		if (bits <= 0)
			return T{};
		if (bits > sizeof(T) * bits_per_byte)
			throw std::invalid_argument{"number of bits (" + std::to_string(bits)
				+ ") exceed number of available bits ("
				+ std::to_string(sizeof(T) * bits_per_byte) + ")"};
		if (ofs + bits > pos)
			throw std::out_of_range{"offset (" + std::to_string(ofs) + ") and bits ("
				+ std::to_string(bits) + ") exceed available number of bits ("
				+ std::to_string(pos) + ")"};

		T value = 0;

		// number of bits unused within the current block
		size_type u_bits = bits_per_block - (ofs % bits_per_block);

		// fraction of the first block
		if (u_bits > 0) {
			auto block = get_block(ofs, u_bits);
			if (bits < u_bits) {
				block >>= (u_bits - bits);
				bits = 0;
			} else {
				bits -= u_bits;
			}
			value += block;
			ofs += u_bits;
		}

		// all complete blocks inbetween, only possible if sizeof(T) exceeds
		// the block size (mupltiple blocks in one T).
		// since this check is possible at compile time, modern compilers
		// probably will eliminated it completely.
		if (sizeof(T) * bits_per_byte > bits_per_block) {
			for (; bits >= bits_per_block; bits -= bits_per_block) {
				value <<= bits_per_block;
				value += get_block(ofs);
				ofs += bits_per_block;
			}
		}

		// fraction of the last block
		if (bits > 0) {
			value <<= bits;
			value += get_block(ofs, bits);
		}

		return value;
	}

	/// Specialization of `get` for enumerations.
	template <class T>
	typename std::enable_if<std::is_enum<T>::value, T>::type get(
		size_type ofs, size_type bits = sizeof(T) * bits_per_byte) const
	{
		return static_cast<T>(get<typename std::underlying_type<T>::type>(ofs, bits));
	}

	/// Specialization of `get` for bool.
	template <class T, typename std::enable_if<std::is_same<T, bool>::value, int>::type = 0>
	void get(T & value, size_type ofs, size_type = 1) const
	{
		value = get_bit(ofs);
	}

	template <class T, typename std::enable_if<!std::is_same<T, bool>::value, int>::type = 0>
	void get(T & value, size_type ofs, size_type bits = sizeof(T) * bits_per_byte) const
	{
		value = get<T>(ofs, bits);
	}

	bool get(size_type ofs) const { return get_bit(ofs); }

public: // access operators
	/// Returns the bit at the specified position.
	bool operator[](size_type i) const { return get_bit(i); }

public: // comparison operators
	/// Equality comparison operator for the same bitset type.
	bool operator==(const bitset & other) const { return this == &other || data == other.data; }

	/// Inequality comparison operator for the same bitset type.
	bool operator!=(const bitset & other) const { return !(*this == other); }

	/// Equalily comparison operator for different bitset types.
	///
	/// Since the blocks differ, a comparison bit by bit is done.
	///
	/// @note This is implemented for readablility, not max performance.
	template <class XBlock,
		class = typename std::enable_if<!std::numeric_limits<XBlock>::is_signed>::type>
	bool operator==(const bitset<XBlock> & other) const
	{
		if (size() != other.size())
			return false;

		auto i = begin();
		auto j = other.begin();
		while (i != end()) {
			if (*i != *j)
				return false;
			++i;
			++j;
		}
		return true;
	}

	/// Inequality comparison operator for different bitset types.
	///
	/// Since the blocks differ, a comparison bit by bit is done.
	///
	/// @note This is implemented for readablility, not max performance.
	template <class XBlock,
		class = typename std::enable_if<!std::numeric_limits<XBlock>::is_signed>::type>
	bool operator!=(const bitset<XBlock> & other) const
	{
		return !(*this == other);
	}

	/// Comparinson for 'less'.
	bool operator<(const bitset & other) const
	{
		// are there any bits in the range of one bitset that exceeds the other
		if (size() > other.size()) {
			if (any(begin() + (size() - other.size()), end()))
				return false;
		} else if (other.size() > size()) {
			if (other.any(other.begin() + (other.size() - size()), other.end()))
				return true;
		}

		// check all blocks from the most to the least significant.
		for (auto i = size() / bits_per_block; i > 0; --i) {
			if (data[i - 1] < other.data[i - 1])
				return true;
		}

		// no difference found, they are the same
		return false;
	}

	/// Comparinson for 'less or equal'.
	bool operator<=(const bitset & other) const
	{
		// are there any bits in the range of one bitset that exceeds the other
		if (size() > other.size()) {
			if (any(begin() + (size() - other.size()), end()))
				return false;
		} else if (other.size() > size()) {
			if (other.any(other.begin() + (other.size() - size()), other.end()))
				return true;
		}

		// check all blocks from the most to the least significant.
		for (auto i = size() / bits_per_block; i > 0; --i) {
			if (data[i - 1] > other.data[i - 1])
				return false;
		}

		// no difference found, they are the same
		return true;
	}

	/// Comparinson for 'greater'.
	bool operator>(const bitset & other) const { return !(*this <= other); }

	/// Comparinson for 'greater or equal'.
	bool operator>=(const bitset & other) const { return !(*this < other); }

public: // arithmetic operators
	/// Increments the bitset by one. If an overflow is to occurr, the bitset
	/// resets to 0 and continues counting.
	bitset & operator++() // ++bitset
	{
		if (size() <= 0)
			return *this;

		const size_type u_bits = size() % bits_per_block;

		// parts of a block
		if (u_bits > 0) {
			size_type ofs = bits_per_block * (size() / bits_per_block);

			block_type block = get_block(ofs, u_bits);

			if (block < ((block_type{1} << u_bits) - 1)) {
				++block;
				set_block(block, ofs, u_bits);
				return *this;
			}
			block = block_type{}; // maximum reached, overflow to the next block
			set_block(block, ofs, u_bits);
		}

		// full blocks
		for (size_type i = size() / bits_per_block; i > 0; --i) {
			if (data[i - 1] < std::numeric_limits<block_type>::max()) {
				++data[i - 1];
				return *this;
			}
			data[i - 1] = block_type{};
		}

		return *this;
	}

	bitset operator++(int) // bitset++
	{
		bitset result{*this};
		++(*this);
		return result;
	}

	/// Decrements the bitset by one. If an underflow is to occurr, the bitset
	/// resets to all 1es and continues counting.
	bitset & operator--() // --bitset
	{
		if (size() <= 0)
			return *this;

		const size_type u_bits = size() % bits_per_block;

		// parts of a block
		if (u_bits > 0) {
			size_type ofs = bits_per_block * (size() / bits_per_block);

			block_type block = get_block(ofs, u_bits);

			if (block > 0) {
				--block;
				set_block(block, ofs, u_bits);
				return *this;
			}
			block = (block_type{1} << u_bits) - 1; // max reached, overflow to the next block
			set_block(block, ofs, u_bits);
		}

		// full blocks
		for (size_type i = size() / bits_per_block; i > 0; --i) {
			if (data[i - 1] > 0) {
				--data[i - 1];
				return *this;
			}
			data[i - 1] = std::numeric_limits<block_type>::max();
		}

		return *this;
	}

	bitset operator--(int) // bitset--
	{
		bitset result{*this};
		--(*this);
		return result;
	}

public: // shift operator
	/// Bit shift left. This function tries to shift entire blocks at once.
	bitset & shl(size_type bits)
	{
		if (bits >= size()) {
			reset();
			return *this;
		}

		// copy all bits necessary, block wise.
		size_type r_ofs = bits;
		size_type w_ofs = 0;
		while (r_ofs < size()) {

			// this resembles std::min, but std::min complains about
			// bits_per_block being an undefined reference.
			const size_type d = size() - r_ofs;
			size_type u_bits = d < bits_per_block ? d : bits_per_block;

			copy_block(r_ofs, w_ofs, u_bits);
			r_ofs += u_bits;
			w_ofs += u_bits;
		}

		// overwrite all remaining bits with zeroes.
		while (w_ofs < size()) {

			// same issue with std::min here.
			const size_type d = size() - w_ofs;
			size_type u_bits = d < bits_per_block ? d : bits_per_block;

			set_block(0, w_ofs, u_bits);
			w_ofs += bits_per_block;
		}

		return *this;
	}

	bitset & operator<<=(size_type bits) { return shl(bits); }

	bitset operator<<(size_type bits) const { return bitset{*this} <<= bits; }

	/// Bit shift right. This function tries to shift entire blocks
	/// at once.
	bitset & shr(size_type bits)
	{
		if (bits >= size()) {
			reset();
			return *this;
		}

		size_type r_ofs = 0;
		size_type w_ofs = 0;

		// first: handle the last bits (probably partially a block, or a single block)
		size_type u_bits = size() % bits_per_block;
		if (u_bits > 0) {
			if (u_bits == size()) {
				u_bits = size() - bits;
				r_ofs = 0;
				w_ofs = bits;
			} else {
				r_ofs = size() - u_bits - bits;
				w_ofs = size() - u_bits;
			}
		} else {
			if (size() == bits_per_block) {
				u_bits = bits_per_block - bits;
				r_ofs = 0;
				w_ofs = bits;
			} else {
				u_bits = bits_per_block;
				r_ofs = size() - bits_per_block - bits;
				w_ofs = size() - bits_per_block;
			}
		}
		copy_block(r_ofs, w_ofs, u_bits);

		// second: handle whole blocks
		while (r_ofs > 0) {
			if (r_ofs > bits_per_block) {
				u_bits = bits_per_block;
				r_ofs -= bits_per_block;
				w_ofs -= bits_per_block;
			} else {
				u_bits = r_ofs;
				r_ofs = 0;
				w_ofs -= u_bits;
			}
			copy_block(r_ofs, w_ofs, u_bits);
		}

		// third: reset all bits remaining in front
		while (w_ofs > 0) {
			u_bits = (w_ofs < bits_per_block) ? w_ofs : bits_per_block;
			w_ofs -= u_bits;
			set_block(0, w_ofs, u_bits);
		}

		return *this;
	}

	bitset & operator>>=(size_type bits) { return shr(bits); }

	bitset operator>>(size_type bits) const { return bitset{*this} >>= bits; }

public: // logic operator
	/// Logical or operation. The resulting bitset is of the size of the larger one.
	///
	/// Example: '0011' | '11000' = '11110'
	bitset & operator|=(const bitset & other)
	{
		if (size() < other.size()) {
			extend(other.size() - size());
			pos = other.size();
		}

		for (auto i = 0u; i < data.size(); ++i)
			data[i] |= other.data[i];

		return *this;
	}

	bitset operator|(const bitset & other) const { return bitset{*this} |= other; }

	/// Logical or operation. The resulting bitset is of the size of the smaller one.
	///
	/// Example: '0111' & '11001' = '0100'
	bitset & operator&=(const bitset & other)
	{
		if (size() > other.size()) {
			for (auto i = other.size(); i < size(); ++i)
				reset(i);
			pos = other.size();
		}

		for (auto i = 0u; i < data.size(); ++i)
			data[i] &= other.data[i];

		return *this;
	}

	bitset operator&(const bitset & other) const { return bitset{*this} &= other; }

	/// Logical xor operation. The resulting bitset is of the size of the larger one.
	///
	/// Example: '0011' ^ '11100' = '11011'
	bitset & operator^=(const bitset & other)
	{
		if (size() < other.size()) {
			extend(other.size() - size());
			pos = other.size();
		}

		for (auto i = 0u; i < data.size(); ++i)
			data[i] ^= other.data[i];

		return *this;
	}

	bitset operator^(const bitset & other) const { return bitset{*this} ^= other; }

public: // other
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
	bool any() const noexcept { return any(begin(), end()); }

	/// Returns true if any of the bits in the specified range are true.
	///
	/// @note This is implemented for readablility, not max performance.
	bool any(const_iterator first, const_iterator last) const noexcept
	{
		for (auto i = first; i != last; ++i)
			if (*i == true)
				return true;
		return false;
	}

	/// Returns true if none of the bits are true.
	///
	/// @note This is implemented for readablility, not max performance.
	bool none() const noexcept { return none(begin(), end()); }

	/// Returns true if none of the bits within the specified range are true.
	///
	/// @note This is implemented for readablility, not max performance.
	bool none(const_iterator first, const_iterator last) const noexcept
	{
		for (auto i = first; i != last; ++i)
			if (*i == true)
				return false;
		return true;
	}

	/// Returns the number of bits set to true.
	///
	/// @note This is implemented for readablility, not max performance.
	size_type count() const noexcept { return count(begin(), end()); }

	/// Returns the number of bits between the specified iterators.
	///
	/// @param[in] first Ponints to the first bit of the range to test.
	/// @param[in] last Ponits to the bit after the range.
	///
	/// @note This is implemented for readablility, not max performance.
	size_type count(const_iterator first, const_iterator last) const noexcept
	{
		size_type n = 0;
		for (auto i = first; i != last; ++i)
			if (*i == true)
				++n;
		return n;
	}
};
}
}

#endif
