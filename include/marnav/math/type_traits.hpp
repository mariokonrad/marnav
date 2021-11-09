#ifndef MARNAV_MATH_TYPE_TRAITS_HPP
#define MARNAV_MATH_TYPE_TRAITS_HPP

#include <type_traits>

namespace marnav
{
namespace math
{
// compatiblity to C++17
template <typename...>
struct conjunction : std::true_type {
};

template <typename T>
struct conjunction<T> : T {
};

template <typename T1, typename... Tn>
struct conjunction<T1, Tn...> : std::conditional<T1::value, conjunction<Tn...>, T1>::type {
};

// inspired by https://www.fluentcpp.com/2019/01/29/how-to-define-a-variadic-number-of-arguments-of-the-same-type-part-2/
template <typename T, typename... Args>
using all_same_type = typename conjunction<std::is_same<Args, T>...>::type;
}
}

#endif
