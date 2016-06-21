#ifndef __MAINWINDOW__HPP__
#define __MAINWINDOW__HPP__

#include <QMainWindow>
#include <string>

class QAction;
class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QSerialPort;
class QListWidget;

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
	void on_sentence_selection();
	void on_open_file();

private:
	void create_actions();
	void create_menus();
	void setup_ui();
	void process_nmea();

	QAction * action_exit = nullptr;
	QAction * action_about = nullptr;
	QAction * action_about_qt = nullptr;
	QAction * action_open_port = nullptr;
	QAction * action_close_port = nullptr;
	QAction * action_open_file = nullptr;

	QLineEdit * port_name = nullptr;
	QComboBox * cb_baudrate = nullptr;
	QListWidget * sentence_list = nullptr;
	QLabel * sentence_desc = nullptr;

	QSerialPort * port = nullptr;

	std::string received_data;
};
}

#endif
