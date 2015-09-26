#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <algorithm>

int main(int argc, char ** argv)
{
	if (argc != 2) {
		printf("usage: %s \"sentence\" (sentence without start/end token)\n", argv[0]);
		return EXIT_FAILURE;
	}

	uint8_t checksum = 0x00;
	std::for_each(argv[1], argv[1] + strlen(argv[1]), [&checksum](char c) { checksum ^= c; });
	printf("%02X : '%s'\n", checksum, argv[1]);

	return EXIT_SUCCESS;
}
