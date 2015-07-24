#include <gtest/gtest.h>
#include <marnav/nmea/date.hpp>
#include <sstream>

namespace
{

using namespace marnav;

class Test_nmea_date : public ::testing::Test
{
};

TEST_F(Test_nmea_date, invalid_day)
{
	EXPECT_ANY_THROW(nmea::date(2012, nmea::month::january,   32));
	EXPECT_ANY_THROW(nmea::date(2012, nmea::month::february,  30));
	EXPECT_ANY_THROW(nmea::date(2012, nmea::month::march,     32));
	EXPECT_ANY_THROW(nmea::date(2012, nmea::month::april,     31));
	EXPECT_ANY_THROW(nmea::date(2012, nmea::month::may,       32));
	EXPECT_ANY_THROW(nmea::date(2012, nmea::month::june,      31));
	EXPECT_ANY_THROW(nmea::date(2012, nmea::month::july,      32));
	EXPECT_ANY_THROW(nmea::date(2012, nmea::month::august,    32));
	EXPECT_ANY_THROW(nmea::date(2012, nmea::month::september, 31));
	EXPECT_ANY_THROW(nmea::date(2012, nmea::month::october,   32));
	EXPECT_ANY_THROW(nmea::date(2012, nmea::month::november,  31));
	EXPECT_ANY_THROW(nmea::date(2012, nmea::month::december,  32));

	EXPECT_ANY_THROW(nmea::date(2012, nmea::month::january,   0));
	EXPECT_ANY_THROW(nmea::date(2012, nmea::month::february,  0));
	EXPECT_ANY_THROW(nmea::date(2012, nmea::month::march,     0));
	EXPECT_ANY_THROW(nmea::date(2012, nmea::month::april,     0));
	EXPECT_ANY_THROW(nmea::date(2012, nmea::month::may,       0));
	EXPECT_ANY_THROW(nmea::date(2012, nmea::month::june,      0));
	EXPECT_ANY_THROW(nmea::date(2012, nmea::month::july,      0));
	EXPECT_ANY_THROW(nmea::date(2012, nmea::month::august,    0));
	EXPECT_ANY_THROW(nmea::date(2012, nmea::month::september, 0));
	EXPECT_ANY_THROW(nmea::date(2012, nmea::month::october,   0));
	EXPECT_ANY_THROW(nmea::date(2012, nmea::month::november,  0));
	EXPECT_ANY_THROW(nmea::date(2012, nmea::month::december,  0));

	EXPECT_ANY_THROW(nmea::date(2010, nmea::month::february, 29));
	EXPECT_ANY_THROW(nmea::date(2011, nmea::month::february, 29));
	EXPECT_ANY_THROW(nmea::date(2012, nmea::month::february, 30));
	EXPECT_ANY_THROW(nmea::date(2013, nmea::month::february, 29));
}

TEST_F(Test_nmea_date, invalid_month)
{
	EXPECT_ANY_THROW(nmea::date(2012, static_cast<nmea::month>( 0), 0));
	EXPECT_ANY_THROW(nmea::date(2012, static_cast<nmea::month>(13), 0));
}

TEST_F(Test_nmea_date, comparison_equal)
{
	nmea::date d0{2010, nmea::month::january, 1};
	nmea::date d1{2010, nmea::month::january, 1};

	EXPECT_TRUE(d0 == d1);
}

TEST_F(Test_nmea_date, invalid_format_for_double)
{
	EXPECT_ANY_THROW(nmea::date::parse("123.455.6"));
}

TEST_F(Test_nmea_date, to_string)
{
	nmea::date d{2010, nmea::month::january, 1};

	auto s = nmea::to_string(d);

	EXPECT_STREQ("010120", s.c_str());
}

TEST_F(Test_nmea_date, stream)
{
	nmea::date d{2010, nmea::month::january, 1};

	std::ostringstream os;
	os << d;

	EXPECT_STREQ("010120", os.str().c_str());
}

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
