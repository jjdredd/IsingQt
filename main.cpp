#include <QApplication>
#include "IsingWindow.hpp"

int main(int argc, char *argv[]) {

	QApplication app(argc, argv);
	IsingWindow iw(100, 100, 1.24, 1.2);

	iw.resize(260, 260);
	iw.setWindowTitle("2D Ising Monte-Carlo");
	iw.show();

	while (true) {
		iw.repaint();
		app.processEvents();
	}

	return 0;

}
