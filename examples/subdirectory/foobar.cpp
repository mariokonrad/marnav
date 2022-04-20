#include <marnav/version.hpp>
#include <iostream>

int main(int, char **)
{
	std::cout << "project version: " << marnav::get_meta().project_version << '\n';
	return 0;
}
