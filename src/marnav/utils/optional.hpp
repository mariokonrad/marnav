#ifndef __UTILS__OPTIONAL__HPP__
#define __UTILS__OPTIONAL__HPP__

namespace marnav
{
namespace utils
{

/// This is a somewhat compatible implementation of std::experimental::optional (as by 2015).
/// The interface differs partially.
///
/// This is (somewhat) necessary, because optional is not part of the standard and may change
/// its interface in the future.
template <class T> class optional
{
public:
	using value_type = T;

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

	void reset()
	{
		data = T{};
		flag = false;
	}

	bool available() const { return flag; }
	explicit operator bool() const { return flag; }

	constexpr const T & value() const { return data; }
	T & value() { return data; }

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

	constexpr const T * operator->() const { return &data; }
	T * operator->() { return &data; }
	constexpr const T & operator*() const { return data; }
	T & operator*() { return data; }

private:
	bool flag;
	T data;
};
}
}

#endif
