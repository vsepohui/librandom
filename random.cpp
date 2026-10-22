#include <math.h>
#include <string>
#include <chrono>
#include "random.h"


std::string drop_dot (std::string s) {
	int pos = s.find(".");
	return std::string(s.substr(0, pos) + s.substr(pos + 1, s.length() - 1));
}

Random::Random(double seed) {
	this->seed = seed;
}

Random::Random() {
	this->seed = this->_get_new_seed();
}

double Random::get_seed () {
	return this->seed;
}

double Random::rand (){
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
	 
	return r;
}


unsigned Random::rand (unsigned num){
	double r = this->rand();
	return (unsigned) (num * r);
}


double Random::_get_new_seed () {
	std::chrono::time_point< std::chrono::system_clock > now = std::chrono::system_clock::now();
	auto duration = now.time_since_epoch();

	auto milliseconds = std::chrono::duration_cast< std::chrono::milliseconds >( duration );
	duration -= milliseconds;

	auto microseconds = std::chrono::duration_cast< std::chrono::microseconds >( duration );
	duration -= microseconds;

	auto nanoseconds = std::chrono::duration_cast< std::chrono::nanoseconds >( duration );

	char buff3[255];
	sprintf(buff3, "%d%d%d", milliseconds.count(), microseconds.count(), nanoseconds.count());
	int ms = abs(atoi(buff3));
  
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	
	char buff[255], buff2[255];
	sprintf(buff, "%d", static_cast<long int> (now_c));
	sprintf(buff2, "%d", ms);
	
	return atof((std::string(buff)+ "."+ std::string(buff2)).c_str());
}

double Random::_harmonic() {
	double x = this->seed;
	static double half_freq = 2.0/7.0;
	
	long step = (long) (x / half_freq);
	x -= step * half_freq;

	return (step % 2 ? -1 : 1)*sqrt (1 - x*x);
}
