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

#include "IsingMC.hpp"

class IsingWindow : public QMainWindow {

	Q_OBJECT;

public:
	IsingWindow(unsigned, unsigned, double, double, QWidget *parent = 0);
	~IsingWindow();

protected:
	void paintEvent(QPaintEvent *e);

private:
	IsingMC *imc;
	QFormLayout *form;
	QLineEdit *lne_J, *lne_b;
	QGridLayout *grid;
	QWidget *testsim;

public slots:
	void le_set_J();
	void le_set_b();

};

// need new widget for ising window
// with seperate computation thread


#endif	// #ifndef _ISING_WINDOW_
