#include<bits/stdc++.h>
#define int long long
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

#define M 400010
#define K 20

int n,a[M];
int tin[M],tout[M],t;
vll g[M];
int B[2*M],col[M],pos[2*M];
int dp[M][K];

struct query{
	int id,l,r;
	bool operator<(const query& R){
		return (B[l]==B[R.l])?r<R.r:B[l]<B[R.l];
	}
}Q[M];

void dfs(int u,int pa=1){
	tin[u]=++t,pos[t]=u;
	dp[u][0]=pa;
	rep(i,1,K)dp[u][i]=dp[dp[u][i-1]][i-1];
	for(auto v:g[u])if(v!=pa)dfs(v,u);
	tout[u]=++t,pos[t]=u;
}

bool is(int u,int v){return tin[u]<=tin[v] and tout[u]>=tout[v];}

int get(int u,int v){
	if(is(u,v))return u;
	if(is(v,u))return v;
	for(int i=K-1;i>=0;--i)if(!is(dp[u][i],v))u=dp[u][i];
	return dp[u][0];
}

int sum,cnt[M],ans[M];

void add(int x,int y){
	if(y and (--cnt[col[x]]==0))sum--;
	else if(!y and (cnt[col[x]]++==0))sum++;
}

void solve(){
	int L=Q[1].l,R=L-1;
	rep(i,1,n+1){
		while(L<Q[i].l)add(pos[L++],1);
		while(L>Q[i].l)add(pos[--L],0);
		while(R<Q[i].r)add(pos[++R],0);
		while(R>Q[i].r)add(pos[R--],1);
		ans[Q[i].id]=sum;
	}
	rep(i,1,n+1)cout<<ans[i]<<" ";
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
   	
   	cin>>n;
   	rep(i,1,n+1)cin>>col[i];
   	rep(i,0,n-1){
   		int u,v;cin>>u>>v;
   		g[u].pb(v),g[v].pb(u);
   	}
   	dfs(1);
   	
   	int sq=sqrt(t);
   	rep(i,1,t+1)B[i]=(i-1)/sq+1;
   	rep(i,1,n+1){
   		Q[i].l=tin[i],Q[i].r=tout[i]-1;
   		Q[i].id=i;
   	}
   	sort(Q+1,Q+n+1);
   	// compress colors
   	int tmp[n+1];
   	rep(i,1,n+1)tmp[i]=col[i];
   	sort(tmp+1,tmp+n+1);
   	int dis=unique(tmp+1,tmp+n+1)-tmp-1;
   	rep(i,1,n+1)col[i]=lower_bound(tmp+1,tmp+dis+1,col[i])-tmp;
   	
   	solve();
   	
    
    return 0;
}