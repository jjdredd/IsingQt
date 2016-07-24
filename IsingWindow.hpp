#ifndef _ISING_WINDOW_
#define _ISING_WINDOW_

#include <Qwidget>

#include "IsingMC"

class IsingWindow : public QWidget {

public:
	IsingWindow(unsigned, unsigned, double, double, QWidget *parent = 0);
	~IsingWindow();

protected:
	void paintEvent(QPaintEvent *e);

private:
	IsingMC *imc;

};


#endif _ISING_WINDOW_		// #ifndef _ISING_WINDOW_
