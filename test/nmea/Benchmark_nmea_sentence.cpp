#include <benchmark/benchmark_api.h>
#include <algorithm>
#include <typeindex>
#include <marnav/nmea/bod.hpp>
#include <marnav/nmea/bwc.hpp>
#include <marnav/nmea/rmc.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{
struct sentence_data {
	std::type_index type;
	std::string tag;
	std::string text;
};

#define INFO(s, text) {std::type_index(typeid(marnav::nmea::s)), marnav::nmea::s::TAG, text}

static std::vector<sentence_data> sentences = {
	INFO(bod, "$GPBOD,12.5,T,,,,*12"),
	INFO(bwc, "$GPBWC,220516,5130.02,N,00046.34,W,213.8,T,218.0,M,0004.6,N,EGLM,A*4C"),
	INFO(rmc, "$GPRMC,201126,A,4702.3944,N,00818.3381,E,0.0,328.4,260807,0.6,E,A*1E"),
};

#undef INFO

static sentence_data get_info(std::type_index t)
{
	const auto i = std::find_if(sentences.begin(), sentences.end(),
		[t](const sentence_data & d) { return t == d.type; });

	if (i == sentences.end())
		throw std::runtime_error{"sentence info not found"};

	return *i;
}

static void all_sentences(benchmark::internal::Benchmark * b)
{
	for (std::size_t i = 0; i < sentences.size(); ++i) {
		b->Arg(i);
	}
}
}

static void Benchmark_make_sentence(benchmark::State & state)
{
	state.SetLabel(sentences[state.range_x()].tag);
	while (state.KeepRunning()) {
		auto tmp = marnav::nmea::make_sentence(sentences[state.range_x()].text);
		benchmark::DoNotOptimize(tmp);
	}
}

BENCHMARK(Benchmark_make_sentence)->Apply(all_sentences);

static void Benchmark_make_sentence_fail(benchmark::State & state)
{
	state.SetLabel(sentences[state.range_x()].tag);
	std::string s = sentences[state.range_x()].text;
	s.replace(3, 3, "XXX");
	while (state.KeepRunning()) {
		try {
			auto tmp = marnav::nmea::make_sentence(s);
			benchmark::DoNotOptimize(tmp);
		} catch (...) {
			// intentionally left blank
		}
	}
}

BENCHMARK(Benchmark_make_sentence_fail)->Apply(all_sentences);

BENCHMARK_MAIN()
