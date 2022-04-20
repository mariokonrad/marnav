#include <marnav/version.hpp>
#include <marnav/nmea/nmea.hpp>
#include <iostream>
#include <string>
#include <vector>

int main(int, char **)
{
	std::cout << "marnav-demo\n";

	const auto meta = marnav::get_meta();
	// clang-format off
	std::cout << "project version: " << meta.project_version << '\n';
	std::cout << "marnav version:"
		<< ' ' << meta.version_major
		<< '.' << meta.version_minor
		<< '.' << meta.version_patch
		<< '\n';
	// clang-format on

	std::cout << "supported sentences:\n";
	for (const auto & entry : marnav::nmea::get_supported_sentences_str())
		std::cout << "- " << entry << '\n';
}
