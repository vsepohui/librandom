#include <EXTERN.h>               /* From the Perl core */
#include <perl.h>                 /* From the Perl core */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static PerlInterpreter *my_perl;    /* The Perl interpreter */

static char *embedding[] = { "", "-e", " \
	use 5.022; \
	use warnings;  \
\
	sub random {\
		my $seed = shift;\
		my $num = shift;\
		my $r = Strong::Random->new($seed);\
		$r->srand($seed);\
		my $val = $r->rand($num);\
		return sprintf \"%0.42f %0.42f\", $r->{seed}, $val;\
	}\
\
	package Strong::Random; \
	use 5.022; use warnings; sub new {  my $class = shift;  my $seed  = shift;    my $self = bless {}, $class;    $self->srand($seed ? abs $seed : undef);    return $self; }   \
	sub _shuffle_seed { ... }\
	  sub _harmonic {  \
	  my $self = shift; \
	   my $x = $self->{seed}; \
	      state $half_freq = 2/7.0;\
			\
	         my $step = int ($x / $half_freq);\
	          $x -= $step * $half_freq; \
	          return ($step % 2 ? -1 : 1)*sqrt (1 - $x*$x); }  \
	    \
	  sub srand {  my $self = shift;  my $seed = shift // $self->_shuffle_seed();    while ($seed >= 100000000) {  $seed /= 2;  }    $self->{seed} = $seed; } \
	sub rand {  my $self = shift;  my $num = shift;  \
		my $r = ($self->_harmonic()+1)/2.0;\
		   $self->{seed} *= $r+1.5; \
		    $self->{seed} /= 2 if ($self->{seed} >= 100000000);   \
		    my $s = $r;  $s =~ s/\\.//;  $r *= substr($s, -5, -1) || 0; \
		    $r = substr($r, 0, 22);  $r =~ s/\\.//;  $r = '0.'. $r;  \
		     return $num ? int ($num * $r) : $r; \
	}  1;  \
			\
	\
	" };

double random2 (double *seed, unsigned num) {
	int argc = 0;
	
	char **argv;
	char **env;
	my_perl = perl_alloc();
	perl_construct(my_perl);


	perl_parse(my_perl, NULL, 3, embedding, NULL);
	perl_run(my_perl);

	dSP;

	ENTER;
	SAVETMPS;

	PUSHMARK(SP);
	EXTEND(SP, 2);
	
	char b1[1024], b2[1024];
	
	sprintf(b1, "%0.42lf", *seed);
	sprintf(b2, "%d", num);

	PUSHs(sv_2mortal(newSVpv(b1, (int)strlen(b1))));
	PUSHs(sv_2mortal(newSVpv(b2, (int)strlen(b2))));

	PUTBACK;

	// Call Perl method
	call_pv("random", G_SCALAR); 
	SPAGAIN;

	STRLEN len1;
	SV *sv1 = POPs;
	char *s1 = SvPVx(sv1, len1);
	
	double r;

	char *rs1 = malloc(sizeof(char)*len1+1);
	memcpy(rs1, s1, sizeof(char)*len1);
	rs1[len1] = (char)0;
	
	sscanf(rs1, "%lf %lf", seed, &r);

	
	PUTBACK;
	FREETMPS;
	LEAVE;    

	perl_destruct(my_perl);
	perl_free(my_perl);
	//PERL_SYS_TERM();

	return r;
}




