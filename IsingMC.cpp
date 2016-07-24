#include "IsingMC.hpp"

#include <iostream>

#include <cmath>
#include <cstdlib>
#include <ctime>

IsingMC::IsingMC(unsigned M, unsigned N, double J, double beta)
	: M(M), N(N), J(J), beta(beta) {

	Lattice = new int * [M];
	for (unsigned i = 0; i < M; i++) {
		Lattice[i] = new int[N];
	}

	srandom(time(NULL));
	for (unsigned i = 0; i < M; i++) {
		for (unsigned j = 0; j < N; j++) {
			if (random() % 2 == 0) Lattice[i][j] = 1;
			else Lattice[i][j] = -1;
		}
	}
}

IsingMC::~IsingMC() {

	for (unsigned i = 0; i < M; i++) {
		delete[] Lattice[i];
	}
	delete[] Lattice;
	Lattice = NULL;
}

void IsingMC::RandomPoint(unsigned& m, unsigned& n) {

	// unsigned pos = static_cast<unsigned>
	// 	(floor (static_cast<double> (random()) / RAND_MAX * M * N));

	// m = static_cast<unsigned> (floor (pos / N));
	// n = pos - m * N;

	m = static_cast<unsigned>
		(floor (static_cast<double> (random()) / RAND_MAX * M));
	n = static_cast<unsigned>
		(floor (static_cast<double> (random()) / RAND_MAX * N));

}

double IsingMC::SpinEnergy(unsigned m, unsigned n) {

	double E = 0;
	for (int i = m - 1 ; i < m + 1; i += 2) {
		for (int j = n - 1; j < n + 1; j += 2) {

			unsigned ii = i, jj = j;
			if (i < 0) ii = M - 1;
			else if (i >= M - 1) ii = 0;

			if (j < 0) jj = N - 1;
			else if (j >= N - 1) jj = 0;

			E -= Lattice[ii][jj] * Lattice[m][n] * J;
		}
	}
	return E;
}

double IsingMC::SpinUHEnergy(unsigned m, unsigned n) {

	double E = 0;
	for (unsigned i = m; i <= m + 1; i++) {
		for (unsigned j = n; j <= n + 1; j++) {
			int ii = i > M - 1 ? 0 : i;
			int jj = j > N - 1 ? 0 : j;

			E -= Lattice[ii][jj] * Lattice[m][n] * J;
		}
	}
	return E;
}

double IsingMC::Energy() {

	double E = 0;
	for (unsigned i = 0; i < M; i++) {
		for (unsigned j = 0; j < N; j++) {
			E += SpinUHEnergy(i, j);
		}
	}
	return E;
}

double IsingMC::EnergyDiff(unsigned m, unsigned n) {

	double de = 0;

	return de;
}

void IsingMC::Step() {

	unsigned i, j;

	while (true) {
		RandomPoint(i, j);

		double de = EnergyDiff(i, j);
		if (de < 0
		    || ((static_cast<double> (random()) / RAND_MAX)
			< exp(-beta * de) ) ) {

			Lattice[i][j] = -Lattice[i][j];
			return;
		}
	}
}

int IsingMC::GetSpin(unsigned i, unsigned j) {
	return Lattice[i][j];
}

unsigned IsingMC::XSize() {
	return M;
}
unsigned IsingMC::YSize() {
	return N;
}

