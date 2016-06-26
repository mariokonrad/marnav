#include <benchmark/benchmark_api.h>
#include <algorithm>
#include <typeindex>
#include <marnav/nmea/aam.hpp>
#include <marnav/nmea/alm.hpp>
#include <marnav/nmea/apb.hpp>
#include <marnav/nmea/bod.hpp>
#include <marnav/nmea/bwc.hpp>
#include <marnav/nmea/bwr.hpp>
#include <marnav/nmea/bww.hpp>
#include <marnav/nmea/dbk.hpp>
#include <marnav/nmea/dbt.hpp>
#include <marnav/nmea/dpt.hpp>
#include <marnav/nmea/dsc.hpp>
#include <marnav/nmea/dse.hpp>
#include <marnav/nmea/dtm.hpp>
#include <marnav/nmea/fsi.hpp>
#include <marnav/nmea/gbs.hpp>
#include <marnav/nmea/gga.hpp>
#include <marnav/nmea/glc.hpp>
#include <marnav/nmea/gll.hpp>
#include <marnav/nmea/gns.hpp>
#include <marnav/nmea/grs.hpp>
#include <marnav/nmea/gsa.hpp>
#include <marnav/nmea/gst.hpp>
#include <marnav/nmea/gsv.hpp>
#include <marnav/nmea/gtd.hpp>
#include <marnav/nmea/hdg.hpp>
#include <marnav/nmea/hfb.hpp>
#include <marnav/nmea/hdm.hpp>
#include <marnav/nmea/hsc.hpp>
#include <marnav/nmea/its.hpp>
#include <marnav/nmea/lcd.hpp>
#include <marnav/nmea/msk.hpp>
#include <marnav/nmea/mss.hpp>
#include <marnav/nmea/mtw.hpp>
#include <marnav/nmea/mwd.hpp>
#include <marnav/nmea/mwv.hpp>
#include <marnav/nmea/osd.hpp>
#include <marnav/nmea/r00.hpp>
#include <marnav/nmea/rma.hpp>
#include <marnav/nmea/rmb.hpp>
#include <marnav/nmea/rmc.hpp>
#include <marnav/nmea/rot.hpp>
#include <marnav/nmea/rpm.hpp>
#include <marnav/nmea/rsa.hpp>
#include <marnav/nmea/rsd.hpp>
#include <marnav/nmea/rte.hpp>
#include <marnav/nmea/sfi.hpp>
#include <marnav/nmea/tds.hpp>
#include <marnav/nmea/tfi.hpp>
#include <marnav/nmea/tll.hpp>
#include <marnav/nmea/tpc.hpp>
#include <marnav/nmea/tpr.hpp>
#include <marnav/nmea/tpt.hpp>
#include <marnav/nmea/ttm.hpp>
#include <marnav/nmea/vbw.hpp>
#include <marnav/nmea/vdm.hpp>
#include <marnav/nmea/vdo.hpp>
#include <marnav/nmea/vdr.hpp>
#include <marnav/nmea/vhw.hpp>
#include <marnav/nmea/vlw.hpp>
#include <marnav/nmea/vpw.hpp>
#include <marnav/nmea/vtg.hpp>
#include <marnav/nmea/vwr.hpp>
#include <marnav/nmea/wcv.hpp>
#include <marnav/nmea/wnc.hpp>
#include <marnav/nmea/wpl.hpp>
#include <marnav/nmea/xdr.hpp>
#include <marnav/nmea/xte.hpp>
#include <marnav/nmea/xtr.hpp>
#include <marnav/nmea/zda.hpp>
#include <marnav/nmea/zdl.hpp>
#include <marnav/nmea/zfo.hpp>
#include <marnav/nmea/ztg.hpp>
#include <marnav/nmea/pgrme.hpp>
#include <marnav/nmea/nmea.hpp>

using namespace marnav;

