#include "IsingMC.hpp"

#include <iostream>

#include <cmath>
#include <cstdlib>

IsingMC::IsingMC(unsigned M, unsigned N, double J, double beta)
	: M(M), N(N), J(J), beta(beta) {

	Lattice = new int[M];
	for (unsigned i = 0; i < M; i++) {
		Lattice[i] = new int[N];
	}

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

	unsigned pos = static_cast<unsigned>
		(floor (static_cast<double> (random()) / RAND_MAX * M * N));

	m = static_cast<unsigned> (floor (pos / N));
	n = pos - m * N;
}

double IsingMC::SpinEnergy(unsigned m, unsigned n) {

	double E = 0;
	for (int i = m - 1 ; i < m + 1; i += 2) {
		for (int j = n - 1; j < n + 1; j += 2) {

			if (i < 0) ii = M - 1;
			else if (i >= M - 1) ii = 0;
			else ii = i;

			if (j < 0) jj = N - 1;
			else if (j >= N - 1) jj = 0;
			else jj = j;

			E -= Lattice[ii][jj] * Lattice[m][n] * J;
		}
	}
	return E;
}

double IsingMC::Energy() {

	double E = 0;
	for (unsigned i = 0; i < M; i++) {
		for (unsigned j = 0; j < N; j++) {
			E += SpinEnergy(i, j);
		}
	}
	return E;
}

void IsingMC::Step() {

	unsigned i, j;
	RandomPoint(i, j);

	double E_1 = Energy();
	Lattice[i][j] = -Lattice[i][j];

	double E_2 = Energy();

	if (E_2 < E_1) return;

	if ()
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

