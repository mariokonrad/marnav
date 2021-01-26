#ifndef TEST_TYPE_TRAITS_HELPER_HPP
#define TEST_TYPE_TRAITS_HELPER_HPP

#include <type_traits>
#include <gtest/gtest.h>

namespace
{
template <class T> void nmea_sentence_traits()
{
	using type = T;

	// construction

	EXPECT_TRUE(std::is_constructible<type>::value);
	// EXPECT_TRUE(std::is_trivially_constructible<type>::value);
	EXPECT_TRUE(std::is_default_constructible<type>::value);
	EXPECT_FALSE(std::is_nothrow_constructible<type>::value);
	EXPECT_TRUE(std::is_copy_constructible<type>::value);
	// EXPECT_TRUE(std::is_trivially_copy_constructible<type>::value);
	EXPECT_TRUE(std::is_move_constructible<type>::value);

	// destruction

	EXPECT_TRUE(std::is_destructible<type>::value);

	// assignable

	EXPECT_TRUE(std::is_copy_assignable<type>::value);
	EXPECT_FALSE(std::is_nothrow_copy_assignable<type>::value);
	// EXPECT_TRUE(std::is_trivially_copy_assignable<type>::value);
	EXPECT_TRUE(std::is_move_assignable<type>::value);
}
}

#endif
