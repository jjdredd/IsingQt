#include <QApplication>
#include <QString>
#include "IsingWindow.hpp"

int main(int argc, char *argv[]) {

	unsigned NX = 500;
	unsigned NY = 500;

	QApplication app(argc, argv);
	IsingWindow iw(NX, NY, 1.14, 0.5);

	// iw.resize(NX, NY);
	iw.setWindowTitle("2D Ising Monte-Carlo");
	iw.show();

	// need to run ising simulaiton in a separate thread

	return app.exec();

	while (true) {
		app.processEvents();
	}

	return 0;

}
