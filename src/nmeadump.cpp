// This is a diagnostics tool and also serves as demonstration
// on how to use the library.
//
// This tool is able to read data fromm stdin, file or a serial
// port.
//
// Usage, read from file:
//
//   nmeadump -f logged-data.txt
//
// Usage, read from NMEA-0183 port:
//
//   nmeadump -p /dev/ttyUSB0 -s 4800
//
// Usage, read from NMEA-0183-HS port:
//
//   nmeadump -p /dev/ttyUSB0 -s 38400
//
// Usage, read from stdin:
//
//   cat logged-data.txt | nmeadump
//

#include <marnav/nmea/ais_helper.hpp>
#include <marnav/nmea/checksum.hpp>
#include <marnav/nmea/name.hpp>
#include <marnav/nmea/nmea.hpp>
#include <marnav/nmea/route.hpp>
#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/string.hpp>
#include <marnav/nmea/waypoint.hpp>

#include <marnav/nmea/aam.hpp>
#include <marnav/nmea/alm.hpp>
#include <marnav/nmea/apa.hpp>
#include <marnav/nmea/apb.hpp>
#include <marnav/nmea/bec.hpp>
#include <marnav/nmea/bod.hpp>
#include <marnav/nmea/bwc.hpp>
#include <marnav/nmea/bwr.hpp>
#include <marnav/nmea/bww.hpp>
#include <marnav/nmea/dbt.hpp>
#include <marnav/nmea/dpt.hpp>
//#include <marnav/nmea/dsc.hpp>
//#include <marnav/nmea/dse.hpp>
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
#include <marnav/nmea/hdt.hpp>
#include <marnav/nmea/hsc.hpp>
#include <marnav/nmea/its.hpp>
#include <marnav/nmea/lcd.hpp>
#include <marnav/nmea/mob.hpp>
#include <marnav/nmea/msk.hpp>
#include <marnav/nmea/mss.hpp>
#include <marnav/nmea/mta.hpp>
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
#include <marnav/nmea/stn.hpp>
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
#include <marnav/nmea/vwe.hpp>
#include <marnav/nmea/vwr.hpp>
#include <marnav/nmea/wcv.hpp>
#include <marnav/nmea/wdc.hpp>
#include <marnav/nmea/wdr.hpp>
#include <marnav/nmea/wnc.hpp>
#include <marnav/nmea/wpl.hpp>
#include <marnav/nmea/xdr.hpp>
#include <marnav/nmea/xte.hpp>
#include <marnav/nmea/xtr.hpp>
#include <marnav/nmea/zda.hpp>
#include <marnav/nmea/zdl.hpp>
#include <marnav/nmea/zfi.hpp>
#include <marnav/nmea/zfo.hpp>
#include <marnav/nmea/zlz.hpp>
#include <marnav/nmea/zpi.hpp>
#include <marnav/nmea/zta.hpp>
#include <marnav/nmea/zte.hpp>
#include <marnav/nmea/ztg.hpp>
#include <marnav/nmea/pgrme.hpp>
#include <marnav/nmea/pgrmm.hpp>
#include <marnav/nmea/pgrmz.hpp>
#include <marnav/nmea/stalk.hpp>

#include <marnav/ais/ais.hpp>
#include <marnav/ais/name.hpp>

#include <marnav/ais/message_01.hpp>
#include <marnav/ais/message_02.hpp>
#include <marnav/ais/message_03.hpp>
#include <marnav/ais/message_04.hpp>
#include <marnav/ais/message_05.hpp>
#include <marnav/ais/message_06.hpp>
#include <marnav/ais/message_07.hpp>
#include <marnav/ais/message_08.hpp>
#include <marnav/ais/message_09.hpp>
#include <marnav/ais/message_10.hpp>
#include <marnav/ais/message_11.hpp>
#include <marnav/ais/message_12.hpp>
#include <marnav/ais/message_13.hpp>
#include <marnav/ais/message_14.hpp>
#include <marnav/ais/message_17.hpp>
#include <marnav/ais/message_18.hpp>
#include <marnav/ais/message_19.hpp>
#include <marnav/ais/message_20.hpp>
#include <marnav/ais/message_21.hpp>
#include <marnav/ais/message_22.hpp>
#include <marnav/ais/message_23.hpp>
#include <marnav/ais/message_24.hpp>
#include <marnav/ais/binary_001_11.hpp>
#include <marnav/ais/binary_200_10.hpp>

#include <marnav/io/default_nmea_reader.hpp>
#include <marnav/io/serial.hpp>

#include <marnav/units/units.hpp>

#include <marnav/utils/unique.hpp>
#include <marnav/utils/mmsi_country.hpp>

#include <cxxopts.hpp>

