#include <benchmark/benchmark_api.h>
#include <marnav/nmea/manufacturer.hpp>

static void benchmark_get_manufacturer_name_from_id(benchmark::State & state)
{
	using namespace marnav;

	const std::vector<nmea::manufacturer_id> ids = nmea::get_supported_manufacturer_id();

	while (state.KeepRunning()) {
		for (auto id : ids) {
			std::string name = nmea::get_manufacturer_name(id);
			benchmark::DoNotOptimize(name);
		}
	}
}

BENCHMARK(benchmark_get_manufacturer_name_from_id);

BENCHMARK_MAIN()
