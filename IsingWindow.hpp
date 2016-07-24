#ifndef _ISING_WINDOW_
#define _ISING_WINDOW_

#include <QWidget>

#include "IsingMC.hpp"

class IsingWindow : public QWidget {

public:
	IsingWindow(unsigned, unsigned, double, double, QWidget *parent = 0);
	~IsingWindow();

protected:
	void paintEvent(QPaintEvent *e);

private:
	IsingMC *imc;

};


#endif	// #ifndef _ISING_WINDOW_
