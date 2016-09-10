#include <fstream>
#include <iostream>
#include <vector>

#include <cxxopts/cxxopts.hpp>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include <marnav/nmea/nmea.hpp>
#include <marnav/nmea/checksum.hpp>
#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/waypoint.hpp>

#include <marnav/nmea/aam.hpp>
#include <marnav/nmea/apb.hpp>
#include <marnav/nmea/bod.hpp>
#include <marnav/nmea/dbt.hpp>
#include <marnav/nmea/dtm.hpp>
#include <marnav/nmea/gga.hpp>
#include <marnav/nmea/gll.hpp>
#include <marnav/nmea/gsa.hpp>
#include <marnav/nmea/gsv.hpp>
#include <marnav/nmea/hdg.hpp>
#include <marnav/nmea/mtw.hpp>
#include <marnav/nmea/mwv.hpp>
#include <marnav/nmea/rmb.hpp>
#include <marnav/nmea/rmc.hpp>
#include <marnav/nmea/rte.hpp>
#include <marnav/nmea/vtg.hpp>
#include <marnav/nmea/zda.hpp>

#include <marnav/nmea/pgrme.hpp>
#include <marnav/nmea/pgrmm.hpp>
#include <marnav/nmea/pgrmz.hpp>

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
		uint32_t port_speed = 0;
		std::string file;
	} config;
} global;

static bool parse_options(int argc, char ** argv)
{
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
			cxxopts::value<uint32_t>(global.config.port_speed))
		("f,file",
			"Specifies the file to use.",
			cxxopts::value<std::string>(global.config.file))
		;
	// clang-format on

	options.parse(argc, argv);

	if (options.count("help")) {
		fmt::printf("%s\n", options.help());
		fmt::printf("If no file or port is specified, stdin is used to read data from.\n\n");
		return true;
	}

	// validation

	static const std::vector<uint32_t> valid_port_speeds = {4800, 38400};

	if (options.count("port") && options.count("file"))
		throw std::runtime_error{"specifying port and file is illegal"};
	if (options.count("port") && !contains(valid_port_speeds, global.config.port_speed))
		throw std::runtime_error{"invalid port speed"};

	return false;
}

static std::string trim(const std::string & s)
{
	static const char * whitespace = "\n\r\t ";
	const auto begin = s.find_first_not_of(whitespace);
	const auto end = s.find_last_not_of(whitespace);
	return begin != std::string::npos ? s.substr(begin, end - begin + 1) : "";
}

