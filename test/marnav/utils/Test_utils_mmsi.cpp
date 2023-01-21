#include <marnav/utils/mmsi.hpp>
#include <gtest/gtest.h>

namespace
{
using marnav::utils::mmsi;

class test_utils_mmsi : public ::testing::Test
{
};

TEST_F(test_utils_mmsi, construction_and_get)
{
	const uint32_t expected = 269263111;

	mmsi m{expected};

	uint32_t value = m;
	EXPECT_EQ(expected, value);
}

TEST_F(test_utils_mmsi, copy_constructed)
{
	mmsi m{269263111};
	mmsi copy = m;

	EXPECT_TRUE(m == copy);
}

TEST_F(test_utils_mmsi, copy_assign)
{
	mmsi m{269263111};
	mmsi copy{0};

	copy = m;

	EXPECT_TRUE(m == copy);
}

TEST_F(test_utils_mmsi, regular)
{
	const mmsi m{269263111};
	EXPECT_TRUE(m.is_regular());
	EXPECT_FALSE(m.is_group());
	EXPECT_FALSE(m.is_coastal());
	EXPECT_FALSE(m.is_auxiliary());
	EXPECT_FALSE(m.is_ais_aids());
	EXPECT_FALSE(m.is_sar_aircraft());
	EXPECT_FALSE(m.is_sart());
	EXPECT_FALSE(m.is_mob());
	EXPECT_FALSE(m.is_epirb_ais());

	EXPECT_EQ(269u, m.mid());
	EXPECT_EQ(263111u, m.id());
	EXPECT_EQ(0u, m.man());

	EXPECT_EQ(269u, m.regular_mid());
	EXPECT_EQ(263111u, m.regular_id());
	EXPECT_EQ(0u, m.group_mid());
	EXPECT_EQ(0u, m.group_id());
	EXPECT_EQ(0u, m.auxiliary_mid());
	EXPECT_EQ(0u, m.auxiliary_id());
	EXPECT_EQ(0u, m.coastal_mid());
	EXPECT_EQ(0u, m.coastal_id());
	EXPECT_EQ(0u, m.mob_id());
	EXPECT_EQ(0u, m.sar_mid());
	EXPECT_EQ(0u, m.sar_id());
	EXPECT_EQ(0u, m.sart_id());
	EXPECT_EQ(0u, m.epirb_ais_id());
	EXPECT_EQ(0u, m.ais_aids_id());

	EXPECT_EQ(0u, m.sart_man());
	EXPECT_EQ(0u, m.mob_man());
	EXPECT_EQ(0u, m.epirb_ais_man());
}

TEST_F(test_utils_mmsi, group)
{
	const mmsi m{26911111};
	EXPECT_FALSE(m.is_regular());
	EXPECT_TRUE(m.is_group());
	EXPECT_FALSE(m.is_coastal());
	EXPECT_FALSE(m.is_auxiliary());
	EXPECT_FALSE(m.is_ais_aids());
	EXPECT_FALSE(m.is_sar_aircraft());
	EXPECT_FALSE(m.is_sart());
	EXPECT_FALSE(m.is_mob());
	EXPECT_FALSE(m.is_epirb_ais());

	EXPECT_EQ(269u, m.mid());
	EXPECT_EQ(11111u, m.id());
	EXPECT_EQ(0u, m.man());

	EXPECT_EQ(0u, m.regular_mid());
	EXPECT_EQ(0u, m.regular_id());
	EXPECT_EQ(269u, m.group_mid());
	EXPECT_EQ(11111u, m.group_id());
	EXPECT_EQ(0u, m.auxiliary_mid());
	EXPECT_EQ(0u, m.auxiliary_id());
	EXPECT_EQ(0u, m.coastal_mid());
	EXPECT_EQ(0u, m.coastal_id());
	EXPECT_EQ(0u, m.mob_id());
	EXPECT_EQ(0u, m.sar_mid());
	EXPECT_EQ(0u, m.sar_id());
	EXPECT_EQ(0u, m.sart_id());
	EXPECT_EQ(0u, m.epirb_ais_id());
	EXPECT_EQ(0u, m.ais_aids_id());

	EXPECT_EQ(0u, m.sart_man());
	EXPECT_EQ(0u, m.mob_man());
	EXPECT_EQ(0u, m.epirb_ais_man());
}

TEST_F(test_utils_mmsi, auxiliary)
{
	const mmsi m{982691111};
	EXPECT_FALSE(m.is_regular());
	EXPECT_FALSE(m.is_group());
	EXPECT_FALSE(m.is_coastal());
	EXPECT_TRUE(m.is_auxiliary());
	EXPECT_FALSE(m.is_ais_aids());
	EXPECT_FALSE(m.is_sar_aircraft());
	EXPECT_FALSE(m.is_sart());
	EXPECT_FALSE(m.is_mob());
	EXPECT_FALSE(m.is_epirb_ais());

	EXPECT_EQ(269u, m.mid());
	EXPECT_EQ(1111u, m.id());
	EXPECT_EQ(0u, m.man());

	EXPECT_EQ(0u, m.regular_mid());
	EXPECT_EQ(0u, m.regular_id());
	EXPECT_EQ(0u, m.group_mid());
	EXPECT_EQ(0u, m.group_id());
	EXPECT_EQ(269u, m.auxiliary_mid());
	EXPECT_EQ(1111u, m.auxiliary_id());
	EXPECT_EQ(0u, m.coastal_mid());
	EXPECT_EQ(0u, m.coastal_id());
	EXPECT_EQ(0u, m.mob_id());
	EXPECT_EQ(0u, m.sar_mid());
	EXPECT_EQ(0u, m.sar_id());
	EXPECT_EQ(0u, m.sart_id());
	EXPECT_EQ(0u, m.epirb_ais_id());
	EXPECT_EQ(0u, m.ais_aids_id());

	EXPECT_EQ(0u, m.sart_man());
	EXPECT_EQ(0u, m.mob_man());
	EXPECT_EQ(0u, m.epirb_ais_man());
}

TEST_F(test_utils_mmsi, ais_aids)
{
	const mmsi m{992691111};
	EXPECT_FALSE(m.is_regular());
	EXPECT_FALSE(m.is_group());
	EXPECT_FALSE(m.is_coastal());
	EXPECT_FALSE(m.is_auxiliary());
	EXPECT_TRUE(m.is_ais_aids());
	EXPECT_FALSE(m.is_sar_aircraft());
	EXPECT_FALSE(m.is_sart());
	EXPECT_FALSE(m.is_mob());
	EXPECT_FALSE(m.is_epirb_ais());

	EXPECT_EQ(0u, m.mid());
	EXPECT_EQ(1111u, m.id());
	EXPECT_EQ(0u, m.man());

	EXPECT_EQ(0u, m.regular_mid());
	EXPECT_EQ(0u, m.regular_id());
	EXPECT_EQ(0u, m.group_mid());
	EXPECT_EQ(0u, m.group_id());
	EXPECT_EQ(0u, m.auxiliary_mid());
	EXPECT_EQ(0u, m.auxiliary_id());
	EXPECT_EQ(0u, m.coastal_mid());
	EXPECT_EQ(0u, m.coastal_id());
	EXPECT_EQ(0u, m.mob_id());
	EXPECT_EQ(0u, m.sar_mid());
	EXPECT_EQ(0u, m.sar_id());
	EXPECT_EQ(0u, m.sart_id());
	EXPECT_EQ(0u, m.epirb_ais_id());
	EXPECT_EQ(1111u, m.ais_aids_id());

	EXPECT_EQ(0u, m.sart_man());
	EXPECT_EQ(0u, m.mob_man());
	EXPECT_EQ(0u, m.epirb_ais_man());
}

TEST_F(test_utils_mmsi, coastal)
{
	const mmsi m{2691111};
	EXPECT_FALSE(m.is_regular());
	EXPECT_FALSE(m.is_group());
	EXPECT_TRUE(m.is_coastal());
	EXPECT_FALSE(m.is_all_coastal());
	EXPECT_FALSE(m.is_all_coastal_for(269));
	EXPECT_FALSE(m.is_auxiliary());
	EXPECT_FALSE(m.is_ais_aids());
	EXPECT_FALSE(m.is_sar_aircraft());
	EXPECT_FALSE(m.is_sart());
	EXPECT_FALSE(m.is_mob());
	EXPECT_FALSE(m.is_epirb_ais());

	EXPECT_EQ(269u, m.mid());
	EXPECT_EQ(1111u, m.id());
	EXPECT_EQ(0u, m.man());

	EXPECT_EQ(0u, m.regular_mid());
	EXPECT_EQ(0u, m.regular_id());
	EXPECT_EQ(0u, m.group_mid());
	EXPECT_EQ(0u, m.group_id());
	EXPECT_EQ(0u, m.auxiliary_mid());
	EXPECT_EQ(0u, m.auxiliary_id());
	EXPECT_EQ(269u, m.coastal_mid());
	EXPECT_EQ(1111u, m.coastal_id());
	EXPECT_EQ(0u, m.mob_id());
	EXPECT_EQ(0u, m.sar_mid());
	EXPECT_EQ(0u, m.sar_id());
	EXPECT_EQ(0u, m.sart_id());
	EXPECT_EQ(0u, m.epirb_ais_id());
	EXPECT_EQ(0u, m.ais_aids_id());

	EXPECT_EQ(0u, m.sart_man());
	EXPECT_EQ(0u, m.mob_man());
	EXPECT_EQ(0u, m.epirb_ais_man());
}

TEST_F(test_utils_mmsi, coastal_all)
{
	const mmsi m{9990000};
	EXPECT_FALSE(m.is_regular());
	EXPECT_FALSE(m.is_group());
	EXPECT_TRUE(m.is_coastal());
	EXPECT_TRUE(m.is_all_coastal());
	EXPECT_TRUE(m.is_all_coastal_for(999));
	EXPECT_FALSE(m.is_auxiliary());
	EXPECT_FALSE(m.is_ais_aids());
	EXPECT_FALSE(m.is_sar_aircraft());
	EXPECT_FALSE(m.is_sart());
	EXPECT_FALSE(m.is_mob());
	EXPECT_FALSE(m.is_epirb_ais());
}

TEST_F(test_utils_mmsi, coastal_all_for_mid)
{
	const mmsi m{2690000};
	EXPECT_FALSE(m.is_regular());
	EXPECT_FALSE(m.is_group());
	EXPECT_TRUE(m.is_coastal());
	EXPECT_FALSE(m.is_all_coastal());
	EXPECT_TRUE(m.is_all_coastal_for(269));
	EXPECT_FALSE(m.is_auxiliary());
	EXPECT_FALSE(m.is_ais_aids());
	EXPECT_FALSE(m.is_sar_aircraft());
	EXPECT_FALSE(m.is_sart());
	EXPECT_FALSE(m.is_mob());
	EXPECT_FALSE(m.is_epirb_ais());
}

TEST_F(test_utils_mmsi, sar_aircraft)
{
	const mmsi m{111269123};
	EXPECT_FALSE(m.is_regular());
	EXPECT_FALSE(m.is_group());
	EXPECT_FALSE(m.is_coastal());
	EXPECT_FALSE(m.is_all_coastal());
	EXPECT_FALSE(m.is_auxiliary());
	EXPECT_FALSE(m.is_ais_aids());
	EXPECT_TRUE(m.is_sar_aircraft());
	EXPECT_FALSE(m.is_sart());
	EXPECT_FALSE(m.is_mob());
	EXPECT_FALSE(m.is_epirb_ais());

	EXPECT_EQ(269u, m.mid());
	EXPECT_EQ(123u, m.id());
	EXPECT_EQ(0u, m.man());

	EXPECT_EQ(0u, m.regular_mid());
	EXPECT_EQ(0u, m.regular_id());
	EXPECT_EQ(0u, m.group_mid());
	EXPECT_EQ(0u, m.group_id());
	EXPECT_EQ(0u, m.auxiliary_mid());
	EXPECT_EQ(0u, m.auxiliary_id());
	EXPECT_EQ(0u, m.coastal_mid());
	EXPECT_EQ(0u, m.coastal_id());
	EXPECT_EQ(0u, m.mob_id());
	EXPECT_EQ(269u, m.sar_mid());
	EXPECT_EQ(123u, m.sar_id());
	EXPECT_EQ(0u, m.sart_id());
	EXPECT_EQ(0u, m.epirb_ais_id());
	EXPECT_EQ(0u, m.ais_aids_id());

	EXPECT_EQ(0u, m.sart_man());
	EXPECT_EQ(0u, m.mob_man());
	EXPECT_EQ(0u, m.epirb_ais_man());
}

TEST_F(test_utils_mmsi, sart)
{
	const mmsi m{970269123};
	EXPECT_FALSE(m.is_regular());
	EXPECT_FALSE(m.is_group());
	EXPECT_FALSE(m.is_coastal());
	EXPECT_FALSE(m.is_all_coastal());
	EXPECT_FALSE(m.is_auxiliary());
	EXPECT_FALSE(m.is_ais_aids());
	EXPECT_FALSE(m.is_sar_aircraft());
	EXPECT_TRUE(m.is_sart());
	EXPECT_FALSE(m.is_mob());
	EXPECT_FALSE(m.is_epirb_ais());

	EXPECT_EQ(0u, m.mid());
	EXPECT_EQ(9123u, m.id());
	EXPECT_EQ(26u, m.man());

	EXPECT_EQ(0u, m.regular_mid());
	EXPECT_EQ(0u, m.regular_id());
	EXPECT_EQ(0u, m.group_mid());
	EXPECT_EQ(0u, m.group_id());
	EXPECT_EQ(0u, m.auxiliary_mid());
	EXPECT_EQ(0u, m.auxiliary_id());
	EXPECT_EQ(0u, m.coastal_mid());
	EXPECT_EQ(0u, m.coastal_id());
	EXPECT_EQ(0u, m.mob_id());
	EXPECT_EQ(0u, m.sar_mid());
	EXPECT_EQ(0u, m.sar_id());
	EXPECT_EQ(9123u, m.sart_id());
	EXPECT_EQ(0u, m.epirb_ais_id());
	EXPECT_EQ(0u, m.ais_aids_id());

	EXPECT_EQ(26u, m.sart_man());
	EXPECT_EQ(0u, m.mob_man());
	EXPECT_EQ(0u, m.epirb_ais_man());
}

TEST_F(test_utils_mmsi, mob)
{
	const mmsi m{972269123};
	EXPECT_FALSE(m.is_regular());
	EXPECT_FALSE(m.is_group());
	EXPECT_FALSE(m.is_coastal());
	EXPECT_FALSE(m.is_all_coastal());
	EXPECT_FALSE(m.is_auxiliary());
	EXPECT_FALSE(m.is_ais_aids());
	EXPECT_FALSE(m.is_sar_aircraft());
	EXPECT_FALSE(m.is_sart());
	EXPECT_TRUE(m.is_mob());
	EXPECT_FALSE(m.is_epirb_ais());

	EXPECT_EQ(0u, m.mid());
	EXPECT_EQ(9123u, m.id());
	EXPECT_EQ(26u, m.man());

	EXPECT_EQ(0u, m.regular_mid());
	EXPECT_EQ(0u, m.regular_id());
	EXPECT_EQ(0u, m.group_mid());
	EXPECT_EQ(0u, m.group_id());
	EXPECT_EQ(0u, m.auxiliary_mid());
	EXPECT_EQ(0u, m.auxiliary_id());
	EXPECT_EQ(0u, m.coastal_mid());
	EXPECT_EQ(0u, m.coastal_id());
	EXPECT_EQ(9123u, m.mob_id());
	EXPECT_EQ(0u, m.sar_mid());
	EXPECT_EQ(0u, m.sar_id());
	EXPECT_EQ(0u, m.sart_id());
	EXPECT_EQ(0u, m.epirb_ais_id());
	EXPECT_EQ(0u, m.ais_aids_id());

	EXPECT_EQ(0u, m.sart_man());
	EXPECT_EQ(26u, m.mob_man());
	EXPECT_EQ(0u, m.epirb_ais_man());
}

TEST_F(test_utils_mmsi, eprib_ais)
{
	const mmsi m{974269123};
	EXPECT_FALSE(m.is_regular());
	EXPECT_FALSE(m.is_group());
	EXPECT_FALSE(m.is_coastal());
	EXPECT_FALSE(m.is_all_coastal());
	EXPECT_FALSE(m.is_auxiliary());
	EXPECT_FALSE(m.is_ais_aids());
	EXPECT_FALSE(m.is_sar_aircraft());
	EXPECT_FALSE(m.is_sart());
	EXPECT_FALSE(m.is_mob());
	EXPECT_TRUE(m.is_epirb_ais());

	EXPECT_EQ(0u, m.mid());
	EXPECT_EQ(9123u, m.id());
	EXPECT_EQ(26u, m.man());

	EXPECT_EQ(0u, m.regular_mid());
	EXPECT_EQ(0u, m.regular_id());
	EXPECT_EQ(0u, m.group_mid());
	EXPECT_EQ(0u, m.group_id());
	EXPECT_EQ(0u, m.auxiliary_mid());
	EXPECT_EQ(0u, m.auxiliary_id());
	EXPECT_EQ(0u, m.coastal_mid());
	EXPECT_EQ(0u, m.coastal_id());
	EXPECT_EQ(0u, m.mob_id());
	EXPECT_EQ(0u, m.sar_mid());
	EXPECT_EQ(0u, m.sar_id());
	EXPECT_EQ(0u, m.sart_id());
	EXPECT_EQ(9123u, m.epirb_ais_id());
	EXPECT_EQ(0u, m.ais_aids_id());

	EXPECT_EQ(0u, m.sart_man());
	EXPECT_EQ(0u, m.mob_man());
	EXPECT_EQ(26u, m.epirb_ais_man());
}
}
