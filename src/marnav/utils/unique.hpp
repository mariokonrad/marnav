#ifndef MARNAV__UTILS__UNIQUE__HPP
#define MARNAV__UTILS__UNIQUE__HPP

#include <memory>

namespace marnav
{
namespace utils
{
/// This is part of the C++14 standard, but unfortnunately not C++11.
template <class T, class... Args> std::unique_ptr<T> make_unique(Args &&... args)
{
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
}
}

#endif