namespace detail
{
template <typename T> static std::string render(const T & t)
{
	return marnav::nmea::to_string(t);
}

static std::string render(const std::string & t) { return t; }

static std::string render(char t) { return fmt::sprintf("%c", t); }

static std::string render(const uint32_t t) { return fmt::sprintf("%u", t); }

static std::string render(const int32_t t) { return fmt::sprintf("%d", t); }

static std::string render(const double t) { return fmt::sprintf("%-8.3f", t); }

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

static std::string render(const marnav::nmea::unit::distance t)
{
	switch (t) {
		case marnav::nmea::unit::distance::meter:
			return "m";
		case marnav::nmea::unit::distance::feet:
			return "ft";
		case marnav::nmea::unit::distance::nm:
			return "nm";
		case marnav::nmea::unit::distance::km:
			return "km";
		case marnav::nmea::unit::distance::fathom:
			return "fathom";
		default:
			break;
	}
	return "-";
}

static std::string render(const marnav::nmea::unit::temperature t)
{
	switch (t) {
		case marnav::nmea::unit::temperature::celsius:
			return "\u00b0C";
		default:
			break;
	}
	return "-";
}

static std::string render(const marnav::nmea::unit::velocity t)
{
	switch (t) {
		case marnav::nmea::unit::velocity::knot:
			return "kn";
		case marnav::nmea::unit::velocity::kmh:
			return "km/h";
		case marnav::nmea::unit::velocity::mps:
			return "m/s";
		default:
			break;
	}
	return "-";
}

static std::string render(const marnav::nmea::side t)
{
	switch (t) {
		case marnav::nmea::side::left:
			return "Left";
		case marnav::nmea::side::right:
			return "Rigth";
		default:
			break;
	}
	return "-";
}

static std::string render(const marnav::nmea::reference t)
{
	switch (t) {
		case marnav::nmea::reference::RELATIVE:
			return "relative";
		case marnav::nmea::reference::TRUE:
			return "true";
		case marnav::nmea::reference::MAGNETIC:
			return "magnetic";
		default:
			break;
	}
	return "-";
}

static std::string render(const marnav::nmea::quality t)
{
	switch (t) {
		case marnav::nmea::quality::invalid:
			return "invaild";
		case marnav::nmea::quality::gps_fix:
			return "GPS fix";
		case marnav::nmea::quality::dgps_fix:
			return "DGPS fix";
		case marnav::nmea::quality::guess:
			return "guess";
		case marnav::nmea::quality::simulation:
			return "simulation";
		default:
			break;
	}
	return "-";
}

static std::string render(const marnav::nmea::direction t)
{
	switch (t) {
		case marnav::nmea::direction::north:
			return "N";
		case marnav::nmea::direction::south:
			return "S";
		case marnav::nmea::direction::west:
			return "W";
		case marnav::nmea::direction::east:
			return "E";
		default:
			break;
	}
	return "-";
}

static std::string render(const marnav::nmea::selection_mode t)
{
	switch (t) {
		case marnav::nmea::selection_mode::manual:
			return "manual";
		case marnav::nmea::selection_mode::automatic:
			return "automatic";
		default:
			break;
	}
	return "-";
}

static std::string render(const marnav::nmea::status t)
{
	switch (t) {
		case marnav::nmea::status::ok:
			return "OK";
		case marnav::nmea::status::warning:
			return "Warning";
		default:
			break;
	}
	return "-";
}

static std::string render(const marnav::nmea::route t)
{
	switch (t) {
		case marnav::nmea::route::complete:
			return "complete";
		case marnav::nmea::route::working:
			return "working";
		default:
			break;
	}
	return "-";
}

static std::string render(const marnav::nmea::waypoint & t) { return t.c_str(); }

static std::string render(const marnav::nmea::mode_indicator t)
{
	switch (t) {
		case marnav::nmea::mode_indicator::invalid:
			return "invalid";
		case marnav::nmea::mode_indicator::autonomous:
			return "autonomous";
		case marnav::nmea::mode_indicator::differential:
			return "differential";
		case marnav::nmea::mode_indicator::estimated:
			return "estimated";
		case marnav::nmea::mode_indicator::manual_input:
			return "manual input";
		case marnav::nmea::mode_indicator::simulated:
			return "simulated";
		case marnav::nmea::mode_indicator::data_not_valid:
			return "not valid";
		case marnav::nmea::mode_indicator::precise:
			return "precise";
		default:
			break;
	}
	return "-";
}

template <typename T> static std::string render(const marnav::utils::optional<T> & t)
{
	if (!t)
		return "-";
	return render(*t);
}

static void print(const std::string & name, const std::string & value)
{
	fmt::printf("\t%-30s : %s\n", name, value);
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

static void print_detail_rmb(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::rmb>(s);
	print("Active", render(t->get_active()));
	print("Cross Track Error", render(t->get_cross_track_error()));
	print("Waypoint To", render(t->get_waypoint_to()));
	print("Waypoint From", render(t->get_waypoint_from()));
	print("Latitude", render(t->get_latitude()));
	print("Longitude", render(t->get_longitude()));
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
	print("Latitude", render(t->get_latitude()));
	print("Longitude", render(t->get_longitude()));
	print("SOG", render(t->get_sog()));
	print("Heading", render(t->get_heading()));
	print("Date", render(t->get_date()));
	print("Magn Dev", fmt::sprintf("%s %s", render(t->get_mag()), render(t->get_mag_hem())));
	print("Mode Ind ", render(t->get_mode_ind()));
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
	print("Latitude", render(t->get_latitude()));
	print("Longitude", render(t->get_longitude()));
	print("Time UTC", render(t->get_time_utc()));
	print("Status", render(t->get_data_valid()));
	print("Mode Indicator", render(t->get_mode_ind()));
}

static void print_detail_bod(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::bod>(s);
	print("Bearing True", render(t->get_bearing_true()));
	print("Bearing Magn", render(t->get_bearing_magn()));
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

static void print_detail_gga(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::gga>(s);
	print("Time", render(t->get_time()));
	print("Latitude", render(t->get_latitude()));
	print("Longitude", render(t->get_longitude()));
	print("Quality Ind", render(t->get_quality_indicator()));
	print("Num Satellites", render(t->get_n_satellites()));
	print("Horiz Dilution", render(t->get_hor_dilution()));
	print("Altitude",
		fmt::sprintf("%s %s", render(t->get_altitude()), render(t->get_altitude_unit())));
	print("Geodial Sep", fmt::sprintf("%s %s", render(t->get_geodial_separation()),
							 render(t->get_geodial_separation_unit())));
	print("DGPS Age", render(t->get_dgps_age()));
	print("DGPS Ref", render(t->get_dgps_ref()));
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
			print("Sat", fmt::sprintf("ID:%02u ELEV:%02u AZIMUTH:%03u SNR:%02u", sat->id,
							 sat->elevation, sat->azimuth, sat->snr));
		}
	}
}

static void print_detail_zda(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::zda>(s);
	print("Time UTC", render(t->get_time_utc()));
	print("Day", render(t->get_day()));
	print("Month", render(t->get_month()));
	print("Year", render(t->get_year()));
	print("Local Zone Hours", render(t->get_local_zone_hours()));
	print("Local Zone Min", render(t->get_local_zone_minutes()));
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
	print("Altitude", render(t->get_altitude()));
	print("Name", render(t->get_name()));
}

static void print_detail_aam(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::aam>(s);
	print("Arrival Circle Entred", render(t->get_arrival_circle_entered()));
	print("Perpendicular Passed", render(t->get_perpendicualar_passed()));
	print("Arrival Circle Radius", fmt::sprintf("%s %s", render(t->get_arrival_circle_radius()),
									   render(t->get_arrival_circle_radius_unit())));
	print("Waypoint", render(t->get_waypoint_id()));
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

static void print_detail_mtw(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::mtw>(s);
	print("Water Temperature",
		fmt::sprintf("%s %s", render(t->get_temperature()), render(t->get_temperature_unit())));
}

static void print_detail_dbt(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::dbt>(s);
	print("Depth Feet", render(t->get_depth_feet()));
	print("Depth Meter", render(t->get_depth_meter()));
	print("Depth Fathom", render(t->get_depth_fathom()));
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
}

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
	static const container sentences = {
		// standard
		ADD_SENTENCE(aam),
		ADD_SENTENCE(apb),
		ADD_SENTENCE(bod),
		ADD_SENTENCE(dbt),
		ADD_SENTENCE(dtm),
		ADD_SENTENCE(gga),
		ADD_SENTENCE(gll),
		ADD_SENTENCE(gsa),
		ADD_SENTENCE(gsv),
		ADD_SENTENCE(hdg),
		ADD_SENTENCE(mtw),
		ADD_SENTENCE(mwv),
		ADD_SENTENCE(rmb),
		ADD_SENTENCE(rmc),
		ADD_SENTENCE(rte),
		ADD_SENTENCE(vtg),
		ADD_SENTENCE(zda),

		// proprietary
		ADD_SENTENCE(pgrme),
		ADD_SENTENCE(pgrmm),
		ADD_SENTENCE(pgrmz)
	};
#undef ADD_SENTENCE

	using namespace marnav;

	try {
		auto s = nmea::make_sentence(line);
		auto i = std::find_if(std::begin(sentences), std::end(sentences),
			[&s](const container::value_type & item) { return item.id == s->id(); });
		if (i == std::end(sentences)) {
			fmt::printf(
				"%s%s%s\n\tnot implemented\n\n", terminal::magenta, line, terminal::normal);
		} else {
			fmt::printf("%s%s%s\n", terminal::green, line, terminal::normal);
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

static void dump_stream(std::istream & is)
{
	while (is) {
		std::string line;
		std::getline(is, line);
		line = trim(line);

		if (line.empty())
			continue;
		if (line[0] == '#')
			continue;

		switch (line[0]) {
			case marnav::nmea::sentence::start_token:
				dump_nmea(line);
				break;
			case marnav::nmea::sentence::start_token_ais:
				// TODO
				break;
			default:
				fmt::printf("%s\n", line);
				break;
		}
	}
}

static void dump_file(const std::string & filename)
{
	std::ifstream ifs{filename.c_str()};
	dump_stream(ifs);
}

static void dump_port(const std::string &, uint32_t)
{
	throw std::runtime_error{"NOT IMPLEMENTED"};
}

static void dump_stdin() { dump_stream(std::cin); }
}

int main(int argc, char ** argv)
{
	using namespace nmeadump;

	if (parse_options(argc, argv))
		return EXIT_SUCCESS;

	if (!global.config.file.empty()) {
		dump_file(global.config.file);
	} else if (!global.config.port.empty()) {
		dump_port(global.config.port, global.config.port_speed);
	} else {
		dump_stdin();
	}

	return EXIT_SUCCESS;
}
