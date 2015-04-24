//----------------------------------------------------------------------------------------------------------------------
// By: Mohammad Saad Zaman
// ECE 358 Lab 1
// UW ID: 20432404
//----------------------------------------------------------------------------------------------------------------------

#include "Distribution.h"
#include <iostream>

#include "math.h"
#include "time.h"
#include <iterator>
using namespace std;
Distribution::Distribution(double i_lambda, int i_iter){
	lambda = i_lambda; 
	iter = i_iter;
	srand((int)time(NULL));
}
Distribution::Distribution(double i_lambda){
	lambda = i_lambda;
	iter = 100;			// default value
	srand((int)time(NULL));
}
void Distribution::generateRV(){
	for (int i = 0; i <= iter; i++){
		generatedValues.push_back(getExpRV());
	}
}
double Distribution::getExpRV(){
	return (((-1) / lambda)*log(1 - getRN()));
}
double Distribution::getRN(){
	return (((double)rand()) / ((double)RAND_MAX + 1));	
}

double Distribution::getMean(){
	double sum = 0;
	double counter = 0;
	for (std::vector<double>::iterator it = generatedValues.begin(); it != generatedValues.end(); it++){
		sum += *it;
		counter++;
	}
	return (sum / counter);
}

double Distribution::getVariance(){
	double mean = getMean();
	double variance = 0;
	double counter = 0;
	for (std::vector<double>::iterator it = generatedValues.begin(); it != generatedValues.end(); it++){
		variance += (*it - mean)*(*it - mean);
		counter++;
	}
	return (variance/counter);
}

std::vector<double> Distribution::getDistVector(){
	return generatedValues;
}

Distribution::~Distribution(){

}
