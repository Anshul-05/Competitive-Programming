class cd{
	double a,b;
	public:
	cd(){a=b=0;}
	cd(int _a){a=_a,b=0;}
	cd(double _a,double _b) {
		a=_a,b=_b;
	}
	double real(){return a;}
	double imag(){return b;}
	void operator+=(cd& X) {
		a+=X.a,b+=X.b;
	}
	void operator*=(cd& X) {
		double _a=a,_b=b;
		a=_a*X.a-_b*X.b,b=_b*X.a+_a*X.b;
	}
	void operator/=(int n) {
		a/=(double)n,b/=(double)n;
	}
	cd operator*(cd& X) {
		return cd(a*X.a-b*X.b,b*X.a+a*X.b);
	}
	cd operator+(cd& X) {
		return cd(a+X.a,b+X.b);
	}
	cd operator-(cd& X) {
		return cd(a-X.a,b-X.b);
	}
};
