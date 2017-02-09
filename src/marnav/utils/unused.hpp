#ifndef MARNAV__UTILS__UNUSED__HPP
#define MARNAV__UTILS__UNUSED__HPP

namespace marnav
{
namespace utils
{
/// Swallows everything thrown into it. Used to prevent the compiler
/// complain about unused parameters like this:
///
/// @code
/// int foo(int a, int b, int c)
/// {
///     unused(c);
///     return a + b;
/// }
/// @endcode
///
/// Why is this good:
/// - Omitting `c` will cause problems with doxygen not having a parameter
///   to describe or clang-tidy complaining about readability.
/// - Providing `c` but not using it causes the compiler to complain about
///   unused prameter.
/// - Macros are fugly.
///
/// Because of the parameter pack, it is also possible to specify
/// multiple arguments:
///
/// @code
/// int foo(int a, int b, int c, int d)
/// {
///     unused(c, d);
///     return a + b;
/// }
/// @endcode
///
/// @note This results in not being code in the binary.
///
template <typename... Args> void unused(Args &&...)
{
}
}
}

#endif
