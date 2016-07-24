#ifndef _ISINGMC_
#define _ISINGMC_

class IsingMC {

public:
	IsingMC(unsigned, unsigned, double, double);
	~IsingMC();
	double Energy();
	void Step();
	int GetSpin(unsigned, unsigned);
	unsigned XSize();
	unsigned YSize();

private:
	unsigned N, M;
	int **Lattice;
	double J, beta;


	void RandomPoint(unsigned&, unsigned&);
	double SpinEnergy(unsigned, unsigned);
	
};

#endif _ISINGMC_ 		// #ifndef _ISINGMC_
