struct dsu_save{
	int u,v,szu,szv;
	dsu_save(){}
	dsu_save(int _u,int _szu,int _v,int _szv){
		u=_u,v=_v,szu=_szu,szv=_szv;
	}
};
struct dsu_RB{
	vector<int> p,sz;
	int comp;
	stack<dsu_save>st;
	dsu_RB(){}
	dsu_RB(int n){
		p.resize(n+1),sz.resize(n+1);
		for(int i=0;i<=n;++i) p[i]=i,sz[i]=1;
		comp=n;
	}
	int find(int v){
		return (v==p[v])?v:p[v]=find(p[v]);
	}
	bool join(int a,int b){
		a=find(a),b=find(b);
		if(a==b)return 0;
		comp--;
		if(sz[b]>sz[a]) swap(a,b);
		st.push(dsu_save(a,sz[a],b,sz[b]));
		p[b]=a,sz[a]+=sz[b];
		return 1;
	}
	void RB(){
		if(st.empty())return;
		dsu_save to=st.top(); st.pop();
		comp++,p[to.u]=to.u,p[to.v]=to.v;
		sz[to.u]=to.szu,sz[to.v]=to.szv;
	}
};
struct query{
	int u,v;
	bool ok;
	query(int _u,int _v){
		u=_u,v=_v;
	}
};
struct tree{
	vector< vector<query> > Q;
	dsu_RB dsu;
	int T;
	tree(){}
	tree(int _T,int n){
		T=_T+5,Q.resize(4*T+10);
		dsu=dsu_RB(n);
	}
	void _add(int u,int s,int e,int l,int r,query &q){
		if(e<l or r<s)return;
		if(l<=s and e<=r){
			Q[u].pb(q);
			return;
		}
		int mid=(s+e)>>1;
		_add(2*u,s,mid,l,r,q);
		_add(2*u+1,mid+1,e,l,r,q);
	}
	void add(int u,int v,int l,int r){ // add u-v edge to [L,R]
		query q(u,v);
		_add(1,0,T-1,l,r,q);
	}
	void dfs(int u,int s,int e,vector<int>& ans){
		for(auto& q:Q[u]) q.ok=dsu.join(q.u,q.v);
		if(s==e){
			ans[s]=dsu.comp;
		} else {
			int mid=(s+e)>>1;
			dfs(2*u,s,mid,ans);
			dfs(2*u+1,mid+1,e,ans);
		}
		for(auto& q:Q[u])if(q.ok) dsu.RB();
	}
	vector<int> solve(){ // get components
		vector<int> ans(T);
		dfs(1,0,T-1,ans);
		return ans;
	}
};