#include <fmt/format.h>
#include <fmt/printf.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace nmeadump
{
namespace terminal
{
static constexpr const char * normal = "\033[0m";
static constexpr const char * black = "\033[30m";
static constexpr const char * red = "\033[31m";
static constexpr const char * green = "\033[32m";
static constexpr const char * yellow = "\033[33m";
static constexpr const char * blue = "\033[34m";
static constexpr const char * magenta = "\033[35m";
static constexpr const char * cyan = "\033[36m";
static constexpr const char * white = "\033[37m";
}

namespace
{
template <class Container>
static bool contains(
	const Container & container, const typename Container::value_type & element)
{
	return std::find(std::begin(container), std::end(container), element)
		!= std::end(container);
}
}

static struct {
	struct {
		std::string port;
		marnav::io::serial::baud speed;
		std::string file;
		std::string input_string;
	} config;
} global;

static bool parse_options(int argc, char ** argv)
{
	uint32_t port_speed = 0;

	// clang-format off
	cxxopts::Options options{argv[0], "NMEA Dump"};
	options.add_options()
		("h,help",
			"Shows help information.")
		("p,port",
			"Specifies the port to use.",
			cxxopts::value<std::string>(global.config.port))
		("s,speed",
			"Specifies the port speed. Valid values: 4800, 38400",
			cxxopts::value<uint32_t>(port_speed))
		("f,file",
			"Specifies the file to use.",
			cxxopts::value<std::string>(global.config.file))
		("i,input",
			"String to parse",
			cxxopts::value<std::string>(global.config.input_string))
		;
	// clang-format on

	const auto args = options.parse(argc, argv);

	if (args.count("help")) {
		fmt::printf("%s\n", options.help());
		fmt::printf("If no file or port is specified, stdin is used to read data from.\n\n");
		return true;
	}

	// validation

	static const std::vector<uint32_t> valid_port_speeds = {4800, 38400};

	if (args.count("port") && args.count("file"))
		throw std::runtime_error{"specifying port and file is illegal"};
	if (args.count("port") && !contains(valid_port_speeds, port_speed))
		throw std::runtime_error{"invalid port speed"};

	switch (port_speed) {
		case 4800:
			global.config.speed = marnav::io::serial::baud::baud_4800;
			break;
		case 38400:
			global.config.speed = marnav::io::serial::baud::baud_38400;
			break;
		default:
			break;
	}

	return false;
}

static std::string trim(const std::string & s)
{
	static const char * whitespace = "\n\r\t ";
	const auto begin = s.find_first_not_of(whitespace);
	const auto end = s.find_last_not_of(whitespace);
	return begin != std::string::npos ? s.substr(begin, end - begin + 1) : "";
}

/// @cond DEV
namespace detail
{
template <typename T>
static std::string render(const T & t)
{
	return marnav::nmea::to_string(t);
}

static std::string render(const std::string & t)
{
	return t;
}

static std::string render(bool t)
{
	return t ? "true" : "false";
}

static std::string render(char t)
{
	return fmt::sprintf("%c", t);
}

static std::string render(const uint32_t t)
{
	return fmt::sprintf("%u", t);
}

static std::string render(const int32_t t)
{
	return fmt::sprintf("%d", t);
}

static std::string render(const uint8_t t)
{
	return fmt::sprintf("%u", t);
}

static std::string render(const double t)
{
	return fmt::sprintf("%-8.3f", t);
}

static std::string render(const marnav::utils::mmsi & t)
{
	const auto country = mmsi_country(t).name;
	if (!country.empty())
		return fmt::sprintf(
			"%09u (%s)", static_cast<marnav::utils::mmsi::value_type>(t), country);
	return fmt::sprintf("%09u", static_cast<marnav::utils::mmsi::value_type>(t));
}

static std::string render(const marnav::nmea::time & t)
{
	return fmt::sprintf("%02u:%02u:%02u", t.hour(), t.minutes(), t.seconds());
}

static std::string render(const marnav::geo::latitude & t)
{
	using namespace marnav::nmea;
	return fmt::sprintf(
		" %02u\u00b0%02u'%04.1f%s", t.degrees(), t.minutes(), t.seconds(), to_string(t.hem()));
}

static std::string render(const marnav::geo::longitude & t)
{
	using namespace marnav::nmea;
	return fmt::sprintf(
		"%03u\u00b0%02u'%04.1f%s", t.degrees(), t.minutes(), t.seconds(), to_string(t.hem()));
}

static std::string render(const marnav::geo::position & p)
{
	using namespace marnav::nmea;
	return fmt::sprintf("%s %s", render(p.lat()), render(p.lon()));
}

static std::string render(const marnav::ais::message_23::report_interval t)
{
	switch (t) {
		case marnav::ais::message_23::report_interval::autonomous_mode:
			return "Autonomous Mode";
		case marnav::ais::message_23::report_interval::minutes_10:
			return "Minutes 10";
		case marnav::ais::message_23::report_interval::minutes_06:
			return "Minutes  6";
		case marnav::ais::message_23::report_interval::minutes_03:
			return "Minutes  3";
		case marnav::ais::message_23::report_interval::minutes_01:
			return "Minutes  1";
		case marnav::ais::message_23::report_interval::seconds_30:
			return "Seconds 30";
		case marnav::ais::message_23::report_interval::seconds_15:
			return "Seconds 15";
		case marnav::ais::message_23::report_interval::seconds_10:
			return "Seconds 10";
		case marnav::ais::message_23::report_interval::seconds_05:
			return "Seconds  5";
		case marnav::ais::message_23::report_interval::next_shorter:
			return "Next Shorter";
		case marnav::ais::message_23::report_interval::next_longer:
			return "Next Longer";
	}
	return "-";
}

static std::string render(const marnav::ais::message_24::part t)
{
	switch (t) {
		case marnav::ais::message_24::part::A:
			return "A";
		case marnav::ais::message_24::part::B:
			return "B";
	}
	return "-";
}

static std::string render(const marnav::ais::binary_001_11::trend t)
{
	switch (t) {
		case marnav::ais::binary_001_11::trend::steady:
			return "steady";
		case marnav::ais::binary_001_11::trend::decreasing:
			return "decreasing ";
		case marnav::ais::binary_001_11::trend::increasing:
			return "increasing";
		case marnav::ais::binary_001_11::trend::not_available:
			return "not available";
	}
	return "-";
}

static std::string render(const marnav::ais::binary_001_11::ice t)
{
	switch (t) {
		case marnav::ais::binary_001_11::ice::no:
			return "no";
		case marnav::ais::binary_001_11::ice::yes:
			return "yes";
		case marnav::ais::binary_001_11::ice::not_available:
			return "not available";
	}
	return "-";
}

static std::string render(const marnav::ais::binary_001_11::precipitation t)
{
	switch (t) {
		case marnav::ais::binary_001_11::precipitation::rain:
			return "rain";
		case marnav::ais::binary_001_11::precipitation::thunderstorm:
			return "thunderstorm";
		case marnav::ais::binary_001_11::precipitation::freezing_rain:
			return "freezing_rain";
		case marnav::ais::binary_001_11::precipitation::mixed_ice:
			return "mixed_ice";
		case marnav::ais::binary_001_11::precipitation::snow:
			return "snow";
		case marnav::ais::binary_001_11::precipitation::not_available:
			return "not available";
	}
	return "-";
}

static std::string render(const marnav::ais::binary_200_10::loaded_state t)
{
	switch (t) {
		case marnav::ais::binary_200_10::loaded_state::not_available:
			return "not available";
		case marnav::ais::binary_200_10::loaded_state::unloaded:
			return "unloaded";
		case marnav::ais::binary_200_10::loaded_state::loaded:
			return "loaded";
	}
	return "-";
}

static std::string render(const marnav::ais::rate_of_turn t)
{
	if (!t.available())
		return "not available";
	if (t.is_not_turning())
		return "not turning";
	if (t.is_more_5deg30s_right())
		return "more 5deg/30s right";
	if (t.is_more_5deg30s_left())
		return "more 5deg/30s left";
	return fmt::sprintf("%f", t.value());
}

static std::string render(const marnav::ais::ship_type t)
{
	return marnav::ais::to_name(t);
}

static std::string render(const marnav::ais::epfd_fix_type t)
{
	return marnav::ais::to_name(t);
}

static std::string render(const marnav::ais::off_position_indicator t)
{
	return marnav::ais::to_name(t);
}

static std::string render(const marnav::ais::virtual_aid t)
{
	return marnav::ais::to_name(t);
}

static std::string render(const marnav::ais::aid_type_id t)
{
	return marnav::ais::to_name(t);
}

static std::string render(const marnav::ais::message_id t)
{
	return marnav::ais::to_name(t);
}

static std::string render(const marnav::ais::maneuver_indicator_id t)
{
	return marnav::ais::to_name(t);
}

static std::string render(const marnav::ais::data_terminal t)
{
	return marnav::ais::to_name(t);
}

static std::string render(const marnav::ais::navigation_status t)
{
	return marnav::ais::to_name(t);
}

static std::string render(const marnav::nmea::mob::mob_status t)
{
	switch (t) {
		case marnav::nmea::mob::mob_status::mob_activated:
			return "mob activated";
		case marnav::nmea::mob::mob_status::test_mode:
			return "test mode";
		case marnav::nmea::mob::mob_status::manual_button:
			return "manual button";
		case marnav::nmea::mob::mob_status::mob_not_in_use:
			return "mob not in use";
		case marnav::nmea::mob::mob_status::error:
			return "error";
	}
	return "-";
}

static std::string render(const marnav::nmea::mob::mob_position_source t)
{
	switch (t) {
		case marnav::nmea::mob::mob_position_source::position_estimated:
			return "position estimated";
		case marnav::nmea::mob::mob_position_source::position_reported:
			return "position reported";
		case marnav::nmea::mob::mob_position_source::reserved:
			return "reserved";
		case marnav::nmea::mob::mob_position_source::error:
			return "error";
	}
	return "-";
}

static std::string render(const marnav::nmea::mob::battery_status t)
{
	switch (t) {
		case marnav::nmea::mob::battery_status::good:
			return "good";
		case marnav::nmea::mob::battery_status::low:
			return "low";
		case marnav::nmea::mob::battery_status::reserved:
			return "reserved";
		case marnav::nmea::mob::battery_status::error:
			return "error";
	}
	return "-";
}

static std::string render(const marnav::nmea::tfi::state t)
{
	switch (t) {
		case marnav::nmea::tfi::state::off:
			return "OFF";
		case marnav::nmea::tfi::state::on:
			return "ON";
		case marnav::nmea::tfi::state::no_answer:
			return "no answer";
	}
	return "-";
}

static std::string render(const marnav::nmea::sentence_id t)
{
	return marnav::nmea::to_name(t);
}

static std::string render(const marnav::nmea::talker t)
{
	return marnav::nmea::to_name(t);
}

static std::string render(const marnav::nmea::unit::distance t)
{
	return marnav::nmea::to_name(t);
}

static std::string render(const marnav::nmea::unit::temperature t)
{
	return marnav::nmea::to_name(t);
}

static std::string render(const marnav::nmea::unit::velocity t)
{
	return marnav::nmea::to_name(t);
}

static std::string render(const marnav::nmea::side t)
{
	return marnav::nmea::to_name(t);
}

static std::string render(const marnav::nmea::reference t)
{
	return marnav::nmea::to_name(t);
}

static std::string render(const marnav::nmea::quality t)
{
	return marnav::nmea::to_name(t);
}

static std::string render(const marnav::nmea::direction t)
{
	return marnav::nmea::to_string(t);
}

static std::string render(const marnav::nmea::selection_mode t)
{
	return marnav::nmea::to_name(t);
}

static std::string render(const marnav::nmea::status t)
{
	return marnav::nmea::to_name(t);
}

static std::string render(const marnav::nmea::route_mode t)
{
	return marnav::nmea::to_name(t);
}

static std::string render(const marnav::nmea::route & t)
{
	return t.c_str();
}

static std::string render(const marnav::nmea::waypoint & t)
{
	return t.c_str();
}

static std::string render(const marnav::nmea::mode_indicator t)
{
	return marnav::nmea::to_name(t);
}

static std::string render(const std::vector<uint8_t> & t)
{
	std::string s;
	s.reserve(t.size() * 3 - 1);
	for (auto i = begin(t); i != end(t); ++i)
		s.append(fmt::sprintf(((i == begin(t)) ? "%02x" : " %02x"), *i));
	return s;
}

static std::string render(const marnav::units::nautical_miles & t)
{
	return fmt::sprintf("%s %s", render(t.value()), render(marnav::nmea::unit::distance::nm));
}

static std::string render(const marnav::units::knots & t)
{
	return fmt::sprintf("%s %s", render(t.value()), render(marnav::nmea::unit::velocity::knot));
}

static std::string render(const marnav::units::meters & t)
{
	return fmt::sprintf(
		"%s %s", render(t.value()), render(marnav::nmea::unit::distance::meter));
}

static std::string render(const marnav::units::feet & t)
{
	return fmt::sprintf("%s %s", render(t.value()), render(marnav::nmea::unit::distance::feet));
}

static std::string render(const marnav::units::meters_per_second & t)
{
	return fmt::sprintf("%s %s", render(t.value()), render(marnav::nmea::unit::velocity::mps));
}

static std::string render(const marnav::units::celsius & t)
{
	return fmt::sprintf(
		"%s %s", render(t.value()), render(marnav::nmea::unit::temperature::celsius));
}

static std::string render(const marnav::units::length & t)
{
	// all lengths are rendered in meters by default
	return render(t.get<marnav::units::meters>());
}

static std::string render(const marnav::units::velocity & t)
{
	// all velocities are rendered in knots by default
	return render(t.get<marnav::units::knots>());
}

static std::string render(const marnav::units::temperature & t)
{
	// all temperatures are rendered in celsius by default
	return render(t.get<marnav::units::celsius>());
}

template <typename T>
static std::string render(const marnav::utils::optional<T> & t)
{
	if (!t)
		return "-";
	return render(*t);
}

static void print(const std::string & name, const std::string & value)
{
	fmt::printf("\t%-30s : %s\n", name, value);
}

static void print(const std::string & title)
{
	fmt::printf("\t%s\n", title);
}

static void print_detail_hdg(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::hdg>(s);
	print("Heading", render(t->get_heading()));
	print("Magn Deviation",
		fmt::sprintf("%s %s", render(t->get_magn_dev()), render(t->get_magn_dev_hem())));
	print("Magn Variation",
		fmt::sprintf("%s %s", render(t->get_magn_var()), render(t->get_magn_var_hem())));
}

static void print_detail_hfb(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::hfb>(s);
	print("Distance Head Foot [m]", render(t->get_distance_head_foot()));
	print("Distance Head Bottom [m]", render(t->get_distance_head_bottom()));
}

static void print_detail_hdm(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::hdm>(s);
	print("Heading", render(t->get_heading()));
}

static void print_detail_hdt(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::hdt>(s);
	print("Heading", render(t->get_heading()));
}

static void print_detail_hsc(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::hsc>(s);
	print("Heading True", render(t->get_heading_true()));
	print("Heading Magnetic", render(t->get_heading_mag()));
}

static void print_detail_its(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::its>(s);
	print("Distance [m]", render(t->get_distance()));
}

static void print_detail_lcd(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::lcd>(s);
	print("GRI microseconds", render(t->get_gri()));
	print("Master", fmt::sprintf("SNR:%d  ECD:%d", t->get_master().snr, t->get_master().ecd));
	for (int i = 0; i < marnav::nmea::lcd::max_differences; ++i) {
		const auto diff = t->get_time_diff(i);
		if (diff) {
			print(fmt::sprintf("Time Diff %d", i),
				fmt::sprintf("SNR:%d  ECD:%d", diff->snr, diff->ecd));
		}
	}
}

static void print_detail_mob(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::mob>(s);
	print("MOB Emitter ID", render(t->get_emitter_id()));
	print("MOB Status", render(t->get_mob_status()));
	print("MOB Time UTC", render(t->get_mob_activation_utc()));
	print("MOB Position Source", render(t->get_mob_position_source()));
	print("Date of Position", render(t->get_position_date()));
	print("Time of Position", render(t->get_position_time()));
	print("Latitude", render(t->get_lat()));
	print("Longitude", render(t->get_lon()));
	print("COG", render(t->get_cog()));
	print("SOG", render(t->get_sog()));
	print("MMSI", render(t->get_mmsi()));
	print("Battery Status", render(t->get_battery_status()));
}

static void print_detail_msk(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::msk>(s);
	print("Frequency to use", render(t->get_frequency()));
	print("Frequency Mode", render(t->get_frequency_mode()));
	print("Beacon Bit Rate", render(t->get_bitrate()));
	print("Beacon Mode", render(t->get_bitrate_mode()));
	print("Frequency for MSS message status", render(t->get_frequency_mss_status()));
}

static void print_detail_rmb(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::rmb>(s);
	print("Active", render(t->get_active()));
	print("Cross Track Error", render(t->get_cross_track_error()));
	print("Waypoint From", render(t->get_waypoint_from()));
	print("Waypoint To", render(t->get_waypoint_to()));
	print("Latitude", render(t->get_lat()));
	print("Longitude", render(t->get_lon()));
	print("Range", render(t->get_range()));
	print("Bearing", render(t->get_bearing()));
	print("Dest. Velocity", render(t->get_dst_velocity()));
	print("Arrival Status", render(t->get_arrival_status()));
	print("Mode Indicator", render(t->get_mode_ind()));
}

static void print_detail_rmc(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::rmc>(s);
	print("Time UTC", render(t->get_time_utc()));
	print("Status", render(t->get_status()));
	print("Latitude", render(t->get_lat()));
	print("Longitude", render(t->get_lon()));
	print("SOG", render(t->get_sog()));
	print("Heading", render(t->get_heading()));
	print("Date", render(t->get_date()));
	print("Magn Dev", fmt::sprintf("%s %s", render(t->get_mag()), render(t->get_mag_hem())));
	print("Mode Ind ", render(t->get_mode_ind()));
}

static void print_detail_rot(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::rot>(s);
	print("Rate of Turn", render(t->get_deg_per_minute()));
	print("Status", render(t->get_data_valid()));
}

static void print_detail_rpm(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::rpm>(s);
	print("Source", render(t->get_source()));
	print("Source Number", render(t->get_source_number()));
	print("RPM", render(t->get_revolutions()));
	print("Propeller Pitch", render(t->get_propeller_pitch()));
	print("Status", render(t->get_data_valid()));
}

static void print_detail_rsa(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::rsa>(s);
	print("Starbord Angle", render(t->get_rudder1()));
	print("Starbord Status", render(t->get_rudder1_valid()));
	print("Port Angle", render(t->get_rudder2()));
	print("Port Status", render(t->get_rudder2_valid()));
}

static void print_detail_rsd(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::rsd>(s);
	print("Cursor Range from own ship", render(t->get_cursor_range()));
	print("Cursor Bearing from own ship", render(t->get_cursor_bearing()));
	print("Range Scale", render(t->get_range_scale()));
	print("Range Units", render(t->get_range_unit()));
}

static void print_detail_vtg(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::vtg>(s);
	print("Track True", render(t->get_track_true()));
	print("Track Magn", render(t->get_track_magn()));
	print("Speed Knots", render(t->get_speed_kn()));
	print("Speed kmh", render(t->get_speed_kmh()));
	print("Mode Indicator", render(t->get_mode_ind()));
}

static void print_detail_gll(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::gll>(s);
	print("Latitude", render(t->get_lat()));
	print("Longitude", render(t->get_lon()));
	print("Time UTC", render(t->get_time_utc()));
	print("Status", render(t->get_data_valid()));
	print("Mode Indicator", render(t->get_mode_ind()));
}

static void print_detail_gns(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::gns>(s);
	print("Time UTC", render(t->get_time_utc()));
	print("Latitude", render(t->get_lat()));
	print("Longitude", render(t->get_lon()));
	print("Mode Indicator", render(t->get_mode_ind()));
	print("Number of Satellites", render(t->get_number_of_satellites()));
	print("HDROP", render(t->get_hdrop()));
	print("Antenna Altitude [m]", render(t->get_antenna_altitude()));
	print("Geoidal Separation [m]", render(t->get_geodial_separation()));
	print("Age of differential Data", render(t->get_age_of_differential_data()));
	print("Differential Ref Station ID", render(t->get_differential_ref_station_id()));
}

static void print_detail_grs(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::grs>(s);
	print("UTC time associated with GGA", render(t->get_time_utc()));
	print("Status", render(t->get_usage()));
	for (int i = 0; i < marnav::nmea::grs::num_satellite_residuals; ++i) {
		const auto residual = t->get_sat_residual(i);
		if (residual)
			print(fmt::sprintf("Sat %02d Residual [m]", i), render(*residual));
	}
}

static void print_detail_bec(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::bec>(s);
	print("Time UTC", render(t->get_time_utc()));
	print("Bearing True", render(t->get_bearing_true()));
	print("Bearing Magn", render(t->get_bearing_magn()));
	print("Distance [nm]", render(t->get_distance().get<marnav::units::nautical_miles>()));
	print("Waypoint", render(t->get_waypoint()));
}

static void print_detail_bod(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::bod>(s);
	print("Bearing True", render(t->get_bearing_true()));
	print("Bearing Magn", render(t->get_bearing_magn()));
	print("Waypoint To", render(t->get_waypoint_to()));
	print("Waypoint From", render(t->get_waypoint_from()));
}

static void print_detail_bwc(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::bwc>(s);
	print("Time UTC", render(t->get_time_utc()));
	print("Bearing True", render(t->get_bearing_true()));
	print("Bearing Magnetic", render(t->get_bearing_mag()));
	print("Distance",
		fmt::sprintf(
			"%s %s", render(t->get_distance()), render(marnav::nmea::unit::distance::nm)));
	print("Waypoint", render(t->get_waypoint_id()));
	print("Mode Indicator", render(t->get_mode_ind()));
}

static void print_detail_bwr(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::bwr>(s);
	print("Time UTC", render(t->get_time_utc()));
	print("Latitude", render(t->get_lat()));
	print("Longitude", render(t->get_lon()));
	print("Bearing True", render(t->get_bearing_true()));
	print("Bearing Magnetic", render(t->get_bearing_mag()));
	print("Distance NM", render(t->get_distance()));
	print("Waypoint", render(t->get_waypoint_id()));
	print("Mode Indicator", render(t->get_mode_ind()));
}

static void print_detail_bww(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::bww>(s);
	print("Bearing True", render(t->get_bearing_true()));
	print("Bearing Magnetic", render(t->get_bearing_magn()));
	print("Waypoint To", render(t->get_waypoint_to()));
	print("Waypoint From", render(t->get_waypoint_from()));
}

static void print_detail_gsa(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::gsa>(s);
	print("Selection Mode", render(t->get_sel_mode()));
	print("Mode", render(t->get_mode()));
	for (auto i = 0; i < marnav::nmea::gsa::max_satellite_ids; ++i) {
		print(fmt::sprintf("Satellite %02u", i), render(t->get_satellite_id(i)));
	}
	print("PDOP", render(t->get_pdop()));
	print("HDOP", render(t->get_hdop()));
	print("VDOP", render(t->get_vdop()));
}

static void print_detail_gst(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::gst>(s);
	print("Time UTC", render(t->get_time_utc()));
	print("Total RMS", render(t->get_total_rms()));
	print("Std Dev Semi-Major Axis", render(t->get_dev_semi_major()));
	print("Std Dev Semi-Minor Axis", render(t->get_dev_semi_minor()));
	print("Orientation Semi-Major Axis", render(t->get_orientation()));
	print("Std Dev. Latitude Error", render(t->get_dev_lat()));
	print("Std Dev. Longitude Error", render(t->get_dev_lon()));
	print("Std Dev. Altitude Error", render(t->get_dev_alt()));
}

static void print_detail_glc(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::glc>(s);
	print("GRI", render(t->get_gri()));
	print("Master TOA",
		fmt::sprintf(
			"DIFF:%s STATUS:%s", render(t->get_master().diff), render(t->get_master().status)));
	for (int i = 0; i < marnav::nmea::glc::max_differences; ++i) {
		const auto & td = t->get_time_diff(i);
		if (td) {
			print(fmt::sprintf("Time Diff %d", i),
				fmt::sprintf("DIFF:%s STATUS:%s", render(td->diff), render(td->status)));
		}
	}
}

static void print_detail_gga(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::gga>(s);
	print("Time", render(t->get_time()));
	print("Latitude", render(t->get_lat()));
	print("Longitude", render(t->get_lon()));
	print("Quality Ind", render(t->get_quality_indicator()));
	print("Num Satellites", render(t->get_n_satellites()));
	print("Horiz Dilution", render(t->get_hor_dilution()));
	print("Altitude", render(t->get_altitude()));
	print("Geodial Sep", render(t->get_geodial_separation()));
	print("DGPS Age", render(t->get_dgps_age()));
	print("DGPS Ref", render(t->get_dgps_ref()));
}

static void print_detail_osd(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::osd>(s);
	print("Heading", render(t->get_heading()));
	print("Status", render(t->get_data_valid()));
	print("Vessel Course True", render(t->get_course()));
	print("Vessel Speed",
		fmt::sprintf("%s %s", render(t->get_speed()), render(t->get_speed_unit())));
	print("Vessel Set", render(t->get_vessel_set()));
	print("Vessel Drift",
		fmt::sprintf("%s %s", render(t->get_vessel_drift()), render(t->get_speed_unit())));
}

static void print_detail_r00(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::r00>(s);
	for (int i = 0; i < marnav::nmea::r00::max_waypoint_ids; ++i) {
		const auto & wp = t->get_waypoint_id(i);
		if (wp) {
			print("Waypoint", render(*wp));
		}
	}
}

static void print_detail_rma(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::rma>(s);
	print("Blink Warning", render(t->get_blink_warning()));
	print("Latitude", render(t->get_lat()));
	print("Longitude", render(t->get_lon()));
	print("Time Diff A", render(t->get_time_diff_a()));
	print("Time Diff B", render(t->get_time_diff_b()));
	print("SOG [kn]", render(t->get_sog()));
	print("Track made good", render(t->get_track()));
	print("Magnetic Variation",
		fmt::sprintf(
			"%s %s", render(t->get_magnetic_var()), render(t->get_magnetic_var_hem())));
}

static void print_detail_mwv(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::mwv>(s);
	print("Angle", fmt::sprintf("%s %s", render(t->get_angle()), render(t->get_angle_ref())));
	print("Speed", fmt::sprintf("%s %s", render(t->get_speed()), render(t->get_speed_unit())));
	print("Data Valid", render(t->get_data_valid()));
}

static void print_detail_gsv(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::gsv>(s);
	print("Num Messages", render(t->get_n_messages()));
	print("Messages Number", render(t->get_message_number()));
	print("Num Sat in View", render(t->get_n_satellites_in_view()));
	for (int i = 0; i < 4; ++i) {
		const auto sat = t->get_sat(i);
		if (sat) {
			print("Sat",
				fmt::sprintf("PRN:%02u ELEV:%02u AZIMUTH:%03u SNR:%s", sat->prn, sat->elevation,
					sat->azimuth, render(sat->snr)));
		}
	}
}

static void print_detail_gtd(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::gtd>(s);
	for (int i = 0; i < marnav::nmea::gtd::max_time_diffs; ++i)
		print(fmt::sprintf("Time Diff %d", i), render(t->get_time_diff(i)));
}

static void print_detail_zda(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::zda>(s);
	print("Time UTC", render(t->get_time_utc()));
	print("Date", render(t->get_date()));
	print("Local Zone Hours", render(t->get_local_zone_hours()));
	print("Local Zone Min", render(t->get_local_zone_minutes()));
}

static void print_detail_zdl(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::zdl>(s);
	print("Time to Point", render(t->get_time_to_point()));
	print("Distance to Point NM", render(t->get_distance()));
	print("Type of Point", render(t->get_type_point()));
}

static void print_detail_zfi(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::zfi>(s);
	print("Time UTC", render(t->get_time_utc()));
	print("Elapsed Time", render(t->get_time_elapsed()));
	print("Origin Waypoint", render(t->get_waypoint_id()));
}

static void print_detail_zfo(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::zfo>(s);
	print("Time UTC", render(t->get_time_utc()));
	print("Elapsed Time", render(t->get_time_elapsed()));
	print("Origin Waypoint", render(t->get_waypoint_id()));
}

static void print_detail_zta(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::zta>(s);
	print("Time UTC", render(t->get_time_utc()));
	print("Time Arrival", render(t->get_time_arrival()));
	print("Destination Waypoint", render(t->get_waypoint_id()));
}

static void print_detail_zte(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::zte>(s);
	print("Time UTC", render(t->get_time_utc()));
	print("Time Remaining", render(t->get_time_remaining()));
	print("Destination Waypoint", render(t->get_waypoint_id()));
}

static void print_detail_zlz(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::zlz>(s);
	print("Time UTC", render(t->get_time_utc()));
	print("Time Local", render(t->get_time_local()));
	print("Local Zone Description", render(t->get_local_zone_description()));
}

static void print_detail_zpi(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::zpi>(s);
	print("Time UTC", render(t->get_time_utc()));
	print("Time at Arrival", render(t->get_time_arrival()));
	print("Destination Waypoint", render(t->get_waypoint_id()));
}

static void print_detail_ztg(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::ztg>(s);
	print("Time UTC", render(t->get_time_utc()));
	print("Time Remaining", render(t->get_time_remaining()));
	print("Destination Waypoint", render(t->get_waypoint_id()));
}

static void print_detail_dtm(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::dtm>(s);
	print("Ref", render(t->get_ref()));
	print("Subcode", render(t->get_subcode()));
	print("Latitude Offset", render(t->get_lat_offset()));
	print("Latitude Hem", render(t->get_lat_hem()));
	print("Longitude Offset", render(t->get_lon_offset()));
	print("Longitude Hem", render(t->get_lon_hem()));
	print("Altitude", render(t->get_altitude().get<marnav::units::meters>()));
	print("Name", render(t->get_name()));
}

static void print_detail_fsi(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::fsi>(s);
	print("Tx Freuency 100 Hz", render(t->get_tx_frequency()));
	print("Rx Freuency 100 Hz", render(t->get_rx_frequency()));
	print("Mode of Operation", render(t->get_communications_mode()));
	print("Power Level", render(t->get_power_level()));
	print("Sentence Status Flag", render(t->get_sentence_status()));
}

static void print_detail_gbs(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::gbs>(s);
	print("Time UTC", render(t->get_time_utc()));
	print("Error Latitude", render(t->get_err_lat().get<marnav::units::meters>()));
	print("Error Longitude", render(t->get_err_lon().get<marnav::units::meters>()));
	print("Error Altitude", render(t->get_err_alt().get<marnav::units::meters>()));
	print("Satellite PRN", render(t->get_satellite()));
	print("Probability", render(t->get_probability()));
	print("Bias", render(t->get_bias().get<marnav::units::meters>()));
	print("Standard Deviation of bias", render(t->get_bias_dev()));
}

static void print_detail_aam(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::aam>(s);
	print("Arrival Circle Entred", render(t->get_arrival_circle_entered()));
	print("Perpendicular Passed", render(t->get_perpendicualar_passed()));
	print("Arrival Circle Radius",
		render(t->get_arrival_circle_radius().get<marnav::units::nautical_miles>()));
	print("Waypoint", render(t->get_waypoint_id()));
}

static void print_detail_alm(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::alm>(s);
	print("Number of Messages", render(t->get_number_of_messages()));
	print("Message Number", render(t->get_message_number()));
	print("Satellite PRN", render(t->get_satellite_prn()));
	print("GPS Week Number", render(t->get_gps_week_number()));
	print("SV Health", render(t->get_sv_health()));
	print("Eccentricity", render(t->get_eccentricity()));
	print("Almanac Reference Time", render(t->get_almanac_reference_time()));
	print("Inclination Angle", render(t->get_inclination_angle()));
	print("Rate of right ascension", render(t->get_rate_of_right_ascension()));
	print("Root of Semimajor Axis", render(t->get_root_of_semimajor_axis()));
	print("Argument of perigee", render(t->get_argument_of_perigee()));
	print("Longitude of ascension node", render(t->get_longitude_of_ascension_node()));
	print("Mean Anomaly", render(t->get_mean_anomaly()));
	print("F0 clock parameter", render(t->get_f0_clock_parameter()));
	print("F1 clock parameter", render(t->get_f1_clock_parameter()));
}

static void print_detail_apa(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::apa>(s);
	print("Lorac C Blink Warning", render(t->get_loran_c_blink_warning()));
	print("Lorac C Cycle Lock Warning", render(t->get_loran_c_cycle_lock_warning()));
	print("Magnitude of Cross Track Error", render(t->get_cross_track_error_magnitude()));
	print("Direction to Steer", render(t->get_direction_to_steer()));
	print("Cross Track Units", render(t->get_cross_track_unit()));
	print("Status Arrival", render(t->get_status_arrival()));
	print("Status Perpendicular Passed", render(t->get_status_perpendicular_passing()));
	print("Bearing Origin to Dest", render(t->get_bearing_origin_to_destination()));
	print("Bearing Origin to Dest Ref", render(t->get_bearing_origin_to_destination_ref()));
	print("Destination Waypoint", render(t->get_waypoint_id()));
}

static void print_detail_rte(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::rte>(s);
	print("Number of Messages", render(t->get_n_messages()));
	print("Message Number", render(t->get_message_number()));
	print("Message Mode", render(t->get_message_mode()));
	for (int i = 0; i < marnav::nmea::rte::max_waypoints; ++i) {
		const auto wp = t->get_waypoint_id(i);
		if (wp)
			print(fmt::sprintf("Waypoint %i", i), render(wp));
	}
}

static void print_detail_sfi(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::sfi>(s);
	print("Number of Messages", render(t->get_n_messages()));
	print("Message Number", render(t->get_message_number()));
	for (const auto & f : t->get_frequencies())
		print("Frequency [kHz]", fmt::sprintf("%s %s", render(f.frequency), render(f.mode)));
}

static void print_detail_stn(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::stn>(s);
	print("Number ID", render(t->get_number()));
}

static void print_detail_tds(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::tds>(s);
	print("Distance [m]", render(t->get_distance()));
}

static void print_detail_tfi(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::tfi>(s);
	print("Sensor #1", render(t->get_sensor(0)));
	print("Sensor #2", render(t->get_sensor(1)));
	print("Sensor #3", render(t->get_sensor(2)));
}

static void print_detail_tll(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::tll>(s);
	print("Target Number", render(t->get_number()));
	print("Latitude", render(t->get_lat()));
	print("Longitude", render(t->get_lon()));
	print("Target Name", render(t->get_name()));
	print("Time UTC", render(t->get_time_utc()));
	print("Target Status", render(t->get_status()));
	print("Reference Target", render(t->get_reference_target()));
}

static void print_detail_tpc(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::tpc>(s);
	print("Horiz. Range from Center Line [m]", render(t->get_distance_centerline()));
	print("Horiz. dist from Transd. along [m]", render(t->get_distance_transducer()));
	print("Depth [m]", render(t->get_depth()));
}

static void print_detail_tpr(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::tpr>(s);
	print("Horizontal Range [m]", render(t->get_range()));
	print("Bearing to Target to Vessel", render(t->get_bearing()));
	print("Depth [m]", render(t->get_depth()));
}

static void print_detail_tpt(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::tpt>(s);
	print("Horizontal Range [m]", render(t->get_range()));
	print("Bearing to Target True", render(t->get_bearing()));
	print("Depth [m]", render(t->get_depth()));
}

static void print_detail_ttm(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::ttm>(s);
	print("Target Number", render(t->get_target_number()));
	print("Target Distance", render(t->get_target_distance()));
	print("Bearing from own ship", render(t->get_bearing_from_ownship()));
	print("Bearing from own ship Ref", render(t->get_bearing_from_ownship_ref()));
	print("Target Speed", render(t->get_target_speed()));
	print("Target Course", render(t->get_target_course()));
	print("Target Course Ref", render(t->get_target_course_ref()));
	print("CPA", render(t->get_distance_cpa()));
	print("TCPA", render(t->get_tcpa()));
	print("Unknown", render(t->get_unknown()));
	print("Target Name", render(t->get_target_name()));
	print("Target Status", render(t->get_target_status()));
	print("Reference Target", render(t->get_reference_target()));
}

static void print_detail_vbw(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::vbw>(s);
	print("Longitudinal Water Speed", render(t->get_water_speed_longitudinal()));
	print("Transverse Water Speed", render(t->get_water_speed_transveral()));
	print("Status", render(t->get_water_speed_status()));
	print("Longitudinal Ground Speed", render(t->get_ground_speed_longitudinal()));
	print("Transverse Ground Speed", render(t->get_ground_speed_transveral()));
	print("Status", render(t->get_ground_speed_status()));
}

static void print_detail_vdr(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::vdr>(s);
	print("Degrees True", render(t->get_degrees_true()));
	print("Degrees Magnetic", render(t->get_degrees_magn()));
	print("Speed of Current", render(t->get_speed()));
}

static void print_detail_mss(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::mss>(s);
	print("Signal Strength [dB 1uV]", render(t->get_signal_strength()));
	print("Signal to Noise Ratio (dB)", render(t->get_signal_to_noise_ratio()));
	print("Beacon Frequency [kHz]", render(t->get_beacon_frequency()));
	print("Beacon Data Rate BPS", render(t->get_beacon_datarate()));
	print("unknown", render(t->get_unknown()));
}

static void print_detail_mta(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::mta>(s);
	print("Air Temperature", render(t->get_temperature()));
}

static void print_detail_mtw(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::mtw>(s);
	print("Water Temperature", render(t->get_temperature()));
}

static void print_detail_mwd(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::mwd>(s);
	print("Direction True", render(t->get_direction_true()));
	print("Direction Magnetic", render(t->get_direction_mag()));
	print("Speed kn", render(t->get_speed_kn()));
	print("Speed m/s", render(t->get_speed_ms()));
}

static void print_detail_dbt(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::dbt>(s);
	print("Depth Feet", render(t->get_depth_feet()));
	print("Depth Meter", render(t->get_depth_meter()));
	print("Depth Fathom", render(t->get_depth_fathom()));
}

static void print_detail_dpt(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::dpt>(s);
	print("Depth", render(t->get_depth_meter().get<marnav::units::meters>()));
	print("Offset from Transducer",
		render(t->get_transducer_offset().get<marnav::units::meters>()));
	print("Max Depth", render(t->get_max_depth()));
}

static void print_detail_apb(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::apb>(s);
	print("Loran C blink warn", render(t->get_loran_c_blink_warning()));
	print("Loran C cycle lock warn", render(t->get_loran_c_cycle_lock_warning()));
	print("Cross Track Error Magnitude", render(t->get_cross_track_error_magnitude()));
	print("Direction to Steer", render(t->get_direction_to_steer()));
	print("Cross Track Unit", render(t->get_cross_track_unit()));
	print("Status Arrival", render(t->get_status_arrival()));
	print("Status Perpendicular Pass", render(t->get_status_perpendicular_passing()));
	print("Bearing Org to Dest", render(t->get_bearing_origin_to_destination()));
	print("Bearing Org to Dest Ref", render(t->get_bearing_origin_to_destination_ref()));
	print("Waypoint", render(t->get_waypoint_id()));
	print("Bearing Pos to Dest", render(t->get_bearing_pos_to_destination()));
	print("Bearing Pos to Dest Ref", render(t->get_bearing_pos_to_destination_ref()));
	print("Heading to Steer to Dest", render(t->get_heading_to_steer_to_destination()));
	print("Heading to Steer to Dest Ref", render(t->get_heading_to_steer_to_destination_ref()));
	print("Mode Indicator", render(t->get_mode_ind()));
}

static void print_detail_pgrme(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::pgrme>(s);
	print("HPE", render(t->get_horizontal_position_error()));
	print("VPE", render(t->get_vertical_position_error()));
	print("O.sph.eq.pos err", render(t->get_overall_spherical_equiv_position_error()));
}

static void print_detail_pgrmm(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::pgrmm>(s);
	print("Map Datum", render(t->get_map_datum()));
}

static void print_detail_pgrmz(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::pgrmz>(s);
	print("Altitude", render(t->get_altitude()));
	print("Fix Type", render(t->get_fix()));
}

static void print_detail_stalk(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::stalk>(s);
	print("Data", render(t->get_data()));
}

static void print_detail_vwe(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::vwe>(s);
	print("Efficiency", render(t->get_efficiency()));
}

static void print_detail_vwr(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::vwr>(s);
	print("Angle", fmt::sprintf("%s %s", render(t->get_angle()), render(t->get_angle_side())));
	print("Speed kn", render(t->get_speed_knots()));
	print("Speed m/s", render(t->get_speed_mps()));
	print("Speed km/h", render(t->get_speed_kmh()));
}

static void print_detail_wcv(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::wcv>(s);
	print("Speed kn", render(t->get_speed()));
	print("Waypoint", render(t->get_waypoint_id()));
}

static void print_detail_wdc(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::wdc>(s);
	print("Distance NM", render(t->get_distance()));
	print("Waypoint", render(t->get_waypoint_id()));
}

static void print_detail_wdr(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::wdr>(s);
	print("Distance NM", render(t->get_distance()));
	print("Waypoint", render(t->get_waypoint_id()));
}

static void print_detail_wnc(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::wnc>(s);
	print("Distnace NM", render(t->get_distance_nm()));
	print("Distnace km", render(t->get_distance_km()));
	print("Waypoint To", render(t->get_waypoint_to()));
	print("Waypoint From", render(t->get_waypoint_from()));
}

static void print_detail_wpl(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::wpl>(s);
	print("Latitude", render(t->get_lat()));
	print("Longitude", render(t->get_lon()));
	print("Waypoint", render(t->get_waypoint_id()));
}

static void print_detail_xdr(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::xdr>(s);
	for (auto i = 0; i < marnav::nmea::xdr::max_transducer_info; ++i) {
		const auto info = t->get_info(i);
		if (info) {
			print("Transducer Info",
				fmt::sprintf("Type:%c  Data:%f  Unit:%c  Name:%s", info->transducer_type,
					info->measurement_data, info->units_of_measurement, info->name));
		}
	}
}

static void print_detail_xte(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::xte>(s);
	print("Status 1", render(t->get_status1()));
	print("Status 2", render(t->get_status2()));
	print("Cross Track Error Magnitude", render(t->get_cross_track_error_magnitude()));
	print("Direction to Steer", render(t->get_direction_to_steer()));
	print("Mode Indicator", render(t->get_mode_ind()));
}

static void print_detail_xtr(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::xtr>(s);
	print("Cross Track Error Magnitude", render(t->get_cross_track_error_magnitude()));
	print("Direction to Steer", render(t->get_direction_to_steer()));
}

static void print_detail_vlw(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::vlw>(s);
	print("Distance Cumulative NM", render(t->get_distance_cum()));
	print("Distance since Rest NM", render(t->get_distance_reset()));
}

static void print_detail_vpw(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::vpw>(s);
	print("Speed kn", render(t->get_speed_knots()));
	print("Speed m/s", render(t->get_speed_meters_per_second()));
}

static void print_detail_vhw(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::vhw>(s);
	print("Heading True", render(t->get_heading_true()));
	print("Heading Magn", render(t->get_heading_magn()));
	print("Speed kn", render(t->get_speed_knots()));
	print("Speed km/h", render(t->get_speed_kmh()));
}

static void print_detail_message_01_common(const marnav::ais::message_01 * t)
{
	print("Repeat Indicator", render(t->get_repeat_indicator()));
	print("MMSI", render(t->get_mmsi()));
	print("Nav Status", render(t->get_nav_status()));
	print("ROT", render(t->get_rot()));
	print("SOG", render(t->get_sog()));
	print("Pos Accuracy", render(t->get_position_accuracy()));
	print("Latitude", render(t->get_lat()));
	print("Longitude", render(t->get_lon()));
	print("COG", render(t->get_cog()));
	print("HDG", render(t->get_hdg()));
	print("Time Stamp", render(t->get_timestamp()));
	print("Maneuver Indicator", render(t->get_maneuver_indicator()));
	print("RAIM", render(t->get_raim()));
	print("Radio Status", render(t->get_radio_status()));
}

static void print_detail_message_01(const marnav::ais::message * m)
{
	print_detail_message_01_common(marnav::ais::message_cast<marnav::ais::message_01>(m));
}

static void print_detail_message_02(const marnav::ais::message * m)
{
	print_detail_message_01_common(marnav::ais::message_cast<marnav::ais::message_02>(m));
}

static void print_detail_message_03(const marnav::ais::message * m)
{
	print_detail_message_01_common(marnav::ais::message_cast<marnav::ais::message_03>(m));
}

static void print_detail_message_04_common(const marnav::ais::message_04 * t)
{
	print("Repeat Indicator", render(t->get_repeat_indicator()));
	print("MMSI", render(t->get_mmsi()));
	print("Year", render(t->get_year()));
	print("Month", render(t->get_month()));
	print("Day", render(t->get_day()));
	print("Hour", render(t->get_hour()));
	print("Minute", render(t->get_minute()));
	print("Second", render(t->get_second()));
	print("Pos Accuracy", render(t->get_position_accuracy()));
	print("Latitude", render(t->get_lat()));
	print("Longitude", render(t->get_lon()));
	print("EPFD Fix", render(t->get_epfd_fix()));
	print("RAIM", render(t->get_raim()));
	print("Radio Status", render(t->get_radio_status()));
}

static void print_detail_message_04(const marnav::ais::message * m)
{
	print_detail_message_04_common(marnav::ais::message_cast<marnav::ais::message_04>(m));
}

static void print_detail_message_11(const marnav::ais::message * m)
{
	print_detail_message_04_common(marnav::ais::message_cast<marnav::ais::message_11>(m));
}

static void print_detail_message_12(const marnav::ais::message * m)
{
	const auto t = marnav::ais::message_cast<marnav::ais::message_12>(m);
	print("Repeat Indicator", render(t->get_repeat_indicator()));
	print("MMSI", render(t->get_mmsi()));
	print("Seqence Number", render(t->get_seqno()));
	print("Destination MMSI", render(t->get_dest_mmsi()));
	print("Retransmit", render(t->get_retransmit()));
	print("Text", render(t->get_text()));
}

static void print_detail_message_13(const marnav::ais::message * m)
{
	const auto t = marnav::ais::message_cast<marnav::ais::message_13>(m);
	print("Repeat Indicator", render(t->get_repeat_indicator()));
	print("MMSI", render(t->get_mmsi()));
	print("MMSI_1", render(t->get_mmsi_1()));
	print("MMSI_2", render(t->get_mmsi_2()));
	print("MMSI_3", render(t->get_mmsi_3()));
	print("MMSI_4", render(t->get_mmsi_4()));
}

static void print_detail_message_14(const marnav::ais::message * m)
{
	const auto t = marnav::ais::message_cast<marnav::ais::message_14>(m);
	print("Repeat Indicator", render(t->get_repeat_indicator()));
	print("MMSI", render(t->get_mmsi()));
	print("Text", render(t->get_text()));
}

static void print_detail_message_05(const marnav::ais::message * m)
{
	const auto t = marnav::ais::message_cast<marnav::ais::message_05>(m);
	print("Repeat Indicator", render(t->get_repeat_indicator()));
	print("MMSI", render(t->get_mmsi()));
	print("AIS Version", render(t->get_ais_version()));
	print("IMO", render(t->get_imo_number()));
	print("Callsign", render(t->get_callsign()));
	print("Shipname", render(t->get_shipname()));
	print("Shiptype", render(t->get_shiptype()));
	print("Length", render(t->get_vessel_dimension().length()));
	print("Width", render(t->get_vessel_dimension().width()));
	print("Draught", render(t->get_draught()));
	print("EPFD Fix", render(t->get_epfd_fix()));
	print("ETA Month", render(t->get_eta_month()));
	print("ETA Day", render(t->get_eta_day()));
	print("ETA Hour", render(t->get_eta_hour()));
	print("ETA Minute", render(t->get_eta_minute()));
	print("Destination", render(t->get_destination()));
	print("DTE", render(t->get_dte()));
}

static void print_detail_message_06(const marnav::ais::message * m)
{
	const auto t = marnav::ais::message_cast<marnav::ais::message_06>(m);
	print("Repeat Indicator", render(t->get_repeat_indicator()));
	print("MMSI", render(t->get_mmsi()));
	print("Sequence No", render(t->get_sequnce_no()));
	print("Destination MMSI", render(t->get_dest_mmsi()));
	print("Retransmit Flag", render(t->get_retransmit_flag()));
	print("DAC", render(t->get_dac()));
	print("FID", render(t->get_fid()));
	// TODO
	fmt::printf("\n\twarning: message 06: decoding of payload not implemented: %03d/%02d\n",
		t->get_dac(), t->get_fid());
}

static void print_detail_message_07(const marnav::ais::message * m)
{
	const auto t = marnav::ais::message_cast<marnav::ais::message_07>(m);
	print("Repeat Indicator", render(t->get_repeat_indicator()));
	print("MMSI", render(t->get_mmsi()));
	print("MMSI_1", render(t->get_mmsi_1()));
	print("MMSI_2", render(t->get_mmsi_2()));
	print("MMSI_3", render(t->get_mmsi_3()));
	print("MMSI_4", render(t->get_mmsi_4()));
}

static void print_detail_message_08(const marnav::ais::message * m)
{
	const auto t = marnav::ais::message_cast<marnav::ais::message_08>(m);
	print("Repeat Indicator", render(t->get_repeat_indicator()));
	print("MMSI", render(t->get_mmsi()));
	print("DAC", render(t->get_dac()));
	print("FID", render(t->get_fid()));

	if (t->get_dac() == 1 && t->get_fid() == 11) {
		marnav::ais::binary_001_11 b;
		t->read_binary(b);
		fmt::printf("\n");
		print("Meteological and Hydrological Data (001/11) IMO236");
		print("Position", render(b.get_position()));
		print("Day", render(b.get_day()));
		print("Hour", render(b.get_hour()));
		print("Minute", render(b.get_minute()));
		print("Wind Speed 10min avg [kn]", render(b.get_wind_speed_avg()));
		print("Wind Gust [kn]", render(b.get_wind_gust()));
		print("Wind Direction", render(b.get_wind_direction()));
		print("Wind Gust Direction", render(b.get_wind_gust_direction()));
		print("Temperature [C]", render(b.get_temperature()));
		print("Humidity [%]", render(b.get_humidity()));
		print("Dew Point [%]", render(b.get_dew_point()));
		print("Air Pressure [hPa]", render(b.get_pressure()));
		print("Air Pressure Trend", render(b.get_pressure_trend()));
		print("Visibility [NM]", render(b.get_visibility()));
		print("Water Level [m]", render(b.get_water_level()));
		print("Water Level Trend", render(b.get_water_level_trend()));
		print("Sufrace Current Speed [kn]", render(b.get_surface_current_speed()));
		print("Sufrace Current Direction", render(b.get_surface_current_direction()));
		print("Current 2 Speed [kn]", render(b.get_current_2_speed()));
		print("Current 2 Direction", render(b.get_current_2_direction()));
		print("Current 2 Depth [m]", render(b.get_current_2_depth()));
		print("Current 3 Speed [kn]", render(b.get_current_3_speed()));
		print("Current 3 Direction", render(b.get_current_3_direction()));
		print("Current 3 Depth [m]", render(b.get_current_3_depth()));
		print("Wave Height [m]", render(b.get_wave_height()));
		print("Wave Period [s]", render(b.get_wave_period()));
		print("Wave Direction", render(b.get_wave_direction()));
		print("Swell Height [m]", render(b.get_swell_height()));
		print("Swell Period [s]", render(b.get_swell_period()));
		print("Swell Direction", render(b.get_swell_direction()));
		print("Sea State", render(b.get_sea_state()));
		print("Water Temperature [C]", render(b.get_water_temperature()));
		print("Precipitation", render(b.get_precipitation()));
		print("Salinity [%]", render(b.get_salinity()));
		print("Ice", render(b.get_ice()));
	} else if (t->get_dac() == 200 && t->get_fid() == 10) {
		marnav::ais::binary_200_10 b;
		t->read_binary(b);
		fmt::printf("\n");
		print("Inland ship static and voyage related data (200/10)");
		print("Vessel ID", render(b.get_vessel_id()));
		print("Length [m]", render(b.get_length()));
		print("Beam [m]", render(b.get_beam()));
		print("Shiptype", render(b.get_shiptype()));
		print("Hazard", render(b.get_hazard()));
		print("Draught [m]", render(b.get_draught()));
		print("Loaded", render(b.get_loaded()));
		print("Speed quality", render(b.get_speed_q()));
		print("Course quality", render(b.get_course_q()));
		print("Heading quality", render(b.get_heading_q()));
	} else {
		fmt::printf("\n\twarning: message 08: decoding of payload not implemented: %03d/%02d\n",
			t->get_dac(), t->get_fid());
	}
}

static void print_detail_message_09(const marnav::ais::message * m)
{
	const auto t = marnav::ais::message_cast<marnav::ais::message_09>(m);
	print("Repeat Indicator", render(t->get_repeat_indicator()));
	print("MMSI", render(t->get_mmsi()));
	print("Altitude", render(t->get_altitude()));
	print("Speed", render(t->get_speed()));
	print("Pos Accuracy", render(t->get_position_accuracy()));
	print("COG", render(t->get_course()));
	print("UTC Second", render(t->get_utc_second()));
	print("DTE", render(t->get_dte()));
	print("RAIM", render(t->get_raim()));
	print("Radio Status", render(t->get_radio_status()));
}

static void print_detail_message_10(const marnav::ais::message * m)
{
	const auto t = marnav::ais::message_cast<marnav::ais::message_10>(m);
	print("Repeat Indicator", render(t->get_repeat_indicator()));
	print("MMSI", render(t->get_mmsi()));
	print("Destination MMSI", render(t->get_dest_mmsi()));
}

static void print_detail_message_17(const marnav::ais::message * m)
{
	const auto t = marnav::ais::message_cast<marnav::ais::message_17>(m);
	print("Repeat Indicator", render(t->get_repeat_indicator()));
	print("MMSI", render(t->get_mmsi()));
	print("Latitude", render(t->get_lat()));
	print("Longitude", render(t->get_lon()));

	// TODO: print payload as hex string
}

static void print_detail_message_18(const marnav::ais::message * m)
{
	const auto t = marnav::ais::message_cast<marnav::ais::message_18>(m);
	print("Repeat Indicator", render(t->get_repeat_indicator()));
	print("MMSI", render(t->get_mmsi()));
	print("SOG", render(t->get_sog()));
	print("Pos Accuracy", render(t->get_position_accuracy()));
	print("Latitude", render(t->get_lat()));
	print("Longitude", render(t->get_lon()));
	print("COG", render(t->get_cog()));
	print("HDG", render(t->get_hdg()));
	print("Time Stamp", render(t->get_timestamp()));
	print("CS Unit", render(t->get_cs_unit()));
	print("Display Flag", render(t->get_display_flag()));
	print("DSC Flag", render(t->get_dsc_flag()));
	print("Band Flag", render(t->get_band_flag()));
	print("Message 22 Flag", render(t->get_message_22_flag()));
	print("Assigned", render(t->get_assigned()));
	print("RAIM", render(t->get_raim()));
	print("Radio Status", render(t->get_radio_status()));
}

static void print_detail_message_19(const marnav::ais::message * m)
{
	const auto t = marnav::ais::message_cast<marnav::ais::message_19>(m);
	print("Repeat Indicator", render(t->get_repeat_indicator()));
	print("MMSI", render(t->get_mmsi()));
	print("SOG", render(t->get_sog()));
	print("Pos Accuracy", render(t->get_position_accuracy()));
	print("Latitude", render(t->get_lat()));
	print("Longitude", render(t->get_lon()));
	print("COG", render(t->get_cog()));
	print("HDG", render(t->get_hdg()));
	print("Time Stamp", render(t->get_timestamp()));
	print("Ship Name", render(t->get_shipname()));
	print("Ship Type", render(t->get_shiptype()));
	print("Length", render(t->get_vessel_dimension().length()));
	print("Width", render(t->get_vessel_dimension().width()));
	print("EPFD Fix", render(t->get_epfd_fix()));
	print("RAIM", render(t->get_raim()));
	print("DTE", render(t->get_dte()));
	print("Assigned", render(t->get_assigned()));
}

static void print_detail_message_20(const marnav::ais::message * m)
{
	const auto t = marnav::ais::message_cast<marnav::ais::message_20>(m);
	print("Repeat Indicator", render(t->get_repeat_indicator()));
	print("MMSI", render(t->get_mmsi()));
	for (int i = 0; i < 3; ++i) {
		const auto entry = t->get_entry(i);
		print(fmt::sprintf("Entry %d", i + 1),
			fmt::sprintf("Offset:%4u  Slots:%1u  Timeout:%1u  Increment:%4u", entry.offset,
				entry.slots, entry.timeout, entry.increment));
	}
}

static void print_detail_message_21(const marnav::ais::message * m)
{
	const auto t = marnav::ais::message_cast<marnav::ais::message_21>(m);
	print("Repeat Indicator", render(t->get_repeat_indicator()));
	print("MMSI", render(t->get_mmsi()));
	print("Aid Type", render(t->get_aid_type()));
	print("Name", render(t->get_name()));
	print("Pos Accuracy", render(t->get_position_accuracy()));
	print("Latitude", render(t->get_lat()));
	print("Longitude", render(t->get_lon()));
	print("Length", render(t->get_vessel_dimension().length()));
	print("Width", render(t->get_vessel_dimension().width()));
	print("EPFD Fix", render(t->get_epfd_fix()));
	print("UTC Second", render(t->get_utc_second()));
	print("Off Pos Indicator", render(t->get_off_position()));
	print("Regional", render(t->get_regional()));
	print("RAIM", render(t->get_raim()));
	print("Virtual Aid Flag", render(t->get_virtual_aid_flag()));
	print("Assigned", render(t->get_assigned()));
	print("Name Extension", render(t->get_name_extension()));
}

static void print_detail_message_22(const marnav::ais::message * m)
{
	const auto t = marnav::ais::message_cast<marnav::ais::message_22>(m);
	print("Repeat Indicator", render(t->get_repeat_indicator()));
	print("MMSI", render(t->get_mmsi()));
	print("Channel A", render(t->get_channel_a()));
	print("Channel B", render(t->get_channel_b()));
	print("TxRx Mode", render(t->get_txrx_mode()));
	print("Power", render(t->get_power()));
	print("Adressed", render(t->get_addressed()));
	if (t->get_addressed()) {
		print("MMSI 1", render(t->get_mmsi_1()));
		print("MMSI 2", render(t->get_mmsi_2()));
	} else {
		print("Position NE", render(t->get_position_ne()));
		print("Position SW", render(t->get_position_sw()));
	}
}

static void print_detail_message_23(const marnav::ais::message * m)
{
	const auto t = marnav::ais::message_cast<marnav::ais::message_23>(m);
	print("Repeat Indicator", render(t->get_repeat_indicator()));
	print("MMSI", render(t->get_mmsi()));
	print("Position NE", render(t->get_position_ne()));
	print("Position SW", render(t->get_position_sw()));
	print("Station Type", render(t->get_station_type()));
	print("Ship Type", render(t->get_shiptype()));
	print("TxRx Mode", render(t->get_txrx_mode()));
	print("Report Interval", render(t->get_interval()));
	print("Quiet Time", render(t->get_quiet_time()));
}

static void print_detail_message_24(const marnav::ais::message * m)
{
	const auto t = marnav::ais::message_cast<marnav::ais::message_24>(m);
	print("Repeat Indicator", render(t->get_repeat_indicator()));
	print("MMSI", render(t->get_mmsi()));
	print("Part", render(t->get_part_number()));
	if (t->get_part_number() == marnav::ais::message_24::part::A) {
		print("Ship Name", render(t->get_shipname()));
	} else {
		print("Ship Type", render(t->get_shiptype()));
		print("Vendor ID", render(t->get_vendor_id()));
		print("Model", render(t->get_model()));
		print("Serial", render(t->get_serial()));
		print("Callsign", render(t->get_callsign()));
		if (t->is_auxiliary_vessel()) {
			print("Mothership MMSI", render(t->get_mothership_mmsi()));
		} else {
			print("Length", render(t->get_vessel_dimension().length()));
			print("Width", render(t->get_vessel_dimension().width()));
		}
	}
}
}
/// @endcond

static void dump_nmea(const std::string & line)
{
#define ADD_SENTENCE(s)                               \
	{                                                 \
		marnav::nmea::s::ID, detail::print_detail_##s \
	}
	struct entry {
		marnav::nmea::sentence_id id;
		std::function<void(const marnav::nmea::sentence *)> func;
	};
	using container = std::vector<entry>;
	// clang-format off
	static const container sentences = {
		// standard
		ADD_SENTENCE(aam),
		ADD_SENTENCE(alm),
		ADD_SENTENCE(apa),
		ADD_SENTENCE(apb),
		ADD_SENTENCE(bec),
		ADD_SENTENCE(bod),
		ADD_SENTENCE(bwc),
		ADD_SENTENCE(bwr),
		ADD_SENTENCE(bww),
		ADD_SENTENCE(dbt),
		ADD_SENTENCE(dpt),
		ADD_SENTENCE(dtm),
		ADD_SENTENCE(fsi),
		ADD_SENTENCE(gbs),
		ADD_SENTENCE(glc),
		ADD_SENTENCE(gga),
		ADD_SENTENCE(gll),
		ADD_SENTENCE(gns),
		ADD_SENTENCE(grs),
		ADD_SENTENCE(gsa),
		ADD_SENTENCE(gst),
		ADD_SENTENCE(gsv),
		ADD_SENTENCE(gtd),
		ADD_SENTENCE(hdg),
		ADD_SENTENCE(hfb),
		ADD_SENTENCE(hdm),
		ADD_SENTENCE(hdt),
		ADD_SENTENCE(hsc),
		ADD_SENTENCE(its),
		ADD_SENTENCE(lcd),
		ADD_SENTENCE(mob),
		ADD_SENTENCE(msk),
		ADD_SENTENCE(mss),
		ADD_SENTENCE(mta),
		ADD_SENTENCE(mtw),
		ADD_SENTENCE(mwd),
		ADD_SENTENCE(mwv),
		ADD_SENTENCE(osd),
		ADD_SENTENCE(r00),
		ADD_SENTENCE(rma),
		ADD_SENTENCE(rmb),
		ADD_SENTENCE(rmc),
		ADD_SENTENCE(rot),
		ADD_SENTENCE(rpm),
		ADD_SENTENCE(rsa),
		ADD_SENTENCE(rsd),
		ADD_SENTENCE(rte),
		ADD_SENTENCE(sfi),
		ADD_SENTENCE(stn),
		ADD_SENTENCE(tds),
		ADD_SENTENCE(tfi),
		ADD_SENTENCE(tll),
		ADD_SENTENCE(tpc),
		ADD_SENTENCE(tpr),
		ADD_SENTENCE(tpt),
		ADD_SENTENCE(ttm),
		ADD_SENTENCE(vbw),
		ADD_SENTENCE(vdr),
		ADD_SENTENCE(vhw),
		ADD_SENTENCE(vlw),
		ADD_SENTENCE(vpw),
		ADD_SENTENCE(vtg),
		ADD_SENTENCE(vwe),
		ADD_SENTENCE(vwr),
		ADD_SENTENCE(wcv),
		ADD_SENTENCE(wdc),
		ADD_SENTENCE(wdr),
		ADD_SENTENCE(wnc),
		ADD_SENTENCE(wpl),
		ADD_SENTENCE(xdr),
		ADD_SENTENCE(xte),
		ADD_SENTENCE(xtr),
		ADD_SENTENCE(zda),
		ADD_SENTENCE(zdl),
		ADD_SENTENCE(zfi),
		ADD_SENTENCE(zfo),
		ADD_SENTENCE(zlz),
		ADD_SENTENCE(zpi),
		ADD_SENTENCE(zta),
		ADD_SENTENCE(zte),
		ADD_SENTENCE(ztg),

		// proprietary
		ADD_SENTENCE(pgrme),
		ADD_SENTENCE(pgrmm),
		ADD_SENTENCE(pgrmz),
		ADD_SENTENCE(stalk)
	};
// clang-format on
#undef ADD_SENTENCE

	using namespace marnav;

	try {
		auto s = nmea::make_sentence(line);
		auto i = std::find_if(std::begin(sentences), std::end(sentences),
			[&s](const container::value_type & item) { return item.id == s->id(); });
		if (i == std::end(sentences)) {
			fmt::printf("\t%s\n", detail::render(s->id()));
			fmt::printf(
				"%s%s%s\n\tnot implemented\n\n", terminal::magenta, line, terminal::normal);
		} else {
			fmt::printf("%s%s%s\n", terminal::green, line, terminal::normal);
			fmt::printf("\tName  : %s\n", detail::render(s->id()));
			fmt::printf("\tTalker: %s\n", detail::render(s->get_talker()));
			i->func(s.get());
			fmt::printf("\n");
		}
	} catch (nmea::unknown_sentence & error) {
		fmt::printf("%s%s%s\n\terror: unknown sentence: %s\n\n", terminal::red, line,
			terminal::normal, error.what());
	} catch (nmea::checksum_error & error) {
		fmt::printf("%s%s%s\n\terror: checksum error: %s\n\n", terminal::red, line,
			terminal::normal, error.what());
	} catch (std::invalid_argument & error) {
		fmt::printf(
			"%s%s%s\n\terror: %s\n\n", terminal::red, line, terminal::normal, error.what());
	}
}

static void dump_ais(const std::vector<std::unique_ptr<marnav::nmea::sentence>> & sentences)
{
#define ADD_MESSAGE(m)                               \
	{                                                \
		marnav::ais::m::ID, detail::print_detail_##m \
	}
	struct entry {
		marnav::ais::message_id id;
		std::function<void(const marnav::ais::message *)> func;
	};
	using container = std::vector<entry>;
	// clang-format off
	static const container messages = {
		ADD_MESSAGE(message_01),
		ADD_MESSAGE(message_02),
		ADD_MESSAGE(message_03),
		ADD_MESSAGE(message_04),
		ADD_MESSAGE(message_05),
		ADD_MESSAGE(message_06),
		ADD_MESSAGE(message_07),
		ADD_MESSAGE(message_08),
		ADD_MESSAGE(message_09),
		ADD_MESSAGE(message_10),
		ADD_MESSAGE(message_11),
		ADD_MESSAGE(message_12),
		ADD_MESSAGE(message_13),
		ADD_MESSAGE(message_14),
		ADD_MESSAGE(message_17),
		ADD_MESSAGE(message_18),
		ADD_MESSAGE(message_19),
		ADD_MESSAGE(message_20),
		ADD_MESSAGE(message_21),
		ADD_MESSAGE(message_22),
		ADD_MESSAGE(message_23),
		ADD_MESSAGE(message_24)
	};
// clang-format on
#undef ADD_MESSAGE

	using namespace marnav;

	try {
		auto m = ais::make_message(nmea::collect_payload(sentences.begin(), sentences.end()));
		auto i = std::find_if(std::begin(messages), std::end(messages),
			[&m](const container::value_type & item) { return item.id == m->type(); });
		if (i == std::end(messages)) {
			fmt::printf("\t%s\n", detail::render(m->type()));
			fmt::printf("%smessage_%02u%s\n\tnot implemented\n\n", terminal::magenta,
				static_cast<uint8_t>(m->type()), terminal::normal);
		} else {
			fmt::printf("\t%s\n", detail::render(m->type()));
			i->func(m.get());
			fmt::printf("\n");
		}
	} catch (std::exception & error) {
		fmt::printf("\t%serror:%s %s\n\n", terminal::red, terminal::normal, error.what());
	}
}

static void process(std::function<bool(std::string &)> source)
{
	using namespace marnav;

	std::string line;
	std::vector<std::unique_ptr<nmea::sentence>> sentences;

	while (source(line)) {
		line = trim(line);
		if (line.empty())
			continue;
		if (line[0] == '#')
			continue;

		if (line[0] == nmea::sentence::start_token) {
			dump_nmea(line);
		} else if (line[0] == nmea::sentence::start_token_ais) {
			fmt::printf("%s%s%s\n", terminal::blue, line, terminal::normal);
			auto s = nmea::make_sentence(line);

			nmea::vdm * v = nullptr; // VDM is the common denominator for AIS relevant messages

			if (s->id() == nmea::sentence_id::VDO) {
				v = nmea::sentence_cast<nmea::vdo>(s.get());
			} else if (s->id() == nmea::sentence_id::VDM) {
				v = nmea::sentence_cast<nmea::vdm>(s.get());
			} else {
				// something strange happened, no VDM nor VDO
				fmt::printf("%s%s%s\n\terror: ignoring AIS sentence, dropping collection.\n\n",
					terminal::red, line, terminal::normal);
				sentences.clear();
				continue;
			}

			// check sentences if a discontuniation has occurred
			if (sentences.size() && (sentences.back()->id() != v->id())) {
				sentences.clear(); // there was a discontinuation, start over collecting
				fmt::printf(
					"\t%swarning:%s dropping collection.\n", terminal::cyan, terminal::normal);
			}

			// check if a previous message was not complete
			const auto n_fragments = v->get_n_fragments();
			const auto fragment = v->get_fragment();
			if (sentences.size() >= fragment) {
				sentences.clear();
				fmt::printf(
					"\t%swarning:%s dropping collection.\n", terminal::cyan, terminal::normal);
			}

			sentences.push_back(std::move(s));
			if (fragment == n_fragments) {
				dump_ais(sentences);
				sentences.clear();
			}
		} else {
			fmt::printf("%s%s%s\n\terror: ignoring AIS sentence.\n\n", terminal::red, line,
				terminal::normal);
		}
	}
}
}

int main(int argc, char ** argv)
{
	using namespace nmeadump;

	if (parse_options(argc, argv))
		return EXIT_SUCCESS;

	if (!global.config.file.empty()) {
		std::ifstream ifs{global.config.file.c_str()};
		process([&](std::string & line) { return !!std::getline(ifs, line); });
	} else if (!global.config.port.empty()) {
		using namespace marnav;
		using namespace marnav::io;
		default_nmea_reader source{
			utils::make_unique<serial>(global.config.port, global.config.speed,
				serial::databits::bit_8, serial::stopbits::bit_1, serial::parity::none)};
		process([&](std::string & line) { return source.read_sentence(line); });
	} else if (!global.config.input_string.empty()) {
		std::istringstream is(global.config.input_string);
		process([&](std::string & line) { return !!std::getline(is, line); });
	} else {
		std::cin.sync_with_stdio(false);
		process([&](std::string & line) { return !!std::getline(std::cin, line); });
	}

	return EXIT_SUCCESS;
}
