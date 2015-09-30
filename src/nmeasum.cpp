#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <algorithm>
#include <marnav/nmea/checksum.hpp>

int main(int argc, char ** argv)
{
	if (argc != 2) {
		printf("usage: %s \"sentence\" (sentence without start/end token)\n", argv[0]);
		return EXIT_FAILURE;
	}

	printf("%02X : '%s'\n", marnav::nmea::checksum(argv[1], argv[1] + strlen(argv[1])), argv[1]);

	return EXIT_SUCCESS;
}
