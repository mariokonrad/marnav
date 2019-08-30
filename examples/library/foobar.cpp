#include <iostream>
#include <marnav/version.hpp>

int main(int, char **)
{
	std::cout << "project version: " << marnav::project_version << '\n';
	return 0;
}
