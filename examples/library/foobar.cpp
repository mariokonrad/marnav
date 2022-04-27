#include <marnav/version.hpp>

#ifdef HAVE_IO
	#include <marnav-io/nmea_reader.hpp>
#endif

#include <iostream>

int main(int, char **)
{
	std::cout << "project version: " << marnav::get_meta().project_version;

#ifdef HAVE_IO
	std::cout << " (IO support: true)";
#endif

	std::cout << std::endl;

	return 0;
}
