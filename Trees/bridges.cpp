vector<int> g[M];
int tin[M],tout[M],low[M],vis[M];
int timer;

void dfs(int u,int pa=0) {
	vis[u]=1;
	tin[u]=low[u]=++timer;
	for(int v:g[u]) {
		if(v==pa) continue;
		if(vis[v]) low[u]=min(low[u],tin[v]);
		else {
			dfs(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>tin[u]) {
				// bridge u-v
			}
		}
	}
}