namespace
{
struct sentence_data {
	std::type_index type;
	std::string tag;
	std::string text;
};

#define INFO(s, text)                                        \
	{                                                        \
		std::type_index(typeid(nmea::s)), nmea::s::TAG, text \
	}

// clang-format off
static std::vector<sentence_data> sentences = {
	INFO(aam, "$GPAAM,A,A,0.5,N,POINT1*6E"),
	INFO(alm, "$GPALM,1,1,15,1159,00,441d,4e,16be,fd5e,a10c9f,4a2da4,686e81,58cbe1,0a4,001*77"),
	INFO(apb, "$GPAPB,A,A,0.10,R,N,V,V,011,M,DEST,011,M,011,M*3C"),
	INFO(bod, "$GPBOD,12.5,T,,,,*12"),
	INFO(bwc, "$GPBWC,220516,5130.02,N,00046.34,W,213.8,T,218.0,M,0004.6,N,EGLM,A*4C"),
	INFO(bwr, "$GPBWR,220516,5130.02,N,00046.34,W,213.8,T,218.0,M,0004.6,N,EGLM*30"),
	INFO(bww, "$GPBWW,213.8,T,218.0,M,POINT1,POINT2*4C"),
	INFO(dbk, "$IIDBK,9.3,f,1.2,M,3.4,F*00"),
	INFO(dbt, "$IIDBT,9.3,f,2.84,M,1.55,F*14"),
	INFO(dpt, "$IIDPT,9.3,1.0*4B"),
	INFO(dsc, "$CDDSC,20,3380210040,00,21,26,1394807410,2242,,,B,E*71"),
	INFO(dse, "$CDDSE,1,1,A,3664251410,00,47800350*1D"),
	INFO(dtm, "$GPDTM,W84,,0.000000,N,0.000000,E,0.0,W84*6F"),
	INFO(fsi, "$GPFSI,156000,156025,,,*60"),
	INFO(gbs, "$GPGBS,123456.32,1.0,2.0,3.0,034,0.1,1.2,0.6*5A"),
	INFO(gga, "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47"),
	INFO(glc, "$GPGLC,1,1,A,1,A,2,A,3,A,4,V,,*21"),
	INFO(gll, "$GPGLL,3553.5295,N,13938.6570,E,002454,A,A*4F"),
	INFO(gns, "$GNGNS,122310.0,3722.42567,N,12258.856215,W,AA,15,0.9,1005.54,6.5,,*75"),
	INFO(grs, "$GPGRS,024603.00,1,-1.8,-2.7,0.3,,,,,,,,,*6C"),
	INFO(gsa, "$GPGSA,A,3,07,08,09,11,18,23,26,28,29,,,,6.6,2.0,3.0*38"),
	INFO(gst, "$GPGST,123456.34,1.0,2.1,3.2,4.3,5.4,6.5,7.6*50"),
	INFO(gsv, "$GPGSV,3,1,09,07,29,138,44,08,22,099,42,09,30,273,44,11,07,057,35*75"),
	INFO(gtd, "$GPGTD,1.0,2.0,3.0,4.0,5.0*43"),
	INFO(hdg, "$HCHDG,45.8,,,0.6,E*16"),
	INFO(hfb, "$GPHFB,1.0,M,2.0,M*58"),
	INFO(hdm, "$HCHDM,45.8,M*10"),
	INFO(hsc, "$GPHSC,45.8,T,,*0C"),
	INFO(its, "$GPITS,1.0,M*3B"),
	INFO(lcd, "$GPLCD,1,001,000,001,000,002,000,003,000,004,000,,*44"),
	INFO(msk, "$GPMSK,123,A,110,M,321*52"),
	INFO(mss, "$GPMSS,12,34,123,456,1*44"),
	INFO(mtw, "$IIMTW,9.5,C*2F"),
	INFO(mwd, "$WIMWD,12.4,T,,,,,,*0D"),
	INFO(mwv, "$IIMWV,084.0,R,10.4,N,A*04"),
	INFO(osd, "$IIOSD,123.4,A,,,,,,,*1F"),
	INFO(r00, "$GPR00,EGLL,EGLM,EGTB,EGUB,EGTK,MBOT,EGTB,,,,,,,*58"),
	INFO(rma, "$GPRMA,,1234.9333,N,,,,,,,,*0B"),
	INFO(rmb, "$GPRMB,A,0.00,L,SIM001,SIM002,5102.6069,N,00500.0000,E,002.4,000.,021.7,V*0D"),
	INFO(rmc, "$GPRMC,201126,A,4702.3944,N,00818.3381,E,0.0,328.4,260807,0.6,E,A*1E"),
	INFO(rot, "$GPROT,1.0,A*30"),
	INFO(rpm, "$IIRPM,S,1,1800.0,5.0,A*7C"),
	INFO(rsa, "$IIRSA,1.0,A,,*2E"),
	INFO(rsd, "$IIRSD,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,A,A*47"),
	INFO(rte, "$GPRTE,1,1,c,*37"),
	INFO(sfi, "$GPSFI,1,1,156025,M*03"),
	INFO(tds, "$GPTDS,12.3,M*07"),
	INFO(tfi, "$GPTFI,0,1,2*53"),
	INFO(tll, "$GPTLL,00,0000.0000,N,00000.0000,E,,000000,T,*00"),
	INFO(tpc, "$GPTPC,1.0,M,2.0,M,3.0,M*33"),
	INFO(tpr, "$GPTPR,1.0,M,2.0,P,3.0,M*3F"),
	INFO(tpt, "$GPTPT,1.0,M,2.0,P,3.0,M*39"),
	INFO(ttm, "$GPTTM,,,,,,,,,,,,,*76"),
	INFO(vbw, "$IIVBW,1.0,-1.5,A,1.0,0.5,A*6F"),
	INFO(vdm, "!AIVDM,1,1,,B,177KQJ5000G?tO`K>RA1wUbN0TKH,0*5C"),
	INFO(vdo, "!AIVDO,1,1,,B,177KQJ5000G?tO`K>RA1wUbN0TKH,0*5E"),
	INFO(vdr, "$IIVDR,211.0,T,1.00,M,1.25,N*3C"),
	INFO(vhw, "$IIVHW,,T,211.0,M,0.00,N,0.00,K*79"),
	INFO(vlw, "$IIVLW,7803.2,N,0.00,N*43"),
	INFO(vpw, "$IIVPW,4.5,N,6.7,M*52"),
	INFO(vtg, "$GPVTG,156.1,T,140.9,M,0.0,N,0.0,K*41"),
	INFO(vwr, "$IIVWR,084.0,R,10.4,N,5.4,M,19.3,K*4A"),
	INFO(wcv, "$GPWCV,12.3,N,POINT1*54"),
	INFO(wnc, "$GPWNC,12.3,N,5.6,K,POINT1,POINT2*78"),
	INFO(wpl, "$GPWPL,12.3,N,123.4,E,POINT1*32"),
	INFO(xdr, "$YXXDR,a,16.0,M,abc*1A"),
	INFO(xte, "$GPXTE,,,,,,*5E"),
	INFO(xtr, "$GPXTR,,,*65"),
	INFO(zda, "$GPZDA,050306,29,10,2003,,*43"),
	INFO(zdl, "$GPZDL,383401,12.3,R*28"),
	INFO(zfo, "$GPZFO,123456.1,000010,POINT1*0C"),
	INFO(ztg, "$GPZTG,123456.1,000010,POINT1*16"),
	INFO(pgrme, "$PGRME,22.0,M,52.9,M,51.0,M*14"),
};
// clang-format on

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

template <class T> static void specific(benchmark::internal::Benchmark * b)
{
	const auto i = std::find_if(sentences.begin(), sentences.end(),
		[](const std::vector<sentence_data>::value_type & v) { return T::TAG == v.tag; });
	b->Arg(std::distance(sentences.begin(), i));
}
}

