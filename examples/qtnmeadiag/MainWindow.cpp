#include "MainWindow.hpp"
#include <vector>
#include <QComboBox>
#include <QCoreApplication>
#include <QFileDialog>
#include <QFontDatabase>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMenuBar>
#include <QMessageBox>
#include <QPushButton>
#include <QSerialPort>
#include <QTextStream>
#include <QToolBar>
#include <marnav/nmea/checksum.hpp>
#include <marnav/nmea/nmea.hpp>
#include <marnav/nmea/bod.hpp>
#include <marnav/nmea/gga.hpp>
#include <marnav/nmea/gll.hpp>
#include <marnav/nmea/gsa.hpp>
#include <marnav/nmea/gsv.hpp>
#include <marnav/nmea/hdg.hpp>
#include <marnav/nmea/mwv.hpp>
#include <marnav/nmea/rmb.hpp>
#include <marnav/nmea/rmc.hpp>
#include <marnav/nmea/rte.hpp>
#include <marnav/nmea/vtg.hpp>
#include <marnav/nmea/pgrme.hpp>
#include <marnav/nmea/pgrmm.hpp>
#include <marnav/nmea/pgrmz.hpp>
#include <marnav/nmea/string.hpp>

namespace marnav_example
{
/// @cond DEV
namespace detail
{
static QString render(const marnav::nmea::status & t)
{
	return marnav::nmea::to_string(t).c_str();
}

static QString render(const marnav::nmea::direction & t)
{
	return marnav::nmea::to_string(t).c_str();
}

static QString render(const marnav::nmea::reference & t)
{
	return marnav::nmea::to_string(t).c_str();
}

static QString render(const marnav::nmea::date & t)
{
	return marnav::nmea::to_string(t).c_str();
}

static QString render(const marnav::nmea::quality & t)
{
	return marnav::nmea::to_string(t).c_str();
}

static QString render(const marnav::nmea::pgrmz::fix_type & t)
{
	return marnav::nmea::to_string(t).c_str();
}

static QString render(const marnav::nmea::unit::distance & t)
{
	return marnav::nmea::to_string(t).c_str();
}

static QString render(const marnav::nmea::unit::velocity & t)
{
	return marnav::nmea::to_string(t).c_str();
}

static QString render(uint32_t t)
{
	return QString{"%1"}.arg(t);
}

static QString render(const std::string & t)
{
	return QString{t.c_str()};
}

static QString render(const marnav::nmea::time & t)
{
	return QString{"%1:%2:%3"}
		.arg(t.hour(), 2, 10, QLatin1Char('0'))
		.arg(t.minutes(), 2, 10, QLatin1Char('0'))
		.arg(t.seconds(), 2, 10, QLatin1Char('0'));
}

static QString render(const marnav::geo::latitude & t)
{
	return QString{" %1°%2'%3%4"}
		.arg(t.degrees(), 2, 10, QLatin1Char('0'))
		.arg(t.minutes(), 2, 10, QLatin1Char('0'))
		.arg(t.seconds(), 2, 'f', 1, QLatin1Char('0'))
		.arg(to_string(t.hem()).c_str());
}

static QString render(const marnav::geo::longitude & t)
{
	return QString{"%1°%2'%3%4"}
		.arg(t.degrees(), 3, 10, QLatin1Char('0'))
		.arg(t.minutes(), 2, 10, QLatin1Char('0'))
		.arg(t.seconds(), 2, 'f', 1, QLatin1Char('0'))
		.arg(to_string(t.hem()).c_str());
}

static QString render(const marnav::nmea::selection_mode & t)
{
	switch (t) {
		case marnav::nmea::selection_mode::manual:
			return QString{"manual"};
		case marnav::nmea::selection_mode::automatic:
			return QString{"automatic"};
		default:
			break;
	}
	return "-";
}

static QString render(const marnav::nmea::route & t)
{
	switch (t) {
		case marnav::nmea::route::complete:
			return QString{"complete"};
		case marnav::nmea::route::working:
			return QString{"working"};
		default:
			break;
	}
	return "-";
}

static QString render(const marnav::nmea::waypoint & t)
{
	return t.c_str();
}

static QString render(const marnav::nmea::mode_indicator & t)
{
	switch (t) {
		case marnav::nmea::mode_indicator::invalid:
			return QString{"invalid"};
		case marnav::nmea::mode_indicator::autonomous:
			return QString{"autonomous"};
		case marnav::nmea::mode_indicator::differential:
			return QString{"differential"};
		case marnav::nmea::mode_indicator::estimated:
			return QString{"estimated"};
		case marnav::nmea::mode_indicator::manual_input:
			return QString{"manual input"};
		case marnav::nmea::mode_indicator::simulated:
			return QString{"simulated"};
		case marnav::nmea::mode_indicator::data_not_valid:
			return QString{"not valid"};
		case marnav::nmea::mode_indicator::precise:
			return QString{"precise"};
		default:
			break;
	}
	return "-";
}

static QString render(const marnav::units::length & t)
{
	return QString{"%1 NM"}.arg(t.get<marnav::units::nautical_miles>().value());
}

static QString render(const marnav::units::velocity & t)
{
	return QString{"%1 knots"}.arg(t.get<marnav::units::knots>().value());
}

template <typename T> static QString render(const marnav::utils::optional<T> & t)
{
	if (!t)
		return "-";
	return render(*t);
}

static QString details_rmb(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::rmb>(s);
	QString result;
	result += "\nActive           : " + render(t->get_active());
	result += "\nCross Track Error: " + render(t->get_cross_track_error());
	result += "\nWaypoint From    : " + render(t->get_waypoint_from());
	result += "\nWaypoint To      : " + render(t->get_waypoint_to());
	result += "\nLatitude         : " + render(t->get_lat());
	result += "\nLongitude        : " + render(t->get_lon());
	result += "\nRange            : " + render(t->get_range());
	result += "\nBearing          : " + render(t->get_bearing());
	result += "\nDest. Velocity   : " + render(t->get_dst_velocity());
	result += "\nArrival Status   : " + render(t->get_arrival_status());
	result += "\nMode Indicator   : " + render(t->get_mode_ind());
	return result;
}

static QString details_rmc(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::rmc>(s);
	QString result;
	result += "\nTime UTC : " + render(t->get_time_utc());
	result += "\nStatus   : " + render(t->get_status());
	result += "\nLatitude : " + render(t->get_lat());
	result += "\nLongitude: " + render(t->get_lon());
	result += "\nSOG      : " + render(t->get_sog());
	result += "\nHeading  : " + render(t->get_heading());
	result += "\nDate     : " + render(t->get_date());
	result += "\nMagn Dev : " + render(t->get_mag());
	result += "\nMagn Hem : " + render(t->get_mag_hem());
	result += "\nMode Ind : " + render(t->get_mode_ind());
	return result;
}

static QString details_mwv(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::mwv>(s);
	QString result;
	result += "\nAngle     : " + render(t->get_angle());
	result += "\nAngle Ref : " + render(t->get_angle_ref());
	result += "\nSpeed     : " + render(t->get_speed());
	result += "\nSpeed Unit: " + render(t->get_speed_unit());
	result += "\nData Valid: " + render(t->get_data_valid());
	return result;
}

static QString details_gga(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::gga>(s);
	QString result;
	result += "\nTime            : " + render(t->get_time());
	result += "\nLatitude        : " + render(t->get_lat());
	result += "\nLongitude       : " + render(t->get_lon());
	result += "\nQuality Ind     : " + render(t->get_quality_indicator());
	result += "\nNum Satellites  : " + render(t->get_n_satellites());
	result += "\nHoriz Dilution  : " + render(t->get_hor_dilution());
	result += "\nAltitude        : " + render(t->get_altitude());
	result += "\nGeodial Sep     : " + render(t->get_geodial_separation());
	result += "\nDGPS Age        : " + render(t->get_dgps_age());
	result += "\nDGPS Ref        : " + render(t->get_dgps_ref());
	return result;
}

static QString details_gsv(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::gsv>(s);
	QString result;
	result += "\nNum Messages   : " + render(t->get_n_messages());
	result += "\nMessages Number: " + render(t->get_message_number());
	result += "\nNum Sat in View: " + render(t->get_n_satellites_in_view());
	for (int i = 0; i < 4; ++i) {
		const auto sat = t->get_sat(i);
		if (sat) {
			result += QString{"\nSat: PRN:%1  ELEV:%2  AZIMUTH:%3  SNR:%4"}
						  .arg(render(sat->prn), 2)
						  .arg(render(sat->elevation), 2)
						  .arg(render(sat->azimuth), 3)
						  .arg(render(sat->snr), 2);
		}
	}
	return result;
}

static QString details_gsa(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::gsa>(s);
	QString result;
	result += "\nSelection Mode: " + render(t->get_sel_mode());
	result += "\nMode          : " + render(t->get_mode());
	for (auto i = 0; i < marnav::nmea::gsa::max_satellite_ids; ++i) {
		result += QString{"\nSatellite %1  : %2"}.arg(i, 2).arg(render(t->get_satellite_id(i)));
	}
	result += "\nPDOP          : " + render(t->get_pdop());
	result += "\nHDOP          : " + render(t->get_hdop());
	result += "\nVDOP          : " + render(t->get_vdop());
	return result;
}

static QString details_gll(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::gll>(s);
	QString result;
	result += "\nLatitude      : " + render(t->get_lat());
	result += "\nLongitude     : " + render(t->get_lon());
	result += "\nTime UTC      : " + render(t->get_time_utc());
	result += "\nStatus        : " + render(t->get_data_valid());
	result += "\nMode Indicator: " + render(t->get_mode_ind());
	return result;
}

static QString details_bod(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::bod>(s);
	QString result;
	result += "\nBearing True : " + render(t->get_bearing_true());
	result += "\nBearing Magn : " + render(t->get_bearing_magn());
	result += "\nWaypoint To  : " + render(t->get_waypoint_to());
	result += "\nWaypoint From: " + render(t->get_waypoint_from());
	return result;
}

static QString details_vtg(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::vtg>(s);
	QString result;
	result += "\nTrack True    : " + render(t->get_track_true());
	result += "\nTrack Magn    : " + render(t->get_track_magn());
	result += "\nSpeed Knots   : " + render(t->get_speed_kn());
	result += "\nSpeed kmh     : " + render(t->get_speed_kmh());
	result += "\nMode Indicator: " + render(t->get_mode_ind());
	return result;
}

static QString details_pgrme(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::pgrme>(s);
	QString result;
	result += "\nHPE                      : " + render(t->get_horizontal_position_error());
	result += "\nVPE                      : " + render(t->get_vertical_position_error());
	result += "\nOverall sph equiv pos err: "
		+ render(t->get_overall_spherical_equiv_position_error());
	return result;
}

static QString details_pgrmm(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::pgrmm>(s);
	QString result;
	result += "\nMap Datum: " + render(t->get_map_datum());
	return result;
}

static QString details_pgrmz(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::pgrmz>(s);
	QString result;
	result += "\nAltitude: " + render(t->get_altitude()) + " feet";
	result += "\nFix Type: " + render(t->get_fix());
	return result;
}

static QString details_hdg(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::hdg>(s);
	QString result;
	result += "\nHeading       : " + render(t->get_heading());
	result += "\nMagn Deviation: " + render(t->get_magn_dev()) + " "
		+ render(t->get_magn_dev_hem());
	result += "\nMagn Variation: " + render(t->get_magn_var()) + " "
		+ render(t->get_magn_var_hem());
	return result;
}

static QString details_rte(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::rte>(s);
	QString result;
	result += "\nNum Messages  : " + render(t->get_n_messages());
	result += "\nMessage Number: " + render(t->get_message_number());
	result += "\nMessage Mode  : " + render(t->get_message_mode());
	for (int i = 0; i < marnav::nmea::rte::max_waypoints; ++i) {
		const auto wp = t->get_waypoint_id(i);
		if (!wp)
			break;
		result += QString{"\nWaypoint ID %1: %2"}.arg(i, 2).arg(render(wp));
	}
	return result;
}
}
/// @endcond

static QString get_details(const marnav::nmea::sentence * s)
{
#define ADD_SENTENCE(s)                          \
	{                                            \
		marnav::nmea::s::ID, detail::details_##s \
	}

	struct entry {
		marnav::nmea::sentence_id id;
		std::function<QString(const marnav::nmea::sentence *)> func;
	};
	using container = std::vector<entry>;
	static const container details = {
		// common
		ADD_SENTENCE(bod), ADD_SENTENCE(gga), ADD_SENTENCE(gsa), ADD_SENTENCE(gll),
		ADD_SENTENCE(gsv), ADD_SENTENCE(hdg), ADD_SENTENCE(mwv), ADD_SENTENCE(rmb),
		ADD_SENTENCE(rmc), ADD_SENTENCE(rte), ADD_SENTENCE(vtg),

		// vendor specific
		ADD_SENTENCE(pgrme), ADD_SENTENCE(pgrmm), ADD_SENTENCE(pgrmz),
	};
#undef ADD_SENTENCE

	auto i = std::find_if(begin(details), end(details),
		[s](const container::value_type & entry) { return entry.id == s->id(); });

	return (i == end(details)) ? QString{"unknown"} : i->func(s);
}

MainWindow::MainWindow()
{
	setWindowTitle(QCoreApplication::instance()->applicationName());

	create_actions();
	create_menus();
	setup_ui();

	port = new QSerialPort(this);
}

MainWindow::~MainWindow()
{
	on_close();
}

void MainWindow::create_menus()
{
	auto menu_file = menuBar()->addMenu(tr("&File"));
	menu_file->addAction(action_open_file);
	menu_file->addSeparator();
	menu_file->addAction(action_open_port);
	menu_file->addAction(action_close_port);
	menu_file->addSeparator();
	menu_file->addAction(action_exit);

	auto menu_help = menuBar()->addMenu(tr("&Help"));
	menu_help->addAction(action_about);
	menu_help->addAction(action_about_qt);
}

void MainWindow::create_actions()
{
	action_exit = new QAction(tr("E&xit"), this);
	action_exit->setStatusTip(tr("Quits the application"));
	action_exit->setShortcut(tr("Ctrl+Q"));
	connect(action_exit, &QAction::triggered, this, &MainWindow::close);

	action_about = new QAction(tr("About ..."), this);
	action_about->setStatusTip(tr("Shows the About dialog"));
	connect(action_about, &QAction::triggered, this, &MainWindow::on_about);

	action_about_qt = new QAction(tr("About Qt ..."), this);
	action_about_qt->setStatusTip(tr("Shows information about Qt"));
	connect(action_about_qt, &QAction::triggered, this, &MainWindow::on_about_qt);

	action_open_port = new QAction(tr("Open Port"), this);
	action_open_port->setStatusTip(tr("Opens Communication Port to read data"));
	connect(action_open_port, &QAction::triggered, this, &MainWindow::on_open);

	action_close_port = new QAction(tr("Close Port"), this);
	action_close_port->setStatusTip(tr("Closes Communication Port"));
	connect(action_close_port, &QAction::triggered, this, &MainWindow::on_close);
	action_close_port->setEnabled(false);

	action_open_file = new QAction(tr("Open File"), this);
	action_open_file->setStatusTip(tr("Opens file containing NMEA sentences"));
	connect(action_open_file, &QAction::triggered, this, &MainWindow::on_open_file);
}

void MainWindow::setup_ui()
{
	QWidget * center = new QWidget(this);
	center->setMinimumWidth(1024);
	center->setMinimumHeight(600);

	sentence_list = new QListWidget(this);
	sentence_list->setSelectionMode(QAbstractItemView::SingleSelection);
	connect(sentence_list, &QListWidget::itemSelectionChanged, this,
		&MainWindow::on_sentence_selection);

	sentence_desc = new QLabel("", this);
	sentence_desc->setTextFormat(Qt::PlainText);
	sentence_desc->setAlignment(Qt::AlignLeft | Qt::AlignTop);

	QFont font{"Monospace"};
	font.setStyleHint(QFont::TypeWriter);

	sentence_list->setFont(font);
	sentence_desc->setFont(font);

	port_name = new QLineEdit(center);
	port_name->setText("/dev/ttyUSB0");
	cb_baudrate = new QComboBox(center);
	cb_baudrate->setEditable(false);
	cb_baudrate->addItems({"4800", "38400"});

	auto l1 = new QHBoxLayout;
	l1->addWidget(sentence_list, 2);
	l1->addWidget(sentence_desc, 1);

	auto l0 = new QGridLayout;
	l0->addWidget(new QLabel(tr("Port:"), this), 0, 0);
	l0->addWidget(port_name, 0, 1);
	l0->addWidget(cb_baudrate, 0, 2);
	l0->addLayout(l1, 1, 0, 1, 3);

	center->setLayout(l0);
	setCentralWidget(center);
}

void MainWindow::read_sentences_from_file(QString filename)
{
	QFile file{filename};
	if (!file.open(QFile::ReadOnly)) {
		QMessageBox::critical(this, "Error", "Unable to open file: " + filename);
		return;
	}

	QTextStream ifs(&file);
	do {
		QString s = ifs.readLine();
		if (s.isNull())
			break;
		if (s.isEmpty())
			continue;
		if (s.startsWith("#"))
			continue;
		add_item(s);
	} while (true);
}

void MainWindow::open_file(QString filename)
{
	QFileInfo file(filename);
	if (!file.exists())
		return;
	read_sentences_from_file(filename);
}

void MainWindow::on_open_file()
{
	auto filename
		= QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Text Files (*.txt)"));

	if (filename.size() == 0)
		return;

	sentence_list->clear();
	sentence_desc->setText("");

	read_sentences_from_file(filename);
}

void MainWindow::add_item(QString raw_sentence)
{
	// if the list grows too large, remove a certain amount from
	// the oldest entries before adding the new one.

	if (sentence_list->count() > 1000) {
		for (int i = 0; i < 10; ++i)
			delete sentence_list->takeItem(0);
	}
	sentence_list->addItem(raw_sentence);
}

void MainWindow::on_about()
{
	QCoreApplication * app = QCoreApplication::instance();
	QMessageBox::about(this, app->applicationName(), app->applicationName()
			+ ": example of Qt using marnav\n\nVersion: " + app->applicationVersion()
			+ "\n\nSee file: LICENSE");
}

void MainWindow::on_about_qt()
{
	QCoreApplication * app = QCoreApplication::instance();
	QMessageBox::aboutQt(this, app->applicationName());
}

void MainWindow::on_sentence_selection()
{
	auto items = sentence_list->selectedItems();
	if (items.empty())
		return;

	auto item = items.front();
	try {
		auto s = marnav::nmea::make_sentence(item->text().toStdString());
		sentence_desc->setText(QString{"Tag: %1\nTalker: %2\n\n%3\n"}
								   .arg(s->tag().c_str())
								   .arg(to_string(s->get_talker()).c_str())
								   .arg(get_details(s.get())));
	} catch (marnav::nmea::unknown_sentence &) {
		sentence_desc->setText("Unknown Sentence");
		item->setForeground(Qt::red);
	} catch (marnav::nmea::checksum_error &) {
		sentence_desc->setText("Checksum Error");
		item->setForeground(Qt::red);
	} catch (std::invalid_argument & error) {
		sentence_desc->setText("Error: " + QString::fromStdString(error.what()));
		item->setForeground(Qt::red);
	}
}

void MainWindow::on_open()
{
	action_open_port->setEnabled(false);
	action_close_port->setEnabled(true);
	action_open_file->setEnabled(false);
	cb_baudrate->setEnabled(false);
	port_name->setEnabled(false);

	port->setPortName(port_name->text());
	port->setBaudRate(cb_baudrate->currentText().toInt());
	port->setParity(QSerialPort::NoParity);
	port->setDataBits(QSerialPort::Data8);
	port->setStopBits(QSerialPort::OneStop);

	connect(port, &QSerialPort::readyRead, this, &MainWindow::on_data_ready);

	if (!port->open(QIODevice::ReadOnly)) {
		on_close();
		QMessageBox::critical(this, "Error", "Unable to open port: " + port->portName());
	}

	sentence_list->clear();
	sentence_desc->setText("");
}

void MainWindow::on_close()
{
	action_open_port->setEnabled(true);
	action_close_port->setEnabled(true);
	action_open_file->setEnabled(true);
	cb_baudrate->setEnabled(true);
	port_name->setEnabled(true);

	disconnect(port, &QSerialPort::readyRead, this, &MainWindow::on_data_ready);

	port->close();
}

void MainWindow::on_data_ready()
{
	while (true) {
		char raw;
		auto rc = port->read(&raw, sizeof(raw));
		if (rc == 0) {
			// no more data for now
			return;
		}
		if (rc < 0) {
			// an error has ocurred
			on_close();
			return;
		}

		switch (raw) {
			case '\r':
				break;
			case '\n':
				add_item(received_data.c_str());
				received_data.clear();
				break;
			default:
				if (received_data.size() > marnav::nmea::sentence::max_length) {
					// error ocurred, discard data
					received_data.clear();
				} else {
					received_data += raw;
				}
				break;
		}
	}
}
}
