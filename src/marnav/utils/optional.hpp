#ifndef __UTILS__OPTIONAL__HPP__
#define __UTILS__OPTIONAL__HPP__

#include <utility>

namespace marnav
{
namespace utils
{

/// This is a somewhat compatible implementation of std::experimental::optional (as by 2015).
/// The interface differs partially.
///
/// @note One of the main differences is: the data of the optional type is stored as member
///   data, not as pointer. This means, the disenganged state is the default constructed
///   optional type. This, of course, limits the application of this type, which is fine
///   for what it is used within this library.
///
/// This is (somewhat) necessary, because optional is not part of the standard and may change
/// its interface in the future.
template <class T> class optional
{
public:
	using value_type = T;

	// constructors

	constexpr optional()
		: flag(false)
		, data()
	{
	}

	constexpr optional(const T & data)
		: flag(true)
		, data(data)
	{
	}

	constexpr optional(T && data)
		: flag(true)
		, data(std::move(data))
	{
	}

	optional(optional &&) = default;
	optional(const optional &) = default;

	// assignment

	optional & operator=(const optional & other)
	{
		this->data = other.data;
		this->flag = other.flag;
		return *this;
	}

	optional & operator=(optional && other)
	{
		this->data = std::move(other.data);
		this->flag = std::move(other.flag);
		return *this;
	}

	template <class U> optional & operator=(U && data)
	{
		this->data = std::move(data);
		flag = true;
		return *this;
	}

	// observers

	constexpr const T * operator->() const { return &data; }
	T * operator->() { return &data; }
	constexpr const T & operator*() const { return data; }
	T & operator*() { return data; }

	bool available() const { return flag; }
	constexpr explicit operator bool() const { return flag; }

	constexpr const T & value() const & { return data; }
	T & value() & { return data; }
	T && value() && { return data; }

	template <class U> constexpr T value_or(U && value) const &
	{
		this->data = std::move(value);
		flag = true;
	}

	template <class U> T value_or(U && value) &&
	{
		this->data = std::move(value);
		flag = true;
	}

	// other

	void reset()
	{
		data = T{};
		flag = false;
	}

private:
	bool flag;
	T data;
};
}
}

#endif
