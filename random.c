#include <EXTERN.h>               /* From the Perl core */
#include <perl.h>                 /* From the Perl core */

static PerlInterpreter *my_perl;    /* The Perl interpreter */

static char *embedding[] = { "", "-e", " \
	use 5.022; \
	use warnings;  \
\
	sub random {\
		my $seed = shift;\
		my $num = shift;\
		my $r = Strong::Random->new($seed);\
		my $val = $r->rand($num);\
		return ($r->{seed}, $val);\
	}\
\
	package Strong::Random; \
	use 5.022; use warnings; sub new {  my $class = shift;  my $seed  = shift;    my $self = bless {}, $class;    $self->srand($seed ? abs $seed : undef);    return $self; }   \
	sub _shuffle_seed { ... }\
	  sub _harmonic {  my $self = shift;  my $x = $self->{seed};    state $half_freq = 2/7.0;   my $step = int ($x / $half_freq); $x -= $step * $half_freq; return ($step % 2 ? -1 : 1)*sqrt (1 - $x*$x); }  \
	  sub srand {  my $self = shift;  my $seed = shift // $self->_shuffle_seed();    while ($seed >= 100000000) {  $seed /= 2;  }    $self->{seed} = $seed; } \
	sub rand {  my $self = shift;  my $num = shift;    my $r = ($self->_harmonic()+1)/2.0;   $self->{seed} *= $r+1.5;  $self->{seed} /= 2 if ($self->{seed} >= 100000000);   my $s = $r;  $s =~ s/\\.//;  $r *= substr($s, -5, -1) || 0;  $r = substr($r, 0, 22);  $r =~ s/\\.//;  $r = '0.'. $r;   return $num ? int $num * $r : $r; }  1;  \
			\
	\
	" };

struct crypter_result random (float &seed, unsigned num) {
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
	PUSHs(sv_2mortal(newSVnv(seed)));
	PUSHs(sv_2mortal(newSViv(num)));
	PUTBACK;

	// Call Perl method
	call_pv("random", G_SCALAR); 
	SPAGAIN;

	STRLEN len;
	seed = POPn;
	float r = POPn;

	PUTBACK;
	FREETMPS;
	LEAVE;    

	perl_destruct(my_perl);
	perl_free(my_perl);
	//PERL_SYS_TERM();

	return r;
}




