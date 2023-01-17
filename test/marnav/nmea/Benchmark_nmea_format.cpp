#include <marnav/nmea/io.hpp>
#include <benchmark/benchmark.h>
#include <algorithm>

namespace v4
{

template <std::size_t Base, typename T>
void format(char * buf, size_t w, T data)
{
	static constexpr char tab[] = "0123456789abcdef";
	static_assert(Base <= sizeof(tab));

	std::size_t i = 0u;
	do {
		buf[i] = tab[data % Base];
		++i;
		data /= Base;
	} while (data);
	for (; i < w; ++i)
		buf[i] = '0';
	std::reverse(buf, buf + i);
}

std::string format(uint64_t data, unsigned int width, marnav::nmea::data_format f)
{
	char buf[std::numeric_limits<uint64_t>::digits10 + 1u] = {0};
	switch (f) {
		case marnav::nmea::data_format::none:
		case marnav::nmea::data_format::dec:
			format<10u>(buf, width, data);
			break;
		case marnav::nmea::data_format::hex:
			format<16>(buf, width, data);
			break;
	}
	return std::string{buf};
}
}

namespace v3
{
void format_dec(char * buf, std::size_t n, size_t w, uint64_t data)
{
	static constexpr char tab[] = "0123456789";

	std::size_t i = 0u;
	do {
		auto m = data % 10u;
		auto d = data / 10u;

		data = d;

		buf[i] = tab[m];
		++i;
	} while (data && i < n);
	std::fill_n(buf + i, std::min(w - i, n - i), '0');
	std::reverse(buf, buf + i);
}

void format_hex(char * buf, std::size_t n, size_t w, uint64_t data)
{
	static constexpr char tab[] = "0123456789abcdef";

	size_t i = 0u;
	do {
		buf[i] = tab[data % 16u];
		++i;
		data /= 16u;
	} while (data && i < n);
	for (; i < w && i < n; ++i)
		buf[i] = '0';
	std::reverse(buf, buf + i);
}

std::string format(uint64_t data, unsigned int width, marnav::nmea::data_format f)
{
	char buf[32] = {0};
	switch (f) {
		case marnav::nmea::data_format::none:
		case marnav::nmea::data_format::dec:
			format_dec(buf, sizeof(buf), width, data);
			break;
		case marnav::nmea::data_format::hex:
			format_hex(buf, sizeof(buf), width, data);
			break;
	}
	return std::string{buf};
}
}

namespace v2
{
void format_dec(char * buf, std::size_t n, size_t w, uint64_t data)
{
	static constexpr char tab[] = "0123456789";

	std::size_t i = 0u;
	do {
		buf[i] = tab[data % 10u];
		++i;
		data /= 10u;
	} while (data && i < n);
	for (; i < w && i < n; ++i)
		buf[i] = '0';
	if (i < n)
		buf[i] = '\0';
	std::reverse(buf, buf + i);
}

void format_hex(char * buf, std::size_t n, size_t w, uint64_t data)
{
	static constexpr char tab[] = "0123456789abcdef";

	size_t i = 0u;
	do {
		buf[i] = tab[data % 16u];
		++i;
		data /= 16u;
	} while (data && i < n);
	for (; i < w && i < n; ++i)
		buf[i] = '0';
	if (i < n)
		buf[i] = '\0';
	std::reverse(buf, buf + i);
}

std::string format(uint64_t data, unsigned int width, marnav::nmea::data_format f)
{
	char buf[32];
	switch (f) {
		case marnav::nmea::data_format::none:
		case marnav::nmea::data_format::dec:
			format_dec(buf, sizeof(buf), width, data);
			break;
		case marnav::nmea::data_format::hex:
			format_hex(buf, sizeof(buf), width, data);
			break;
	}
	return std::string{buf};
}
}

namespace v1
{
void format_dec(char * buf, std::size_t n, size_t w, uint64_t data)
{
	static constexpr char tab[] = "0123456789";

	std::size_t i = 0u;
	do {
		buf[i] = tab[data % 10u];
		++i;
		data /= 10u;
	} while (data && i < n);
	for (; i < w && i < n; ++i)
		buf[i] = '0';
	std::reverse(buf, buf + i);
}

void format_hex(char * buf, std::size_t n, size_t w, uint64_t data)
{
	static constexpr char tab[] = "0123456789abcdef";

	size_t i = 0u;
	do {
		buf[i] = tab[data % 16u];
		++i;
		data /= 16u;
	} while (data && i < n);
	for (; i < w && i < n; ++i)
		buf[i] = '0';
	std::reverse(buf, buf + i);
}

std::string format(uint64_t data, unsigned int width, marnav::nmea::data_format f)
{
	char buf[32] = {0};
	switch (f) {
		case marnav::nmea::data_format::none:
		case marnav::nmea::data_format::dec:
			format_dec(buf, sizeof(buf), width, data);
			break;
		case marnav::nmea::data_format::hex:
			format_hex(buf, sizeof(buf), width, data);
			break;
	}
	return std::string{buf};
}
}

