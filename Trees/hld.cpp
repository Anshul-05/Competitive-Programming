struct Node {
	// Node info
	int mx;
	Node() {
		mx=-inf;
	}	
	void Reset() {
		
	}
};
Node Merge(const Node& A,const Node& B) {
	// merge two Nodes
	Node C=A;
	if(B.mx>A.mx) C=B;
	return C;
}

class SegTree {
	int N;
	vector<Node> t;
	public:
	SegTree(){}
	
	SegTree(int n){
		N=n;
		t.assign(4*N+10,Node());
	}
	
	SegTree(vector<int> &A) {
		N=(int)A.size();
		t.assign(4*N+10,Node());
		Build(A,1,0,N-1);
	}
	
	void Build(vector<int> &a,int u,int s,int e) {
		if(s==e) {
			// leaf
			t[u].mx=a[s];
			return;
		}
		int mid=(s+e)>>1;
		Build(a,2*u,s,mid);
		Build(a,2*u+1,mid+1,e);
		t[u]=Merge(t[2*u],t[2*u+1]);
	}
	
	void Push(int u,int par) {
		// push info to child
		
	}
	
	void push(int u,int l,int r) {
		// update Node info
		return;
		
		if(l!=r) {
			Push(2*u,u);
			Push(2*u+1,u);
		}
		t[u].Reset();
	}
	
	void update(int l,int r,int x,int type=1) {
		update(1,0,N-1,l,r,x);
	}
	
	Node query(int l,int r) {
		return query(1,0,N-1,l,r);
	}
	
	void update(int u,int s,int e,int l,int r,int x) {
		if(e<l or r<s) return;
		if(l<=s and e<=r) {
			// update Node
			t[u].mx=x;
			return;
		}
		push(u,s,e);
		int mid=(s+e)>>1;
		update(2*u,s,mid,l,r,x);
		update(2*u+1,mid+1,e,l,r,x);
		push(2*u,s,mid);
		push(2*u+1,mid+1,e);
		t[u]=Merge(t[2*u],t[2*u+1]);
	}
	
	Node query(int u,int s,int e,int l,int r) {
		if(e<l or r<s) return Node(); 
		push(u,s,e);
		if(l<=s and e<=r) return t[u];
		int mid=(s+e)>>1;
		Node L=query(2*u,s,mid,l,r);
		Node R=query(2*u+1,mid+1,e,l,r);
		return Merge(L,R);
	}
};

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

class HeavyLight {
	public:
	vector<int> par,H,heavy,head,pos;
	SegTree tree;
	
	HeavyLight(const Graph& G,int root=0) {
		int n=G.n;
		par=H=head=pos=vector<int>(n,0);
		heavy.resize(n,-1);
		dfs(root,G);
		par[root]=-1;
		for(int i=0,cur=0;i<n;++i)
			if(par[i]<0 or heavy[par[i]]!=i)
				for(int j=i;j!=-1;j=heavy[j])
					head[j]=i,pos[j]=cur++;
		tree=SegTree(n);
	}
	
	int dfs(int u,const Graph& G) {
		int sz=1,mx=0;
		for(int v:G.g[u]) {
			if(v==par[u]) continue;
			par[v]=u,H[v]=H[u]+1;
			int now=dfs(v,G);
			sz+=now;
			if(now>mx) mx=now,heavy[u]=v;
		}
		return sz;
	}
	
	int query(int u,int v) {
		Node ans=Node();
		for(;head[u]!=head[v];v=par[head[v]]) {
			if(H[head[u]]>H[head[v]]) swap(u,v);
			Node now=tree.query(pos[head[v]],pos[v]);
			ans=Merge(ans,now);
		}
		if(H[u]>H[v]) swap(u,v);
		Node now=tree.query(pos[u],pos[v]);// pos[u]->lca
		ans=Merge(ans,now);
		return ans.mx;
	}
	
	void update(int u,int x) {
		tree.update(pos[u],pos[u],x);
	}
	// segtree V: V[pos[i]]=val[i]
};