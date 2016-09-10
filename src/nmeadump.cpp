#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cxxopts.hpp>
#include <marnav/nmea/nmea.hpp>
#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/checksum.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/nmea/bod.hpp>
#include <marnav/nmea/dtm.hpp>
#include <marnav/nmea/gga.hpp>
#include <marnav/nmea/gll.hpp>
#include <marnav/nmea/gsa.hpp>
#include <marnav/nmea/gsv.hpp>
#include <marnav/nmea/hdg.hpp>
#include <marnav/nmea/mwv.hpp>
#include <marnav/nmea/rmb.hpp>
#include <marnav/nmea/rmc.hpp>
#include <marnav/nmea/vtg.hpp>
#include <marnav/nmea/zda.hpp>
#include <marnav/nmea/pgrme.hpp>
#include <marnav/nmea/pgrmm.hpp>
#include <marnav/nmea/pgrmz.hpp>

namespace nmeadump
{
namespace terminal
{
static constexpr const char * normal  = "\033[0m";
static constexpr const char * black   = "\033[30m";
static constexpr const char * red     = "\033[31m";
static constexpr const char * green   = "\033[32m";
static constexpr const char * yellow  = "\033[33m";
static constexpr const char * blue    = "\033[34m";
static constexpr const char * magenta = "\033[35m";
static constexpr const char * cyan    = "\033[36m";
static constexpr const char * white   = "\033[37m";
}

namespace
{
template <class Container>
static bool contains(const Container & container, const typename Container::value_type & element)
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
		std::cout << options.help() << '\n';
		std::cout << "If no file or port is specified, stdin is used to read data from.\n";
		std::cout << '\n';
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

static std::string render(const std::string & t)
{
	return t;
}

static std::string render(char t)
{
	return std::string{} + t;
}

static std::string render(const uint32_t t)
{
	std::stringstream s;
	s << t;
	return s.str();
}

static std::string render(const int32_t t)
{
	std::stringstream s;
	s << t;
	return s.str();
}

static std::string render(const double t)
{
	std::stringstream s;
	s << std::left << std::setw(7) << std::setprecision(5) << t;
	return s.str();
}

static std::string render(const marnav::nmea::time & t)
{
	using namespace marnav::nmea;

	std::stringstream s;
	s << std::setw(2) << std::setfill('0') << t.hour() << ':' << std::setw(2)
	  << std::setfill('0') << t.minutes() << ':' << std::setw(2) << std::setfill('0')
	  << t.seconds();
	return s.str();
}

static std::string render(const marnav::geo::latitude & t)
{
	using namespace marnav::nmea;

	std::stringstream s;
	s << ' ' << std::setw(2) << std::setfill('0') << t.degrees() << "\u00b0" << std::setw(2)
	  << std::setfill('0') << t.minutes() << '\'' << std::setw(4) << std::setprecision(3)
	  << std::setfill('0') << t.seconds() << to_string(t.hem());
	return s.str();
}

static std::string render(const marnav::geo::longitude & t)
{
	using namespace marnav::nmea;

	std::stringstream s;
	s << std::setw(3) << std::setfill('0') << t.degrees() << "\u00b0" << std::setw(2)
	  << std::setfill('0') << t.minutes() << '\'' << std::setw(4) << std::setprecision(3)
	  << std::setfill('0') << t.seconds() << to_string(t.hem());
	return s.str();
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

static std::string render(const marnav::nmea::waypoint & t)
{
	return t.c_str();
}

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

static void print_detail_hdg(std::ostream & os, const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::hdg>(s);
	os << '\t' << "Heading          : " << render(t->get_heading()) << '\n';
	os << '\t' << "Magn Deviation   : " << render(t->get_magn_dev()) << ' '
	   << render(t->get_magn_dev_hem()) << '\n';
	os << '\t' << "Magn Variation   : " << render(t->get_magn_var()) << ' '
	   << render(t->get_magn_var_hem()) << '\n';
}

static void print_detail_rmb(std::ostream & os, const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::rmb>(s);
	os << '\t' << "Active           : " << render(t->get_active()) << '\n';
	os << '\t' << "Cross Track Error: " << render(t->get_cross_track_error()) << '\n';
	os << '\t' << "Waypoint To      : " << render(t->get_waypoint_to()) << '\n';
	os << '\t' << "Waypoint From    : " << render(t->get_waypoint_from()) << '\n';
	os << '\t' << "Latitude         : " << render(t->get_latitude()) << '\n';
	os << '\t' << "Longitude        : " << render(t->get_longitude()) << '\n';
	os << '\t' << "Range            : " << render(t->get_range()) << '\n';
	os << '\t' << "Bearing          : " << render(t->get_bearing()) << '\n';
	os << '\t' << "Dest. Velocity   : " << render(t->get_dst_velocity()) << '\n';
	os << '\t' << "Arrival Status   : " << render(t->get_arrival_status()) << '\n';
	os << '\t' << "Mode Indicator   : " << render(t->get_mode_ind()) << '\n';
}

static void print_detail_rmc(std::ostream & os, const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::rmc>(s);
	os << '\t' << "Time UTC         : " << render(t->get_time_utc()) << '\n';
	os << '\t' << "Status           : " << render(t->get_status()) << '\n';
	os << '\t' << "Latitude         : " << render(t->get_latitude()) << '\n';
	os << '\t' << "Longitude        : " << render(t->get_longitude()) << '\n';
	os << '\t' << "SOG              : " << render(t->get_sog()) << '\n';
	os << '\t' << "Heading          : " << render(t->get_heading()) << '\n';
	os << '\t' << "Date             : " << render(t->get_date()) << '\n';
	os << '\t' << "Magn Dev         : " << render(t->get_mag()) << '\n';
	os << '\t' << "Magn Hem         : " << render(t->get_mag_hem()) << '\n';
	os << '\t' << "Mode Ind         : " << render(t->get_mode_ind()) << '\n';
}

static void print_detail_vtg(std::ostream & os, const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::vtg>(s);
	os << '\t' << "Track True       : " << render(t->get_track_true()) << '\n';
	os << '\t' << "Track Magn       : " << render(t->get_track_magn()) << '\n';
	os << '\t' << "Speed Knots      : " << render(t->get_speed_kn()) << '\n';
	os << '\t' << "Speed kmh        : " << render(t->get_speed_kmh()) << '\n';
	os << '\t' << "Mode Indicator   : " << render(t->get_mode_ind()) << '\n';
}

static void print_detail_gll(std::ostream & os, const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::gll>(s);
	os << '\t' << "Latitude         : " << render(t->get_latitude()) << '\n';
	os << '\t' << "Longitude        : " << render(t->get_longitude()) << '\n';
	os << '\t' << "Time UTC         : " << render(t->get_time_utc()) << '\n';
	os << '\t' << "Status           : " << render(t->get_data_valid()) << '\n';
	os << '\t' << "Mode Indicator   : " << render(t->get_mode_ind()) << '\n';
}

static void print_detail_bod(std::ostream & os, const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::bod>(s);
	os << '\t' << "Bearing True     : " << render(t->get_bearing_true()) << '\n';
	os << '\t' << "Bearing Magn     : " << render(t->get_bearing_magn()) << '\n';
	os << '\t' << "Waypoint To      : " << render(t->get_waypoint_to()) << '\n';
	os << '\t' << "Waypoint From    : " << render(t->get_waypoint_from()) << '\n';
}

static void print_detail_gsa(std::ostream & os, const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::gsa>(s);
	os << '\t' << "Selection Mode   : " + render(t->get_sel_mode()) << '\n';
	os << '\t' << "Mode             : " + render(t->get_mode()) << '\n';
	for (auto i = 0; i < marnav::nmea::gsa::max_satellite_ids; ++i) {
		os << '\t' << "Satellite " << std::setw(2) << i << "     : "
		   << render(t->get_satellite_id(i)) << '\n';
	}
	os << '\t' << "PDOP             : " + render(t->get_pdop()) << '\n';
	os << '\t' << "HDOP             : " + render(t->get_hdop()) << '\n';
	os << '\t' << "VDOP             : " + render(t->get_vdop()) << '\n';
}

static void print_detail_gga(std::ostream & os, const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::gga>(s);
	os << '\t' << "Time             : " << render(t->get_time()) << '\n';
	os << '\t' << "Latitude         : " << render(t->get_latitude()) << '\n';
	os << '\t' << "Longitude        : " << render(t->get_longitude()) << '\n';
	os << '\t' << "Quality Ind      : " << render(t->get_quality_indicator()) << '\n';
	os << '\t' << "Num Satellites   : " << render(t->get_n_satellites()) << '\n';
	os << '\t' << "Horiz Dilution   : " << render(t->get_hor_dilution()) << '\n';
	os << '\t' << "Altitude         : " << render(t->get_altitude()) << '\n';
	os << '\t' << "Altitude Unit    : " << render(t->get_altitude_unit()) << '\n';
	os << '\t' << "Geodial Sep      : " << render(t->get_geodial_separation()) << '\n';
	os << '\t' << "Geodial Sep Unit : " << render(t->get_geodial_separation_unit()) << '\n';
	os << '\t' << "DGPS Age         : " << render(t->get_dgps_age()) << '\n';
	os << '\t' << "DGPS Ref         : " << render(t->get_dgps_ref()) << '\n';
}

static void print_detail_mwv(std::ostream & os, const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::mwv>(s);
	os << '\t' << "Angle            : " << render(t->get_angle()) << '\n';
	os << '\t' << "Angle Ref        : " << render(t->get_angle_ref()) << '\n';
	os << '\t' << "Speed            : " << render(t->get_speed()) << '\n';
	os << '\t' << "Speed Unit       : " << render(t->get_speed_unit()) << '\n';
	os << '\t' << "Data Valid       : " << render(t->get_data_valid()) << '\n';
}

static void print_detail_gsv(std::ostream & os, const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::gsv>(s);
	os << '\t' << "Num Messages     : " << render(t->get_n_messages()) << '\n';
	os << '\t' << "Messages Number  : " << render(t->get_message_number()) << '\n';
	os << '\t' << "Num Sat in View  : " << render(t->get_n_satellites_in_view()) << '\n';
	for (int i = 0; i < 4; ++i) {
		const auto sat = t->get_sat(i);
		if (sat) {
			os << '\t' << "Sat              : "
			   << "ID:" << std::setw(2) << std::setfill('0') << render(sat->id) << "  "
			   << "ELEV:" << std::setw(2) << std::setfill('0') << render(sat->elevation) << "  "
			   << "AZIMUTH:" << std::setw(3) << std::setfill('0') << render(sat->azimuth)
			   << "  "
			   << "SNR:" << std::setw(2) << std::setfill('0') << render(sat->snr) << '\n';
		}
	}
}

static void print_detail_zda(std::ostream & os, const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::zda>(s);
	os << '\t' << "Time UTC         : " << render(t->get_time_utc()) << '\n';
	os << '\t' << "Day              : " << render(t->get_day()) << '\n';
	os << '\t' << "Month            : " << render(t->get_month()) << '\n';
	os << '\t' << "Year             : " << render(t->get_year()) << '\n';
	os << '\t' << "Local Zone Hours : " << render(t->get_local_zone_hours()) << '\n';
	os << '\t' << "Local Zone Min   : " << render(t->get_local_zone_minutes()) << '\n';
}

static void print_detail_dtm(std::ostream & os, const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::dtm>(s);
	os << '\t' << "Ref              : " << render(t->get_ref()) << '\n';
	os << '\t' << "Subcode          : " << render(t->get_subcode()) << '\n';
	os << '\t' << "Latitude Offset  : " << render(t->get_lat_offset()) << '\n';
	os << '\t' << "Latitude Hem     : " << render(t->get_lat_hem()) << '\n';
	os << '\t' << "Longitude Offset : " << render(t->get_lon_offset()) << '\n';
	os << '\t' << "Longitude Hem    : " << render(t->get_lon_hem()) << '\n';
	os << '\t' << "Altitude         : " << render(t->get_altitude()) << '\n';
	os << '\t' << "Name             : " << render(t->get_name()) << '\n';
}

static void print_detail_pgrme(std::ostream & os, const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::pgrme>(s);
	os << '\t' << "HPE              : " << render(t->get_horizontal_position_error()) << '\n';
	os << '\t' << "VPE              : " << render(t->get_vertical_position_error()) << '\n';
	os << '\t'
	   << "O.sph.eq.pos err : " << render(t->get_overall_spherical_equiv_position_error())
	   << '\n';
}

static void print_detail_pgrmm(std::ostream & os, const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::pgrmm>(s);
	os << '\t' << "Map Datum        : " << render(t->get_map_datum()) << '\n';
}

static void print_detail_pgrmz(std::ostream & os, const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::pgrmz>(s);
	os << '\t' << "Altitude         : " << render(t->get_altitude()) << " feet" << '\n';
	os << '\t' << "Fix Type         : " << render(t->get_fix()) << '\n';
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
		std::function<void(std::ostream &, const marnav::nmea::sentence *)> func;
	};
	using container = std::vector<entry>;
	static const container sentences = {
		// standard
		ADD_SENTENCE(bod),
		ADD_SENTENCE(dtm),
		ADD_SENTENCE(gga),
		ADD_SENTENCE(gll),
		ADD_SENTENCE(gsa),
		ADD_SENTENCE(gsv),
		ADD_SENTENCE(hdg),
		ADD_SENTENCE(mwv),
		ADD_SENTENCE(rmb),
		ADD_SENTENCE(rmc),
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
			std::cout << terminal::magenta << "unknown: " << terminal::normal << line << '\n'
					  << '\n';
		} else {
			std::cout << terminal::green << line << terminal::normal << '\n';
			i->func(std::cout, s.get());
			std::cout << '\n';
		}
	} catch (nmea::unknown_sentence & error) {
		std::cerr << terminal::red << "error: unknown sentence: " << terminal::normal << line
				  << '\n'
				  << '\t' << error.what() << '\n'
				  << '\n';
	} catch (nmea::checksum_error & error) {
		std::cerr << terminal::red << "error: checksum error: " << terminal::normal << line
				  << '\n'
				  << '\t' << error.what() << '\n'
				  << '\n';
	} catch (std::invalid_argument & error) {
		std::cerr << terminal::red << "error: " << terminal::normal << line << '\n'
				  << '\t' << error.what() << '\n'
				  << '\n';
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
				std::cout << line << '\n';
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

static void dump_stdin()
{
	dump_stream(std::cin);
}
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
