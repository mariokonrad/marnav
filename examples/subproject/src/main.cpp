#include <marnav/version.hpp>
#include <marnav/nmea/nmea.hpp>
#include <iostream>
#include <string>
#include <vector>

int main(int, char **)
{
	std::cout << "marnav-demo\n";
	// clang-format off
	std::cout << "project version: " << marnav::project_version << '\n';
	std::cout << "marnav version:"
		<< ' ' << marnav::version_major
		<< '.' << marnav::version_minor
		<< '.' << marnav::version_patch
		<< '\n';
	// clang-format on

	std::cout << "supported sentences:\n";
	for (const auto & entry : marnav::nmea::get_supported_sentences_str())
		std::cout << "- " << entry << '\n';
}
