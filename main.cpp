#include <QApplication>
#include <QString>
#include "IsingWindow.hpp"

int main(int argc, char *argv[]) {

	unsigned NX = 200;
	unsigned NY = 200;

	QApplication app(argc, argv);
	IsingWindow iw(NX, NY, 1.14, 0.1);

	// iw.resize(NX, NY);
	iw.setWindowTitle("2D Ising Monte-Carlo");
	iw.show();

	while (true) {
		iw.repaint();
		app.processEvents();
	}

	return 0;

}
