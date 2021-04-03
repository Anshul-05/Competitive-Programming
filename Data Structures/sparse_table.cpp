class SparseTable {
	vector<int> A,lev;
	vector<vector<int>> dp;
	public:
	
	SparseTable(vector<int> &v) {
		A=v;
		int n=(int)A.size();
		lev.resize(n+1,0);
		for(int i=2;i<=n;++i) {
			lev[i]=lev[i/2]+1;
		}
		dp.pb(A);
		for(int j=1;(1<<j)<=n;++j) {
			dp.pb(vector<int>(n-(1<<j)+1));
			for(int i=0;i<(int)dp[j].size();++i) {
				dp[j][i]=merge(dp[j-1][i],dp[j-1][i+(1<<(j-1))]);
			}
		}
	}
	int query(int L,int R) {
		assert(L<=R);
		int d=lev[R-L+1];
		return merge(dp[d][L],dp[d][R-(1<<d)+1]);
	}
	int merge(int a,int b) {
		return min(a,b);
	}
};