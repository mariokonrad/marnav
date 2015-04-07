#include <gtest/gtest.h>
#include <nmea/date.hpp>

namespace
{

using namespace marnav;

class Test_nmea_date : public ::testing::Test
{
};

TEST_F(Test_nmea_date, is_leap_year)
{
	EXPECT_TRUE(nmea::date::is_leap_year(1980));
	EXPECT_FALSE(nmea::date::is_leap_year(1981));
	EXPECT_FALSE(nmea::date::is_leap_year(1982));
	EXPECT_FALSE(nmea::date::is_leap_year(1983));
	EXPECT_TRUE(nmea::date::is_leap_year(1984));
	EXPECT_FALSE(nmea::date::is_leap_year(1985));
	EXPECT_FALSE(nmea::date::is_leap_year(1986));
	EXPECT_FALSE(nmea::date::is_leap_year(1987));
	EXPECT_TRUE(nmea::date::is_leap_year(1988));
	EXPECT_FALSE(nmea::date::is_leap_year(1989));
	EXPECT_FALSE(nmea::date::is_leap_year(1990));
	EXPECT_FALSE(nmea::date::is_leap_year(1991));
	EXPECT_TRUE(nmea::date::is_leap_year(1992));
	EXPECT_FALSE(nmea::date::is_leap_year(1993));
	EXPECT_FALSE(nmea::date::is_leap_year(1994));
	EXPECT_FALSE(nmea::date::is_leap_year(1995));
	EXPECT_TRUE(nmea::date::is_leap_year(1996));
	EXPECT_FALSE(nmea::date::is_leap_year(1997));
	EXPECT_FALSE(nmea::date::is_leap_year(1998));
	EXPECT_FALSE(nmea::date::is_leap_year(1999));
	EXPECT_TRUE(nmea::date::is_leap_year(2000));
	EXPECT_FALSE(nmea::date::is_leap_year(2001));
	EXPECT_FALSE(nmea::date::is_leap_year(2002));
	EXPECT_FALSE(nmea::date::is_leap_year(2003));
	EXPECT_TRUE(nmea::date::is_leap_year(2004));
	EXPECT_FALSE(nmea::date::is_leap_year(2005));
	EXPECT_FALSE(nmea::date::is_leap_year(2006));
	EXPECT_FALSE(nmea::date::is_leap_year(2007));
	EXPECT_TRUE(nmea::date::is_leap_year(2008));
	EXPECT_FALSE(nmea::date::is_leap_year(2009));
	EXPECT_FALSE(nmea::date::is_leap_year(2010));
	EXPECT_FALSE(nmea::date::is_leap_year(2011));
	EXPECT_TRUE(nmea::date::is_leap_year(2012));
	EXPECT_FALSE(nmea::date::is_leap_year(2013));
	EXPECT_FALSE(nmea::date::is_leap_year(2014));
	EXPECT_FALSE(nmea::date::is_leap_year(2015));
	EXPECT_TRUE(nmea::date::is_leap_year(2016));
	EXPECT_FALSE(nmea::date::is_leap_year(2017));
	EXPECT_FALSE(nmea::date::is_leap_year(2018));
	EXPECT_FALSE(nmea::date::is_leap_year(2019));
	EXPECT_TRUE(nmea::date::is_leap_year(2020));
	EXPECT_FALSE(nmea::date::is_leap_year(2021));
	EXPECT_FALSE(nmea::date::is_leap_year(2022));
	EXPECT_FALSE(nmea::date::is_leap_year(2023));
	EXPECT_TRUE(nmea::date::is_leap_year(2024));
	EXPECT_FALSE(nmea::date::is_leap_year(2025));
	EXPECT_FALSE(nmea::date::is_leap_year(2026));
	EXPECT_FALSE(nmea::date::is_leap_year(2027));
	EXPECT_TRUE(nmea::date::is_leap_year(2028));
	EXPECT_FALSE(nmea::date::is_leap_year(2029));
	EXPECT_FALSE(nmea::date::is_leap_year(2030));

	EXPECT_FALSE(nmea::date::is_leap_year(2100));
	EXPECT_FALSE(nmea::date::is_leap_year(2200));
	EXPECT_FALSE(nmea::date::is_leap_year(2300));
	EXPECT_TRUE(nmea::date::is_leap_year(2400));
}
}
