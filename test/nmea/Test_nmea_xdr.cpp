#include <gtest/gtest.h>
#include <marnav/nmea/xdr.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_xdr : public ::testing::Test
{
};

TEST_F(Test_nmea_xdr, contruction) { nmea::xdr xdr; }

TEST_F(Test_nmea_xdr, parse)
{
	auto s = nmea::make_sentence("$YXXDR,a,16.0,M,abc*1A");
	ASSERT_NE(nullptr, s);

	auto xdr = nmea::sentence_cast<nmea::xdr>(s);
	ASSERT_NE(nullptr, xdr);
}

TEST_F(Test_nmea_xdr, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::xdr::parse("@@", {0, "@"}));
	EXPECT_ANY_THROW(nmea::xdr::parse("@@", {41, "@"}));
	EXPECT_ANY_THROW(nmea::xdr::parse("@@", {3, "@"}));
}

TEST_F(Test_nmea_xdr, empty_to_string)
{
	nmea::xdr xdr;

	EXPECT_STREQ("$YXXDR*4F", nmea::to_string(xdr).c_str());
}

TEST_F(Test_nmea_xdr, nonempty_to_string)
{
	nmea::xdr xdr;
	xdr.set_info(0, {'a', 1.678, 'C', "ABC"});

	EXPECT_STREQ("$YXXDR,a,1.678,C,ABC*0B", nmea::to_string(xdr).c_str());
}

TEST_F(Test_nmea_xdr, get_info_invalid_index)
{
	nmea::xdr xdr;

	EXPECT_ANY_THROW(xdr.get_info(-1));
	EXPECT_ANY_THROW(xdr.get_info(40));
}

TEST_F(Test_nmea_xdr, one_data_point)
{
	auto s = nmea::make_sentence("$YXXDR,a,1.0,M,abc*2C");
	ASSERT_NE(nullptr, s);
	auto xdr = nmea::sentence_cast<nmea::xdr>(s);
	ASSERT_NE(nullptr, xdr);

	auto info = *xdr->get_info(0);
	EXPECT_EQ('a', info.transducer_type);
	EXPECT_NEAR(1.0, info.measurement_data, 1e-8);
	EXPECT_EQ('M', info.units_of_measurement);
	EXPECT_STREQ("abc", info.name.c_str());
}

TEST_F(Test_nmea_xdr, two_data_points)
{
	auto s = nmea::make_sentence("$YXXDR,a,1.0,M,abc,b,2.0,M,def*48");
	ASSERT_NE(nullptr, s);
	auto xdr = nmea::sentence_cast<nmea::xdr>(s);
	ASSERT_NE(nullptr, xdr);

	{
		auto info = *xdr->get_info(0);
		EXPECT_EQ('a', info.transducer_type);
		EXPECT_NEAR(1.0, info.measurement_data, 1e-8);
		EXPECT_EQ('M', info.units_of_measurement);
		EXPECT_STREQ("abc", info.name.c_str());
	}
	{
		auto info = *xdr->get_info(1);
		EXPECT_EQ('b', info.transducer_type);
		EXPECT_NEAR(2.0, info.measurement_data, 1e-8);
		EXPECT_EQ('M', info.units_of_measurement);
		EXPECT_STREQ("def", info.name.c_str());
	}
}

TEST_F(Test_nmea_xdr, recorded)
{
	// found on the internet
	{
		auto s = nmea::make_sentence(
			"$IIXDR,C,,C,ENV_WATER_T,C,24.24,C,ENV_OUTAIR_T,P,100700,P,ENV_ATMOS_P*6E");
	}
	{
		auto s = nmea::make_sentence("$IIXDR,C,24.24,C,ENV_OUTSIDE_T,P,100700,P,ENV_ATMOS_P,H,"
									 "64.356,P,ENV_OUTSIDE_H*37");
	}
	{
		auto s = nmea::make_sentence("$IIXDR,P,1.02481,B,Barometer*29"); // replaced checksum
	}
	{
		auto s = nmea::make_sentence("$IIXDR,C,19.52,C,TempAir*19"); // replaced checksum
	}
}

}
