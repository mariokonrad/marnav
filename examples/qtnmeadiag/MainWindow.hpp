#ifndef __MAINWINDOW__HPP__
#define __MAINWINDOW__HPP__

#include <QMainWindow>
#include <string>

class QMenu;
class QAction;
class QLineEdit;
class QPlainTextEdit;
class QPushButton;
class QSerialPort;
class QComboBox;

namespace marnav_example
{

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();
	virtual ~MainWindow();

private slots:
	void on_about();
	void on_about_qt();
	void on_open();
	void on_close();
	void on_data_ready();

private:
	void create_actions();
	void create_menus();
	void setup_ui();
	void process_nmea();

	QMenu * menu_file;
	QMenu * menu_help;
	QAction * action_exit;
	QAction * action_about;
	QAction * action_about_qt;

	QPushButton * btn_open;
	QPushButton * btn_close;
	QLineEdit * port_name;
	QComboBox * cb_baudrate;
	QPlainTextEdit * text;

	QSerialPort * port;

	std::string received_data;
};

}

#endif
