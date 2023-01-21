#include <marnav/nmea/checksum.hpp>
#include <benchmark/benchmark.h>

namespace
{
// Baseline implementation.
static std::string checksum_to_string_v0(uint8_t sum)
{
	char buf[8];
	snprintf(buf, sizeof(buf), "%02X", sum);
	return buf;
}
}

static void benchmark_nmea_checksum_to_string_v0(benchmark::State & state)
{
	std::string result;
	while (state.KeepRunning()) {
		result = checksum_to_string_v0(state.range(0));
		benchmark::DoNotOptimize(result);
	}
}

BENCHMARK(benchmark_nmea_checksum_to_string_v0)->Range(0x00, 0xff);

static void benchmark_nmea_checksum_to_string(benchmark::State & state)
{
	std::string result;
	while (state.KeepRunning()) {
		result = marnav::nmea::checksum_to_string(state.range(0));
		benchmark::DoNotOptimize(result);
	}
}

BENCHMARK(benchmark_nmea_checksum_to_string)->Range(0x00, 0xff);

BENCHMARK_MAIN();
