class Random {
	public: 
		Random(double seed);
		Random();
		double rand(unsigned num);
		
	private:
		double seed;
		double _harmonic();
		double _get_new_seed();
};
