class DSU {
	vector<int> p,sz;
	public:
	DSU(){}
	
	DSU(int n) {
		p=sz=vector<int>(n+1,0);
		for(int i=0;i<=n;++i) p[i]=i;
	}
	int find(int v) {
		return (v==p[v])?v:p[v]=find(p[v]);
	}
	bool join(int a,int b) {
		if((a=find(a))==(b=find(b))) return 0;
		if(sz[a]>sz[b]) swap(a,b);
		p[b]=a,sz[b]+=sz[a];
		return 1;
	}
};
