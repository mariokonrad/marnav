#include <gtest/gtest.h>
#include <marnav/nmea/dse.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_dse : public ::testing::Test
{
};

TEST_F(Test_nmea_dse, contruction) { EXPECT_NO_THROW(nmea::dse dse); }

TEST_F(Test_nmea_dse, parse)
{
	static const std::vector<std::string> TESTS
		= {"$CDDSE,1,1,A,3664251410,00,47800350*1D", "$CDDSE,1,1,R,3380210040,00,46506420*0F"};

	for (const auto & test : TESTS) {
		auto s = nmea::make_sentence(test);
		EXPECT_NE(nullptr, s);
		if (s) {
			auto dse = nmea::sentence_cast<nmea::dse>(s);
			EXPECT_NE(nullptr, dse);
		}
	}
}

TEST_F(Test_nmea_dse, get_number_of_messages)
{
	{
		auto s = nmea::sentence_cast<nmea::dse>(
			nmea::make_sentence("$CDDSE,1,1,A,3664251410,00,47800350*1D"));
		EXPECT_EQ(1u, s->get_number_of_messages());
	}
	{
		auto s = nmea::sentence_cast<nmea::dse>(
			nmea::make_sentence("$CDDSE,2,1,A,3664251410,00,47800350*1E"));
		EXPECT_EQ(2u, s->get_number_of_messages());
	}
}

TEST_F(Test_nmea_dse, get_sentence_number)
{
	{
		auto s = nmea::sentence_cast<nmea::dse>(
			nmea::make_sentence("$CDDSE,1,1,A,3664251410,00,47800350*1D"));
		EXPECT_EQ(1u, s->get_sentence_number());
	}
	{
		auto s = nmea::sentence_cast<nmea::dse>(
			nmea::make_sentence("$CDDSE,1,2,A,3664251410,00,47800350*1E"));
		EXPECT_EQ(2u, s->get_sentence_number());
	}
}

TEST_F(Test_nmea_dse, get_flag)
{
	{
		auto s = nmea::sentence_cast<nmea::dse>(
			nmea::make_sentence("$CDDSE,1,1,A,3664251410,00,47800350*1D"));
		EXPECT_EQ(nmea::dse::query_flag::a, s->get_flag());
	}
	{
		auto s = nmea::sentence_cast<nmea::dse>(
			nmea::make_sentence("$CDDSE,1,1,Q,3664251410,00,47800350*0D"));
		EXPECT_EQ(nmea::dse::query_flag::query, s->get_flag());
	}
	{
		auto s = nmea::sentence_cast<nmea::dse>(
			nmea::make_sentence("$CDDSE,1,1,R,3664251410,00,47800350*0E"));
		EXPECT_EQ(nmea::dse::query_flag::reply, s->get_flag());
	}
}

TEST_F(Test_nmea_dse, get_mmsi)
{
	auto s = nmea::sentence_cast<nmea::dse>(
		nmea::make_sentence("$CDDSE,1,1,A,3664251410,00,47800350*1D"));
	EXPECT_EQ(utils::mmsi{366425141}, s->get_mmsi());
}

TEST_F(Test_nmea_dse, empty_to_string)
{
	nmea::dse dse;
	EXPECT_STREQ("$CDDSE,1,1,Q,0000000000,,*04", nmea::to_string(dse).c_str());
}
}
