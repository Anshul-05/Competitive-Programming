struct BIT {
	vector<int> bit;
	int MAX;
	public:
	BIT(){}
	
	BIT(int n) {
		MAX=n+10;
		bit.resize(MAX,0);
	}
	
	void up(int x,int val) {
		++x;
		while(x<MAX) bit[x]+=val,x+=x&(-x);
	}
	int get(int x) {
		++x;
		int ans=0;
		while(x) ans+=bit[x],x-=x&(-x);
		return ans;
	}
};