namespace v0
{
std::string format(uint64_t data, unsigned int width, marnav::nmea::data_format f)
{
	// buffer to hold the resulting string with a static size.
	// this construct prevents VLA, and should be replaced with C++14 dynarray
	char buf[64];
	if (width >= sizeof(buf))
		throw std::invalid_argument{"width too large in nmea::format"};

	char fmt[8];
	switch (f) {
		case marnav::nmea::data_format::none:
		case marnav::nmea::data_format::dec:
			snprintf(fmt, sizeof(fmt), "%%0%ulu", width);
			break;
		case marnav::nmea::data_format::hex:
			snprintf(fmt, sizeof(fmt), "%%0%ulx", width);
			break;
	}

	snprintf(buf, sizeof(buf), fmt, data);
	return buf;
}
}

void bench_dec_v0(benchmark::State & state)
{
	while (state.KeepRunning()) {
		const std::uint64_t data = state.range(0);
		const auto s = v0::format(data, 10, marnav::nmea::data_format::dec);
		benchmark::DoNotOptimize(s);
	}
}

void bench_hex_v0(benchmark::State & state)
{
	while (state.KeepRunning()) {
		const std::uint64_t data = state.range(0);
		const auto s = v0::format(data, 10, marnav::nmea::data_format::hex);
		benchmark::DoNotOptimize(s);
	}
}

void bench_dec_v1(benchmark::State & state)
{
	while (state.KeepRunning()) {
		const std::uint64_t data = state.range(0);
		const auto s = v1::format(data, 10, marnav::nmea::data_format::dec);
		benchmark::DoNotOptimize(s);
	}
}

void bench_hex_v1(benchmark::State & state)
{
	while (state.KeepRunning()) {
		const std::uint64_t data = state.range(0);
		const auto s = v1::format(data, 10, marnav::nmea::data_format::hex);
		benchmark::DoNotOptimize(s);
	}
}

void bench_dec_v2(benchmark::State & state)
{
	while (state.KeepRunning()) {
		const std::uint64_t data = state.range(0);
		const auto s = v2::format(data, 10, marnav::nmea::data_format::dec);
		benchmark::DoNotOptimize(s);
	}
}

void bench_hex_v2(benchmark::State & state)
{
	while (state.KeepRunning()) {
		const std::uint64_t data = state.range(0);
		const auto s = v2::format(data, 10, marnav::nmea::data_format::hex);
		benchmark::DoNotOptimize(s);
	}
}

void bench_dec_v3(benchmark::State & state)
{
	while (state.KeepRunning()) {
		const std::uint64_t data = state.range(0);
		const auto s = v3::format(data, 10, marnav::nmea::data_format::dec);
		benchmark::DoNotOptimize(s);
	}
}

void bench_hex_v3(benchmark::State & state)
{
	while (state.KeepRunning()) {
		const std::uint64_t data = state.range(0);
		const auto s = v3::format(data, 10, marnav::nmea::data_format::hex);
		benchmark::DoNotOptimize(s);
	}
}

void bench_dec_v4(benchmark::State & state)
{
	while (state.KeepRunning()) {
		const std::uint64_t data = state.range(0);
		const auto s = v4::format(data, 10, marnav::nmea::data_format::dec);
		benchmark::DoNotOptimize(s);
	}
}

void bench_hex_v4(benchmark::State & state)
{
	while (state.KeepRunning()) {
		const std::uint64_t data = state.range(0);
		const auto s = v4::format(data, 10, marnav::nmea::data_format::hex);
		benchmark::DoNotOptimize(s);
	}
}

BENCHMARK(bench_dec_v0)->Range(0, 1lu << 48);
BENCHMARK(bench_dec_v1)->Range(0, 1lu << 48);
BENCHMARK(bench_dec_v2)->Range(0, 1lu << 48);
BENCHMARK(bench_dec_v3)->Range(0, 1lu << 48);
BENCHMARK(bench_dec_v4)->Range(0, 1lu << 48);

BENCHMARK(bench_hex_v0)->Range(0, 1lu<<48);
BENCHMARK(bench_hex_v1)->Range(0, 1lu<<48);
BENCHMARK(bench_hex_v2)->Range(0, 1lu<<48);
BENCHMARK(bench_hex_v3)->Range(0, 1lu<<48);
BENCHMARK(bench_hex_v4)->Range(0, 1lu<<48);

BENCHMARK_MAIN();
