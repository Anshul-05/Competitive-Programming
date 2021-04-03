class Graph{
	public:
	int n,T,LG;
	vector<vector<int>> g,dp;
	vector<int> par,in,out,h;
	
	Graph(int _n) {
		n=_n;
		T=LG=0;
		g.resize(n);
		par=in=out=h=vector<int>(n,0);
	}
	
	void add(int u,int v) {
		g[u].push_back(v);
	}
	
	void dfs(int u,int pa=0) {
		in[u]=++T;
		par[u]=pa;
		for(int v:g[u]) {
			if(v==pa) continue;
			h[v]=h[u]+1;
			dfs(v,u);
		}
		out[u]=++T;
	}
	
	void LCA(int v) {
		dfs(v,v);
		LG=ceil(log2(n))+1;
		dp.resize(n);
		for(int u=0;u<n;++u) {
			dp[u].resize(LG,0);
			dp[u][0]=par[u];
		}
		for(int i=1;i<LG;++i)
			for(int u=0;u<n;++u)
				dp[u][i]=dp[dp[u][i-1]][i-1];
	}
	
	bool is_ancestor(int u,int v) {
		return in[u]<=in[v] and out[u]>=out[v];
	}
	
	int lca(int u,int v) {
		if(is_ancestor(u,v)) return u;
		if(is_ancestor(v,u)) return v;
		for(int i=LG-1;i>=0;--i) 
			if(!is_ancestor(dp[u][i],v))
				u=dp[u][i];
		return dp[u][0];
	}
	
};