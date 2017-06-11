#include <QApplication>
#include "IsingWindow.hpp"

int main(int argc, char *argv[]) {

	unsigned NX = 300;
	unsigned NY = 300;

	QApplication app(argc, argv);
	IsingWindow iw(NX, NY, 1.24, 1.2);

	// iw.resize(NX, NY);
	iw.setWindowTitle("2D Ising Monte-Carlo");
	iw.show();

	while (true) {
		iw.repaint();
		app.processEvents();
	}

	return 0;

}
