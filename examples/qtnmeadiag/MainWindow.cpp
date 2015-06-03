#include "MainWindow.hpp"
#include <QMenuBar>
#include <QToolBar>
#include <QMessageBox>
#include <QCoreApplication>
#include <QPlainTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSerialPort>
#include <marnav/nmea/nmea.hpp>

MainWindow::MainWindow()
	: menu_file(nullptr)
	, menu_help(nullptr)
	, action_exit(nullptr)
	, action_about(nullptr)
	, action_about_qt(nullptr)
	, btn_open(nullptr)
	, btn_close(nullptr)
	, port_name(nullptr)
	, text(nullptr)
	, port(nullptr)
{
	setWindowTitle(tr("qtnmeadiag"));

	create_actions();
	create_menus();
	setup_ui();

	port = new QSerialPort(this);
}

MainWindow::~MainWindow() { on_close(); }

void MainWindow::create_menus()
{
	menu_file = menuBar()->addMenu(tr("&File"));
	menu_file->addAction(action_exit);

	menu_help = menuBar()->addMenu(tr("&Help"));
	menu_help->addAction(action_about);
	menu_help->addAction(action_about_qt);
}

void MainWindow::create_actions()
{
	action_exit = new QAction(tr("E&xit"), this);
	action_exit->setStatusTip(tr("Quits the application"));
	action_exit->setShortcut(tr("Ctrl+Q"));
	connect(action_exit, SIGNAL(triggered()), this, SLOT(close()));

	action_about = new QAction(tr("About ..."), this);
	action_about->setStatusTip(tr("Shows the About dialog"));
	connect(action_about, SIGNAL(triggered()), this, SLOT(on_about()));

	action_about_qt = new QAction(tr("About Qt ..."), this);
	action_about_qt->setStatusTip(tr("Shows information about Qt"));
	connect(action_about_qt, SIGNAL(triggered()), this, SLOT(on_about_qt()));
}

void MainWindow::setup_ui()
{
	QWidget * center = new QWidget(this);

	text = new QPlainTextEdit(center);
	text->setReadOnly(true);

	port_name = new QLineEdit(center);
	port_name->setText("/dev/ttyUSB0");
	btn_open = new QPushButton(tr("Open"), center);
	connect(btn_open, SIGNAL(pressed()), this, SLOT(on_open()));
	btn_close = new QPushButton(tr("Close"), center);
	connect(btn_close, SIGNAL(pressed()), this, SLOT(on_close()));
	btn_close->setEnabled(false);

	QGridLayout * layout = new QGridLayout;
	layout->addWidget(port_name, 0, 0);
	layout->addWidget(btn_open, 0, 1);
	layout->addWidget(btn_close, 0, 2);
	layout->addWidget(text, 1, 0, 1, 3);

	center->setLayout(layout);
	setCentralWidget(center);
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

void MainWindow::on_open()
{
	btn_open->setEnabled(false);
	btn_close->setEnabled(true);

	port->setPortName(port_name->text());
	port->setBaudRate(QSerialPort::Baud4800);
	port->setParity(QSerialPort::NoParity);
	port->setDataBits(QSerialPort::Data8);
	port->setStopBits(QSerialPort::OneStop);

	connect(port, SIGNAL(readyRead()), this, SLOT(on_data_ready()));

	if (!port->open(QIODevice::ReadOnly)) {
		on_close();
		QMessageBox::critical(this, "Error", "Unable to open port");
	}
}

void MainWindow::on_close()
{
	btn_open->setEnabled(true);
	btn_close->setEnabled(false);

	disconnect(port, SIGNAL(readyRead()), this, SLOT(on_data_ready()));

	port->close();
}

void MainWindow::process_nmea()
{
	try {
		auto sentence = marnav::nmea::make_sentence(received_data);

		// sentence is ok, for now: just show the received data
		text->appendPlainText(received_data.c_str());

		// TODO: prevent text from growing too large, remove some lines
		// TODO: print sentence specific data
	} catch (...) {
		// ignore
	}
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
				process_nmea();
				received_data.clear();
				break;
			default:
				if (received_data.size() > marnav::nmea::sentence::MAX_LENGTH) {
					// error ocurred, discard data
					received_data.clear();
				} else {
					received_data += raw;
				}
				break;
		}
	}
}

