#include <marnav/version.hpp>
#include <iostream>

int main(int, char **)
{
	std::cout << "project version: " << marnav::project_version << '\n';
	return 0;
}
