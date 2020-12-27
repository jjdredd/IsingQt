#include <iostream>
#include <QPainter>
#include "IsingWindow.hpp"

IsingWindow::IsingWindow(unsigned M, unsigned N, double J,
			 double beta, QWidget *parent) : QMainWindow(parent) {

	imc = new IsingMC(M, N, J, beta);

	setCentralWidget(new QWidget);

	lne_J = new QLineEdit( QString(std::to_string(J).c_str()) );
	lne_b = new QLineEdit( QString(std::to_string(beta).c_str()) );

	form = new QFormLayout;
	form->addRow("Jparam:", lne_J);
	form->addRow("bparam:", lne_b);

	connect(lne_J, SIGNAL(returnPressed()), this, SLOT (le_set_J()));
	connect(lne_b, SIGNAL (returnPressed()), this, SLOT (le_set_b()));

	centralWidget()->setLayout(form);

}

IsingWindow::~IsingWindow() {
	delete imc;
	delete form;
	delete lne_J;
	delete lne_b;
}

void IsingWindow::le_set_J() {
	bool status;
	double val = lne_J->text().toDouble(&status);
	if (!status) return;
	imc->SetJ(val);
	std::cout << "J is now set to: " << val << std::endl;
	
}

void IsingWindow::le_set_b() {
	bool status;
	double val = lne_b->text().toDouble(&status);
	if (!status) return;
	imc->SetBeta(val);
	std::cout << "beta is now set to: " << val << std::endl;
}

void IsingWindow::paintEvent(QPaintEvent *e) {

	Q_UNUSED(e);
	return;

	QPainter qp(this);
	unsigned PenSize = 2;
	unsigned offset = PenSize ? PenSize : 1;

	for (unsigned i = 0; i < 100 // imc->XSize() * imc->YSize()
		     ;i++) imc->Step();
	// std::cout << imc->Energy() << std::endl;

	// std::cout << "Energy: " << imc->Energy()
	// 	  << " Magnetization: " << imc->Magnetization()
	// 	  << std::endl;

	QPen WhitePen(Qt::white, PenSize, Qt::SolidLine),
		BlackPen(Qt::black, PenSize, Qt::SolidLine);
	for (unsigned i = 0; i < imc->XSize(); i++) {
		for (unsigned j = 0; j < imc->YSize(); j++) {

			if (imc->GetSpin(i, j) == 1) {
				qp.setPen(WhitePen);
			} else 	qp.setPen(BlackPen);

			qp.drawPoint(offset * i, offset * j);
		}
	}
}
