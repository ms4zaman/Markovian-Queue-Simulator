// Distribution.h
#include <iostream>
#include <vector>

class Distribution{
public:
	Distribution(double i_lambda, int i_iter);
	Distribution(double i_lambda);
	~Distribution();

	double getRN();
	double getExpRV();
	double getMean();
	double getVariance();

	void generateRV();
	void printRV();
	std::vector<double> getDistVector();

private:
	double lambda;
	int iter;

protected:
	std::vector<double> generatedValues;

};

