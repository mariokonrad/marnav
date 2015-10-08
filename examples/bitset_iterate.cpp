#include <iostream>
#include <marnav/utils/bitset.hpp>

int main(int, char **)
{
	marnav::utils::bitset<uint32_t> bits;

	// append some data
	bits.append(0xaa, 8);
	bits.append(0x55, 8);

	// iterate through all bits and print them to stdout
	for (auto const & bit : bits)
		std::cout << bit;
	std::cout << "\n";
}
