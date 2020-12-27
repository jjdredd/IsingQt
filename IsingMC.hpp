#ifndef _ISINGMC_
#define _ISINGMC_

class IsingMC {

public:
	IsingMC(unsigned, unsigned, double, double);
	~IsingMC();
	double Energy();
	double Magnetization();
	void Step();
	int GetSpin(unsigned, unsigned);
	unsigned XSize();
	unsigned YSize();
	void SetJ(double);
	void SetBeta(double);

private:
	unsigned M, N;
	int **Lattice;
	double J, beta;

	void RandomPoint(unsigned&, unsigned&);
	double SpinEnergy(unsigned, unsigned);
	double EnergyDiff(unsigned, unsigned);
	double SpinUHEnergy(unsigned m, unsigned n);
	
};

#endif	// #ifndef _ISINGMC_
