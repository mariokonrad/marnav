#ifndef TEST_NMEA_EXCEPTION_HELPER_HPP
#define TEST_NMEA_EXCEPTION_HELPER_HPP

#define EXPECT_EXCEPTION_STREQ(action, exception_type, s) \
	try {                                                 \
		{                                                 \
			action;                                       \
		}                                                 \
		FAIL() << "must not be reached";                  \
	} catch (exception_type & e) {                        \
		EXPECT_STREQ(s, e.what());                        \
	} catch (...) {                                       \
		FAIL() << "unexpected exception caught";          \
	}

#endif
