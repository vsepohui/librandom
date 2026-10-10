#include <math.h>
#include <string>
#include "random.h"


std::string drop_dot (std::string s) {
	int pos = s.find(".");
	return std::string(s.substr(0, pos) + s.substr(pos + 1, s.length() - 1));
}

Random::Random(double seed) {
	this->seed = seed;
}

double Random::rand (unsigned num){
	double r = (this->_harmonic()+1.0)/2.0+1.5;
	
	this->seed *= r;
	
	while (this->seed >= 100000000) {
			this->seed /= 2.0;
	}
	
	char buff [1024];
	sprintf(buff, "%0.42g", r);
	std::string s(buff);
	
	
	s = drop_dot(s);
    r *= atoi( s.substr(s.length() > 4 ? s.length()-5 : 0, s.length()).c_str() );
    
	char buff2 [1024];
	sprintf(buff2, "%0.42g", r);
	std::string r2(buff2);
    
    r2 = r2.substr(0, r2.length() < 22 ? r2.length() : 22);
   
	r2 = drop_dot(r2);
	r2 = std::string("0.") + r2;

	r = atof(r2.c_str());
	 
	return num ? (int) (num * r) : r;
}

double Random::_harmonic() {
	double x = this->seed;
	static double half_freq = 2.0/7.0;
	
	long step = (long) (x / half_freq);
	x -= step * half_freq;

	return (step % 2 ? -1 : 1)*sqrt (1 - x*x);
}
