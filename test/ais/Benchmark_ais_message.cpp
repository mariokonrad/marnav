#include <benchmark/benchmark.h>
#include <marnav/ais/ais.hpp>

namespace
{
using payload = std::vector<std::pair<std::string, uint32_t>>;

struct message_data {
	std::string label;
	payload data;
};

static std::vector<message_data> messages = {
	{"message_01", {{"133m@ogP00PD;88MD5MTDww@2D7k", 0}}},
	{"message_02", {{"233m@ogP00PD;88MD5MTDww@2D7k", 0}}},
	{"message_03", {{"333m@ogP00PD;88MD5MTDww@2D7k", 0}}},
	{"message_04", {{"4020ssAuho;N?PeNwjOAp<70089A", 0}}},
	{"message_05",
		{{"55P5TL01VIaAL@7WKO@mBplU@<PDhh000000001S;AJ::4A80?4i@E53", 0},
			{"1@0000000000000", 2}}},
	{"message_09", {{"91b55vRAQwOnDE<M05ICOp0208CM", 0}}},
	{"message_10", {{":81:Jf1D02J0", 0}}},
	{"message_11", {{";020ssAuho;N?PeNwjOAp<70089A", 0}}},
	{"message_18", {{"B000000000H0htY08D41qwv00000", 0}}},
	{"message_19", {{"C000000000H0htY08D41qwv0000000000000000000000000000@", 0}}},
	{"message_21", {{"E@28isPVa9Qh:0a90SWW0h@@@@@@2kJP;hHP@00003v0100", 2}}},
	{"message_22", {{"F000000000000000000000000000", 0}}},
	{"message_23", {{"G00000000000000000000000000", 2}}},
	{"message_24", {{"H000004000000000000000000000", 0}}},
};

static void all_messages(benchmark::internal::Benchmark * b)
{
	for (std::size_t i = 0; i < messages.size(); ++i) {
		b->Arg(i);
	}
}
}

static void Benchmark_make_message(benchmark::State & state)
{
	state.SetLabel(messages[state.range(0)].label);
	while (state.KeepRunning()) {
		auto tmp = marnav::ais::make_message(messages[state.range(0)].data);
		benchmark::DoNotOptimize(tmp);
	}
}

BENCHMARK(Benchmark_make_message)->Apply(all_messages);

BENCHMARK_MAIN();
