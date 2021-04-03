#include<bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define vll vector<int>
#define pii pair<int,int>
#define pb push_back
#define sz(v) (int)(v).size()
#define inf 1e18
#define md 1000000007
#define all(v) (v).begin(),(v).end()
#define rep(i,a,b) for(int i=a;i<b;++i)
using namespace std;

#define M 100010

vll g[M];
int n,t,m;
int sz[M],son[M];
void run(int u,int pa=0){
	sz[u]=1;
	for(auto v:g[u])if(v!=pa){
		run(v,u),sz[u]+=sz[v];
		if(sz[v]>sz[son[u]])son[u]=v;
	}
}
int ans[M],sum;
int col[M];
int mx,ch;
string s;
void up(int u,int pa,int y){
	// add smthng
	for(auto v:g[u])if(v!=pa and v!=ch)up(v,u,y);
}
void dfs(int u,int pa=0,bool ok=1){
	for(auto v:g[u])if(v!=pa and v!=son[u])dfs(v,u);
	if(son[u])dfs(son[u],u,0),ch=son[u];
	up(u,pa,1),ch=0;
	// do smthng
	if(ok)up(u,pa,0);
}
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
   	
   	cin>>n>>m;
   	rep(i,2,n+1){
   		// add edge
   	}
   	run(1);dfs(1);
   	// print ans
    
    return 0;
}