static void Benchmark_make_sentence(benchmark::State & state)
{
	state.SetLabel(sentences[state.range_x()].tag);
	while (state.KeepRunning()) {
		auto tmp = nmea::make_sentence(sentences[state.range_x()].text);
		benchmark::DoNotOptimize(tmp);
	}
}

BENCHMARK(Benchmark_make_sentence)->Apply(all_sentences);

template <class T> static void Benchmark_create_sentence(benchmark::State & state)
{
	state.SetLabel(sentences[state.range_x()].tag);
	while (state.KeepRunning()) {
		auto tmp = nmea::create_sentence<T>(sentences[state.range_x()].text);
		benchmark::DoNotOptimize(tmp);
	}
}

BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::aam)->Apply(specific<nmea::aam>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::alm)->Apply(specific<nmea::alm>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::apb)->Apply(specific<nmea::apb>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::bod)->Apply(specific<nmea::bod>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::bwc)->Apply(specific<nmea::bwc>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::bwr)->Apply(specific<nmea::bwr>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::bww)->Apply(specific<nmea::bww>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::dbk)->Apply(specific<nmea::dbk>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::dbt)->Apply(specific<nmea::dbt>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::dpt)->Apply(specific<nmea::dpt>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::dsc)->Apply(specific<nmea::dsc>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::dse)->Apply(specific<nmea::dse>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::dtm)->Apply(specific<nmea::dtm>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::fsi)->Apply(specific<nmea::fsi>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::gbs)->Apply(specific<nmea::gbs>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::gga)->Apply(specific<nmea::gga>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::glc)->Apply(specific<nmea::glc>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::gll)->Apply(specific<nmea::gll>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::gns)->Apply(specific<nmea::gns>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::grs)->Apply(specific<nmea::grs>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::gsa)->Apply(specific<nmea::gsa>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::gst)->Apply(specific<nmea::gst>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::gsv)->Apply(specific<nmea::gsv>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::gtd)->Apply(specific<nmea::gtd>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::hdg)->Apply(specific<nmea::hdg>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::hfb)->Apply(specific<nmea::hfb>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::hdm)->Apply(specific<nmea::hdm>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::hsc)->Apply(specific<nmea::hsc>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::its)->Apply(specific<nmea::its>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::lcd)->Apply(specific<nmea::lcd>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::msk)->Apply(specific<nmea::msk>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::mss)->Apply(specific<nmea::mss>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::mtw)->Apply(specific<nmea::mtw>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::mwd)->Apply(specific<nmea::mwd>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::mwv)->Apply(specific<nmea::mwv>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::osd)->Apply(specific<nmea::osd>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::r00)->Apply(specific<nmea::r00>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::rma)->Apply(specific<nmea::rma>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::rmb)->Apply(specific<nmea::rmb>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::rmc)->Apply(specific<nmea::rmc>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::rot)->Apply(specific<nmea::rot>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::rpm)->Apply(specific<nmea::rpm>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::rsa)->Apply(specific<nmea::rsa>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::rsd)->Apply(specific<nmea::rsd>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::rte)->Apply(specific<nmea::rte>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::sfi)->Apply(specific<nmea::sfi>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::tds)->Apply(specific<nmea::tds>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::tfi)->Apply(specific<nmea::tfi>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::tll)->Apply(specific<nmea::tll>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::tpc)->Apply(specific<nmea::tpc>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::tpr)->Apply(specific<nmea::tpr>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::tpt)->Apply(specific<nmea::tpt>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::ttm)->Apply(specific<nmea::ttm>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::vbw)->Apply(specific<nmea::vbw>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::vdm)->Apply(specific<nmea::vdm>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::vdo)->Apply(specific<nmea::vdo>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::vdr)->Apply(specific<nmea::vdr>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::vhw)->Apply(specific<nmea::vhw>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::vlw)->Apply(specific<nmea::vlw>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::vpw)->Apply(specific<nmea::vpw>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::vtg)->Apply(specific<nmea::vtg>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::vwr)->Apply(specific<nmea::vwr>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::wcv)->Apply(specific<nmea::wcv>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::wnc)->Apply(specific<nmea::wnc>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::wpl)->Apply(specific<nmea::wpl>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::xdr)->Apply(specific<nmea::xdr>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::xte)->Apply(specific<nmea::xte>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::xtr)->Apply(specific<nmea::xtr>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::zda)->Apply(specific<nmea::zda>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::zdl)->Apply(specific<nmea::zdl>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::zfo)->Apply(specific<nmea::zfo>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::ztg)->Apply(specific<nmea::ztg>);
BENCHMARK_TEMPLATE(Benchmark_create_sentence, nmea::pgrme)->Apply(specific<nmea::pgrme>);

static void Benchmark_extract_id(benchmark::State & state)
{
	state.SetLabel(sentences[state.range_x()].tag);
	while (state.KeepRunning()) {
		auto tmp = nmea::extract_id(sentences[state.range_x()].text);
		benchmark::DoNotOptimize(tmp);
	}
}

BENCHMARK(Benchmark_extract_id)->Apply(all_sentences);

BENCHMARK_MAIN()
