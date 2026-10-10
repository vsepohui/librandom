/*	package Strong::Random; \

	 
	sub rand {  my $self = shift;  my $num = shift;  \
		my $r = ($self->_harmonic()+1)/2.0;\
		   $self->{seed} *= $r+1.5; \
		    $self->{seed} /= 2 if ($self->{seed} >= 100000000);   \
		    my $s = $r;  $s =~ s/\\.//;  $r *= substr($s, -5, -1) || 0; \
		    $r = substr($r, 0, 22);  $r =~ s/\\.//;  $r = '0.'. $r;  \
		     return $num ? int ($num * $r) : $r; \
	}  1;  \
*/

#include <math.h>
#include <string>
#include "random.h"

Random::Random(double seed) {
	this->seed = seed;
}

std::string drop_dot (std::string s) {
	int pos = s.find(".");
	return std::string(s.substr(0, pos - 1) + s.substr(pos + 1, s.length() - 1));
}

double Random::rand (unsigned num){
	double r = (this->_harmonic()+1.0)/2.0 + 1.5;
	
		
	this->seed *= r;
	
	while (this->seed >= 100000000) {
			this->seed /= 10.0;
	}
	
	char buff [1024];
	sprintf(buff, "%0.42g", r);
	std::string s(buff);
	
	
	std::string s2 = drop_dot(s);
	    
    r *= atoi( s2.substr(s2.length() > 5 ? s2.length()-6 : 0, s2.length()-1).c_str() );
    
//    printf("%d\n", atoi( s2.substr(s2.length() > 5 ? s2.length()-6 : 0, s2.length()-1).c_str() ));
	

    s2 = std::to_string(r);

	char buff2 [1024];
	sprintf(buff2, "%0.42g", r);
	std::string s3(buff2);
    
    s3 = s3.substr(0, 22);
   
	s3 = drop_dot(s3);
	s3 = std::string("0.") + s3;

	r = atof(s3.c_str());
	 
	return num ? (int) (num * r) : r;
}

double Random::_harmonic() {
	double x = this->seed;
	static double half_freq = 2.0/7.0;
	
	long step = (long) (x / half_freq);
	x -= step * half_freq;

	return (step % 2 ? -1 : 1)*sqrt (1 - x*x);
}
