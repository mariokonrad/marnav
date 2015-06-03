#include <QApplication>
#include "MainWindow.hpp"
#include <marnav/version.hpp>

int main(int argc, char ** argv)
{
	QApplication app{argc, argv};
	app.setApplicationName("qtnmeadiag");
	app.setApplicationVersion(QString("%1.%2.%3")
								  .arg(marnav::version_major)
								  .arg(marnav::version_minor)
								  .arg(marnav::version_patch));
	MainWindow win;
	win.show();
	return app.exec();
}
