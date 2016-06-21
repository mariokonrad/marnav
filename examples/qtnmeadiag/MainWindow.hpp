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

	QMenu * menu_file = nullptr;
	QMenu * menu_help = nullptr;
	QAction * action_exit = nullptr;
	QAction * action_about = nullptr;
	QAction * action_about_qt = nullptr;

	QPushButton * btn_open = nullptr;
	QPushButton * btn_close = nullptr;
	QLineEdit * port_name = nullptr;
	QComboBox * cb_baudrate = nullptr;
	QPlainTextEdit * text = nullptr;

	QSerialPort * port = nullptr;

	std::string received_data;
};
}

#endif
