#include <iostream>
#include <QPainter>
#include "IsingWindow.hpp"

IsingWindow::IsingWindow(unsigned M, unsigned N, double J,
			 double beta, QWidget *parent) : QWidget(parent) {

	imc = new IsingMC(M, N, J, beta);
}

IsingWindow::~IsingWindow() {
	delete imc;
}

void IsingWindow::paintEvent(QPaintEvent *e) {

	Q_UNUSED(e);

	QPainter qp(this);
	unsigned PenSize = 0;

	imc->Step();

	QPen WhitePen(Qt::white, PenSize, Qt::SolidLine),
		BlackPen(Qt::black, PenSize, Qt::SolidLine);
	for (unsigned i = 0; i < imc->XSize(); i++) {
		for (unsigned j = 0; j < imc->YSize(); j++) {

			if (imc->GetSpin(i, j) == 1) {
				qp.setPen(WhitePen);
			} else 	qp.setPen(BlackPen);

			qp.drawPoint(i, j);
		}
	}
}
