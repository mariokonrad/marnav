#include <benchmark/benchmark_api.h>
#include <marnav/nmea/split.hpp>
#include <regex>

namespace
{
static const std::vector<std::string> SENTENCES = {
	"$GPRMC,201126,A,4702.3944,N,00818.3381,E,0.0,328.4,260807,0.6,E,A*1E",
	"$GPRMC,,V,,,,,,,300510,0.6,E,N*39",
	"$,,,,,,,,,,,,*",
};

// Baseline implementation.
static std::vector<std::string> parse_fields__v0(const std::string & s)
{
	if (s.size() < 1)
		return std::vector<std::string>{};

	std::regex field_regex{"(,|\\*)"};
	auto fields_begin = std::sregex_token_iterator{begin(s) + 1, end(s), field_regex, -1};
	auto fields_end = std::sregex_token_iterator();
	return {fields_begin, fields_end};
}

// Improved implementation, reducing instantiation of regex parser.
static std::vector<std::string> parse_fields__v1(const std::string & s)
{
	if (s.size() < 1)
		return std::vector<std::string>{};

	static const std::regex field_regex{"(,|\\*)"};
	auto fields_begin = std::sregex_token_iterator{begin(s) + 1, end(s), field_regex, -1};
	auto fields_end = std::sregex_token_iterator();
	return {fields_begin, fields_end};
}

// No regex anymore, simple string handling
static std::vector<std::string> parse_fields__v2(const std::string & s)
{
	if (s.size() < 1)
		return std::vector<std::string>{};

	static const char * DELIMITERS = ",*";
	std::vector<std::string> result;
	std::string::size_type last = 1;
	std::string::size_type p = s.find_first_of(DELIMITERS, last);
	while (last != std::string::npos) {
		result.push_back(s.substr(last, p - last));
		if (p == std::string::npos)
			break;
		last = p + 1;
		p = s.find_first_of(DELIMITERS, last);
	}
	return result;
}

// No regex anymore, simple string handling, reallocating string vector for
// 14 elements (number of fields in RMC)
static std::vector<std::string> parse_fields__v3(const std::string & s)
{
	if (s.size() < 1)
		return std::vector<std::string>{};

	static const char * DELIMITERS = ",*";
	std::vector<std::string> result;
	result.reserve(14);
	std::string::size_type last = 1;
	std::string::size_type p = s.find_first_of(DELIMITERS, last);
	while (last != std::string::npos) {
		result.push_back(s.substr(last, p - last));
		if (p == std::string::npos)
			break;
		last = p + 1;
		p = s.find_first_of(DELIMITERS, last);
	}
	return result;
}
}

static void Benchmark_nmea_split_v0(benchmark::State & state)
{
	std::string sentence = SENTENCES[state.range_x()];
	std::vector<std::string> result;
	while (state.KeepRunning()) {
		result = parse_fields__v0(sentence);
		benchmark::DoNotOptimize(result);
	}
}

BENCHMARK(Benchmark_nmea_split_v0)->Range(0, 2);

static void Benchmark_nmea_split_v1(benchmark::State & state)
{
	std::string sentence = SENTENCES[state.range_x()];
	std::vector<std::string> result;
	while (state.KeepRunning()) {
		result = parse_fields__v1(sentence);
		benchmark::DoNotOptimize(result);
	}
}

BENCHMARK(Benchmark_nmea_split_v1)->Range(0, 2);

static void Benchmark_nmea_split_v2(benchmark::State & state)
{
	std::string sentence = SENTENCES[state.range_x()];
	std::vector<std::string> result;
	while (state.KeepRunning()) {
		result = parse_fields__v2(sentence);
		benchmark::DoNotOptimize(result);
	}
}

BENCHMARK(Benchmark_nmea_split_v2)->Range(0, 2);

static void Benchmark_nmea_split_v3(benchmark::State & state)
{
	std::string sentence = SENTENCES[state.range_x()];
	std::vector<std::string> result;
	while (state.KeepRunning()) {
		result = parse_fields__v3(sentence);
		benchmark::DoNotOptimize(result);
	}
}

BENCHMARK(Benchmark_nmea_split_v3)->Range(0, 2);

static void Benchmark_nmea_split(benchmark::State & state)
{
	std::string sentence = SENTENCES[state.range_x()];
	std::vector<std::string> result;
	while (state.KeepRunning()) {
		result = marnav::nmea::detail::parse_fields(sentence);
		benchmark::DoNotOptimize(result);
	}
}

BENCHMARK(Benchmark_nmea_split)->Range(0, 2);

BENCHMARK_MAIN()
