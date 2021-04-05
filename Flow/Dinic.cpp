struct Edge {
	int u,v,cap,flow=0;
	Edge(int u,int v,int cap) : u(u), v(v), cap(cap) {}
};

class Dinic {
	public:
	vector<Edge> edges;
	vector<vector<int>> G;
	int n,m=0,s,t;
	vector<int> H,ptr;
	queue<int> q;
	
	Dinic(int n,int s,int t) : n(n), s(s), t(t) {
		G.resize(n+1);
		H=ptr=vector<int>(n+1);
	}
	
	void add(int u,int v,int cap) {
		edges.emplace_back(u,v,cap);
		edges.emplace_back(v,u,0);
		G[u].push_back(m++);
		G[v].push_back(m++);
	}
	
	bool bfs() {
		while(!q.empty()) {
			int u=q.front();
			q.pop();
			for(int v:G[u]) {
				int to=edges[v].v;
				int gap=edges[v].cap-edges[v].flow;
				if(H[to]!=-1 or gap<1) continue;
				H[to]=H[u]+1,q.push(to);
			}
		}
		return H[t]!=-1;
	}
	
	int dfs(int u,int X) {
		if(!X) return 0;
		if(u==t) return X;
		for(int &i=ptr[u];i<sz(G[u]);++i) {
			int v=G[u][i],to=edges[v].v;
			int gap=edges[v].cap-edges[v].flow;
			if(H[to]!=(H[u]+1) or gap<1) continue;
			int Y=dfs(to,min(X,gap));
			if(!Y) continue;
			edges[v].flow+=Y;
			edges[v^1].flow-=Y;
			return Y;
		}
		return 0;
	}
	
	int flow() {
		int ans=0;
		while(true) {
			fill(H.begin(),H.end(),-1);
			H[s]=0,q.push(s);
			if(!bfs()) break;
			fill(ptr.begin(),ptr.end(),0);
			while(int X=dfs(s,inf)) ans+=X;
		}
		return ans;
	}
};
// EV^2
// for unit network : Esqrt(V)
