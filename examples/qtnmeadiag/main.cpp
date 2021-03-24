#include "MainWindow.hpp"
#include <marnav/version.hpp>
#include <QApplication>
#include <QCommandLineParser>
#include <QFileInfo>

int main(int argc, char ** argv)
{
	QApplication app{argc, argv};
	app.setApplicationName("qtnmeadiag");
	app.setApplicationVersion(QString("%1.%2.%3")
								  .arg(marnav::version_major)
								  .arg(marnav::version_minor)
								  .arg(marnav::version_patch));

	QCommandLineParser parser;
	parser.setApplicationDescription("NMEA Browser and Diagnostics Tool");
	parser.addHelpOption();
	parser.addVersionOption();

	QCommandLineOption option_file{"file", "Reads file containing NMEA sentences", "file"};
	parser.addOption(option_file);

	parser.process(app);

	marnav_example::MainWindow win;
	if (parser.isSet(option_file))
		win.open_file(parser.value(option_file));
	win.show();
	return app.exec();
}
