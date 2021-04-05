class matching {
	public:
	vector<vector<int>> G;
	vector<int> pa,pb,was;
	int n,m,res,t;
	
	matching(int n,int m) : n(n), m(m) {
		pa=vector<int>(n+1,-1);
		pb=vector<int>(m+1,-1);
		was=vector<int>(n+1,0);
		G.resize(n+1);
		res=t=0;
	}
	
	void add(int u,int v) {
		G[u].push_back(v);
	}
	
	bool dfs(int u) {
		was[u]=t;
		for(int v:G[u])
			if(pb[v]<0) {
				pb[v]=u,pa[u]=v;
				return true;
			}
		for(int v:G[u]) 
			if(was[pb[v]]!=t and dfs(pb[v])) {
				pb[v]=u,pa[u]=v;
				return true;
			}
		return false;
	}
	
	int solve() {
		while(true) {
			t++;
			int add=0;
			for(int i=0;i<n;++i) 
				if(pa[i]<0 and dfs(i)) ++add;
			if(!add) break;
			res+=add;
		}
		return res;
	}
	bool run_one(int u) {
		if(pa[u]<0) return 0;
		t++;
		return dfs(u);
	}
};
