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
#include <thread>
#include <mutex>

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

public slots:
	void set_J();
	void set_b();

};

// need new widget for ising window
// with seperate computation thread

class IsingWidget : public QWidget {

	Q_OBJECT;

public:
	IsingWidget(unsigned, unsigned, double, double, QWidget *parent = 0);
	~IsingWidget();
	void SetJ(double);
	void SetBeta(double);
	double Energy();
	double Magnetization();

protected:
	void paintEvent(QPaintEvent *e);
	void simulationThread(unsigned);

private:
	IsingMC *imc;
	std::mutex mtx;
	bool running;

};


#endif	// #ifndef _ISING_WINDOW_
