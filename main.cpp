#include "IsingWindow.hpp"

int main(int argc, char *argv[]) {

	QApplication app(argc, argv);
	IsingWindow iw;

	iw.resize(280, 270);
	iw.setIwTitle("2D Ising Monte-Carlo");
	iw.show();

	return app.exec();

}
