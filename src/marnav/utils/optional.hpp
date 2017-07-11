#ifndef MARNAV__UTILS__OPTIONAL__HPP
#define MARNAV__UTILS__OPTIONAL__HPP

#include <utility>

namespace marnav
{
namespace utils
{
/// @brief Carries an optional value.
///
/// This is a somewhat compatible implementation of std::experimental::optional (as by 2015).
/// The interface differs partially.
///
/// @tparam T Data type to be held by the optional.
///
/// @note One of the main differences is: the data of the optional type is stored as member
///   data, not as pointer. This means, the disenganged state is the default constructed
///   optional type. This, of course, limits the application of this type, which is fine
///   for what it is used within this library.
///
/// This is (somewhat) necessary, because optional is not part of the standard and may change
/// its interface in the future.
///
template <class T> class optional
{
public:
	using value_type = T;

	// constructors

	/// Initializes the optional with the default constructed data.
	constexpr optional() noexcept
		: flag_(false)
		, data_()
	{
	}

	constexpr optional(const T & data)
		: flag_(true)
		, data_(data)
	{
	}

	constexpr optional(T && data) noexcept
		: flag_(true)
		, data_(std::move(data))
	{
	}

	optional(const optional & other) noexcept
		: flag_(other.flag_)
		, data_(other.data_)
	{
	}

	optional(optional && other) noexcept
		: flag_(std::move(other.flag_))
		, data_(std::move(other.data_))
	{
	}

	// assignment

	optional & operator=(const optional & other) noexcept
	{
		this->data_ = other.data_;
		this->flag_ = other.flag_;
		return *this;
	}

	optional & operator=(optional && other) noexcept
	{
		this->data_ = std::move(other.data_);
		this->flag_ = std::move(other.flag_);
		return *this;
	}

	template <class U> optional & operator=(U && data)
	{
		this->data_ = std::move(data);
		flag_ = true;
		return *this;
	}

	// observers

	constexpr const T * operator->() const { return &data_; }

	T * operator->() { return &data_; }

	constexpr const T & operator*() const { return data_; }

	T & operator*() { return data_; }

	bool available() const { return flag_; }

	constexpr explicit operator bool() const { return flag_; }

	constexpr bool has_value() const { return flag_; }

	constexpr const T & value() const & { return data_; }

	T & value() & { return data_; }

	T && value() && { return data_; }

	/* disabling c++14 extensions for now
	template <class U> constexpr T value_or(U && value) const &
	{
		if (available())
			return data;
		return value;
	}

	template <class U> T value_or(U && value) &&
	{
		if (available())
			return data;
		return value;
	}
	*/

	// other

	/// Resets the data to the default constructed value and marks
	/// the optional as 'not set'.
	void reset()
	{
		data_ = T{};
		flag_ = false;
	}

private:
	bool flag_;
	T data_;
};

/// @brief Creates and returns an optioal of type T, initialized with the specified
/// arguments.
///
/// @tparam T The optional type
/// @tparam Args Types of arguments to initialize the value
/// @param[in] args The arguments to initialize the value
/// @return the optional of type T
template <class T, class... Args> optional<T> make_optional(Args &&... args)
{
	return optional<T>(T{std::forward<Args>(args)...});
}

/// @brief Creates and returns an optioal of type T, representing a non-carrying
/// optional.
///
/// @tparam T The optional type
/// @return the optional of type T
template <class T> optional<T> make_optional()
{
	return optional<T>();
}
}
}

#endif
