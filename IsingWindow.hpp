#ifndef _ISING_WINDOW_
#define _ISING_WINDOW_

#include <QMainWindow>
#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QPainter>
#include <QHBoxLayout>
#include <QString>
#include <QGridLayout>
#include <QPushButton>
#include <QTimer>
#include <QLabel>
#include <thread>

#include "IsingMC.hpp"

class IsingWidget;

class IsingWindow : public QMainWindow {

	Q_OBJECT;

public:
	IsingWindow(unsigned, unsigned, double, double, QWidget *parent = 0);
	~IsingWindow();

private:

	QFormLayout *form;
	QLineEdit *lne_J, *lne_b;
	QGridLayout *grid;
	IsingWidget *simwid;
	QPushButton *btn_start;
	QLabel *l_mag, *l_e;

public slots:
	void set_J();
	void set_b();
	void toggle_simulation(bool);

};

// need new widget for ising window
// with seperate computation thread
//
// add start, stop and randomize functionality

class IsingWidget : public QWidget {

	Q_OBJECT;

public:
	IsingWidget(unsigned, unsigned, double, double, QWidget *parent = 0);
	~IsingWidget();
	void SetJ(double);
	void SetBeta(double);
	double Energy();
	double Magnetization();
	void ToggleSimulation(bool);

signals:
	void GetMagnetization(const QString &);
	void GetEnergy(const QString &);

public slots:
	void OutputTextData();

protected:
	void paintEvent(QPaintEvent *e);
	void simulationThread(unsigned);
	void startSimulation();
	void stopSimulation();

private:
	IsingMC *imc;
	bool running;
	unsigned iterations;
	QTimer *render_timer, *text_timer;

};


#endif	// #ifndef _ISING_WINDOW_
