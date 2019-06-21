#include <iostream>
#include <marnav/version.hpp>

int main(int, char **)
{
	using namespace marnav;

	std::cout << version_major << "." << version_minor << "." << version_patch << "\n";
	return 0;
}
