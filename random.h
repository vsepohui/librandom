class Random {
	public: 
		Random(double seed);
		double rand(unsigned num);
		
	private:
		double seed;
		
		double _harmonic();
};
