#include <iostream>
#include <QPainter>
#include "IsingWindow.hpp"

IsingWindow::IsingWindow(unsigned M, unsigned N, double J,
			 double beta, QWidget *parent) : QMainWindow(parent) {

	simwid = new IsingWidget(M, N, J, beta, parent);
	grid = new QGridLayout;

	setCentralWidget(new QWidget);

	lne_J = new QLineEdit( QString(std::to_string(J).c_str()) );
	lne_b = new QLineEdit( QString(std::to_string(beta).c_str()) );

	form = new QFormLayout;
	form->addRow("Jparam:", lne_J);
	form->addRow("bparam:", lne_b);

	connect(lne_J, SIGNAL (returnPressed()), this, SLOT (set_J()));
	connect(lne_b, SIGNAL (returnPressed()), this, SLOT (set_b()));

	grid->addLayout(form, 0, 1);
	grid->addWidget(simwid, 0, 0);

	centralWidget()->setLayout(grid);

}

IsingWindow::~IsingWindow() {
	delete lne_J;
	delete lne_b;
	delete form;
	delete simwid;
	delete grid;
}

void IsingWindow::set_J() {
	bool status;
	double val = lne_J->text().toDouble(&status);
	if (!status) return;
	simwid->SetJ(val);
	std::cout << "J is now set to: " << val << std::endl;
	
}

void IsingWindow::set_b() {
	bool status;
	double val = lne_b->text().toDouble(&status);
	if (!status) return;
	simwid->SetBeta(val);
	std::cout << "beta is now set to: " << val << std::endl;
}


//
// IsingWidget
// 

IsingWidget::IsingWidget (unsigned M, unsigned N, double J,
			  double beta, QWidget *parent)
	: running(false) {

	Q_UNUSED(parent);
	imc = new IsingMC(M, N, J, beta);
	setFixedWidth(M);
	setFixedHeight(N);

}

IsingWidget::~IsingWidget () {
	delete imc;
}

void IsingWidget::paintEvent (QPaintEvent *e) {

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

void IsingWidget::SetJ (double val) { imc->SetJ(val); }
void IsingWidget::SetBeta (double val) { imc->SetBeta(val); }
double IsingWidget::Energy () { return imc->Energy(val); }
double IsingWidget::Magnetization () { return imc->Magnetization(val); }

void IsingWidget::simulationThread(unsigned num) {
	while (true) {
		for (unsigned i = 0; i < num; i++) {
			mtx.lock();
			if (running) {
				imc->Step();
			}
			mtx.unlock();
		}
		emit paintEvent(0);
	}
}
