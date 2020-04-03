#include <benchmark/benchmark.h>
#include <iomanip>
#include <locale>
#include <sstream>

namespace
{
// Baseline implementation
void read_v0(const std::string & s, double & value)
{
	if (s.empty())
		return;
	std::size_t pos = 0;
	value = std::stod(s, &pos);
	if (pos != s.size())
		throw std::runtime_error{"invalid string to convert to double: [" + s + "]"};
}

void read_v1(const std::string & s, double & value)
{
	if (s.empty())
		return;
	std::istringstream is(s);
	is.imbue(std::locale::classic());
	is >> value;
	if (!is.eof())
		throw std::runtime_error{"invalid string to convert to double: [" + s + "]"};
}

void read_v2(const std::string & s, double & value)
{
	if (s.empty())
		return;
	std::stringstream ss;
	ss.imbue(std::locale::classic());
	ss << s;
	ss >> value;
	if (!ss.eof())
		throw std::runtime_error{"invalid string to convert to double: [" + s + "]"};
}

void read_v3(const std::string & s, double & value)
{
	static const locale_t locale = ::newlocale(LC_NUMERIC_MASK, "C", nullptr);

	if (s.empty())
		return;
	char * endptr = nullptr;
	value = ::strtod_l(s.c_str(), &endptr, locale);
	if (endptr != s.c_str() + s.size())
		throw std::runtime_error{"invalid string to convert to double: [" + s + "]"};
}
}

static void Benchmark_nmea_string_to_double_v0(benchmark::State & state)
{
	static const std::string s = "3.14159265";
	while (state.KeepRunning()) {
		double result = 0.0;
		read_v0(s, result);
		benchmark::DoNotOptimize(result);
	}
}

BENCHMARK(Benchmark_nmea_string_to_double_v0);

static void Benchmark_nmea_string_to_double_v1(benchmark::State & state)
{
	static const std::string s = "3.14159265";
	while (state.KeepRunning()) {
		double result;
		read_v1(s, result);
		benchmark::DoNotOptimize(result);
	}
}

BENCHMARK(Benchmark_nmea_string_to_double_v1);

static void Benchmark_nmea_string_to_double_v2(benchmark::State & state)
{
	static const std::string s = "3.14159265";
	while (state.KeepRunning()) {
		double result;
		read_v2(s, result);
		benchmark::DoNotOptimize(result);
	}
}

BENCHMARK(Benchmark_nmea_string_to_double_v2);

static void Benchmark_nmea_string_to_double_v3(benchmark::State & state)
{
	static const std::string s = "3.14159265";
	while (state.KeepRunning()) {
		double result;
		read_v3(s, result);
		benchmark::DoNotOptimize(result);
	}
}

BENCHMARK(Benchmark_nmea_string_to_double_v3);

// baseline, "old implementation"
std::string format_double_v0(double data, unsigned int width)
{
	// buffer to hold the resulting string with a static size.
	// this construct prevents VLA, and should be replaced with C++14 dynarray
	char buf[32];
	if (width >= sizeof(buf))
		throw std::invalid_argument{"width too large in nmea::format"};

	char fmt[8];
	snprintf(fmt, sizeof(fmt), "%%.%uf", width);
	snprintf(buf, sizeof(buf), fmt, data);
	return buf;
}

std::string format_double_v1(double data, unsigned int width)
{
	std::ostringstream os;
	os.imbue(std::locale::classic());
	os << std::setiosflags(std::ios::dec | std::ios::fixed);
	os << std::setprecision(width);
	os << data;
	return os.str();
}

static void Benchmark_nmea_format_double_v0(benchmark::State & state)
{
	while (state.KeepRunning()) {
		std::string result = format_double_v0(3.14159, 4);
		benchmark::DoNotOptimize(result);
	}
}

BENCHMARK(Benchmark_nmea_format_double_v0);

static void Benchmark_nmea_format_double_v1(benchmark::State & state)
{
	while (state.KeepRunning()) {
		std::string result = format_double_v1(3.14159, 4);
		benchmark::DoNotOptimize(result);
	}
}

BENCHMARK(Benchmark_nmea_format_double_v1);

BENCHMARK_MAIN()
