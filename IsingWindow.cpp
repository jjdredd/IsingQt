#include <iostream>
#include "IsingWindow.hpp"

IsingWindow::IsingWindow(unsigned M, unsigned N, double J,
			 double beta, QWidget *parent)
	: QMainWindow(parent) {

	l_mag = new QLabel(this);
	l_e = new QLabel(this);
	simwid = new IsingWidget(M, N, J, beta, parent);
	grid = new QGridLayout;

	setCentralWidget(new QWidget);

	l_mag->setText("Magnetization:");
	l_e->setText("Energy:");

	connect(simwid, SIGNAL(GetMagnetization(const QString &)),
		l_mag, SLOT(setText(const QString &)) );

	connect(simwid, SIGNAL(GetEnergy(const QString &)),
		l_e, SLOT(setText(const QString &)) );

	lne_J = new QLineEdit( QString(std::to_string(J).c_str()) );
	lne_b = new QLineEdit( QString(std::to_string(beta).c_str()) );

	form = new QFormLayout;
	form->addRow("J :", lne_J);
	form->addRow("1/T :", lne_b);

	connect(lne_J, SIGNAL (returnPressed()), this, SLOT (set_J()) );
	connect(lne_b, SIGNAL (returnPressed()), this, SLOT (set_b()) );

	btn_start = new QPushButton("Start", this);
	btn_start->setCheckable(true);
	connect(btn_start, SIGNAL (toggled(bool)), this, SLOT (toggle_simulation(bool)) );

	grid->addLayout(form, 0, 2);
	grid->addWidget(simwid, 0, 0, 2, 2);
	grid->addWidget(l_mag, 1, 2);
	grid->addWidget(l_e, 2, 2);
	grid->addWidget(btn_start, 3, 2);

	centralWidget()->setLayout(grid);

}

IsingWindow::~IsingWindow() {
	toggle_simulation(false); // XXX FIXME (data races)
	delete l_mag;
	delete l_e;
	delete lne_J;
	delete lne_b;
	delete btn_start;
	delete form;
	delete simwid;
	delete grid;
}

void IsingWindow::set_J() {
	bool status;
	double val = lne_J->text().toDouble(&status);
	if (!status) return;
	simwid->SetJ(val);
}

void IsingWindow::set_b() {
	bool status;
	double val = lne_b->text().toDouble(&status);
	if (!status) return;
	simwid->SetBeta(val);
}

void IsingWindow::toggle_simulation(bool sstate) {
	if (sstate) { btn_start->setText("Stop"); }
	else { btn_start->setText("Start"); }
	simwid->ToggleSimulation(sstate);
}


//
// IsingWidget
// 

IsingWidget::IsingWidget (unsigned M, unsigned N, double J,
			  double beta, QWidget *parent)
	: running(false) {

	Q_UNUSED(parent);
	
	iterations = 100;
	imc = new IsingMC(M, N, J, beta);
	setFixedWidth(M);
	setFixedHeight(N);

	render_timer = new QTimer(this);
	text_timer = new QTimer(this);
	connect(render_timer, SIGNAL (timeout()), this, SLOT (update()) );
	connect(text_timer, SIGNAL (timeout()), this, SLOT (OutputTextData()) );
	render_timer->start(10);
	text_timer->start(500);

}

IsingWidget::~IsingWidget () {
	delete imc;
	delete render_timer;
}

void IsingWidget::paintEvent (QPaintEvent *e) {

	Q_UNUSED(e);

	QPainter qp(this);
	unsigned PenSize = 1;
	unsigned offset = PenSize ? PenSize : 1;

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
double IsingWidget::Energy () { return imc->Energy(); }
double IsingWidget::Magnetization () { return imc->Magnetization(); }

void IsingWidget::simulationThread(unsigned num) {
	while (running) {
		for (unsigned i = 0; i < num; i++) {
			imc->Step();
		}
	}
}

void IsingWidget::ToggleSimulation(bool sstate) {
	if (sstate) { startSimulation(); }
	else { stopSimulation(); }
}

void IsingWidget::startSimulation() {
	if (running) return;
	std::thread(&IsingWidget::simulationThread, this, iterations).detach();
	running = true;
}

void IsingWidget::stopSimulation() {
	running = false;
}


void IsingWidget::OutputTextData() {

	QString magnet("Magnetization: ");
	QString energy("Energy: ");

	magnet += QString::number(Magnetization());
	energy += QString::number(Energy());

	emit GetMagnetization(magnet);
	emit GetEnergy(energy);
}
