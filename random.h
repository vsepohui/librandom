class Random {
	public: 
		Random(double seed);
		Random();
		unsigned rand(unsigned num);
		double rand ();
		double get_seed();
	private:
		double seed;
		double _harmonic();
		double _get_new_seed();
};
