#include<bits/stdc++.h>
#define ld long double
#define fi first
#define se second
#define vll vector<int>
#define pii pair<int,int>
#define pb push_back
#define sz(v) (int)(v).size()
#define inf 1e18
#define md (int)(998244353)
#define all(v) (v).begin(),(v).end()
#define rep(i,a,b) for(int i=a;i<b;++i)

using namespace std;

using LL = long long;
#define M 2000010
/*
bool vis[M];
LL cnt[M],sum[M],sump[M];
LL spf[M],mu[M];
void seive(){
	vis[0]=vis[1]=1;
	rep(i,2,M)if(!vis[i])for(int j=2*i;j<M;j+=i)vis[j]=1;
	rep(i,1,M)cnt[i]=!vis[i],cnt[i]+=cnt[i-1];
	rep(i,2,M)if(!spf[i])for(int j=i;j<M;j+=i)if(!spf[j])spf[j]=i;
	rep(i,1,M){
		if(!vis[i])sum[i]=i;
		sum[i]+=sum[i-1];
		sump[i]=spf[i];
		sump[i]+=sump[i-1];
	}
	mu[1]=1;
	rep(i,2,M){
		mu[i]=(spf[i/spf[i]]==spf[i])?0:-1*mu[i/spf[i]];
	}
}
*/
#define KK 1000010
LL l_cnt[KK],l_sum[KK];
LL s_cnt[KK],s_sum[KK];
LL s_sum2[KK];
bool vis[KK];
LL Psum(LL N,LL mod) {
	auto get=[&](LL n) {
		LL x = n%mod, y = (n+1)%mod, xh = (n/2)%mod, yh = ((n+1)/2)%mod;
		LL now;
		if(n % 2 == 0) now = ((LL)xh * y) % mod;
		else now = ((LL)x * yh) % mod;
		now--;
		if(now < 0) now += mod;
		return now;
	};
	LL v = sqrt(N + 0.5);
	// vector<LL> l_cnt(v + 1, 0), l_sum(v + 1, 0);
	// vector<LL> s_cnt(v + 1, 0), s_sum(v + 1, 0);
	// vector<LL> s_sum2(v + 1, 0);
	// vector<bool> vis(v + 1, 0);
	for(int i = 1; i <= v; ++i) {
		s_cnt[i] = i-1, s_sum[i] = get(i);
		l_cnt[i] = (N/i - 1) % mod, l_sum[i] = get(N/i);
		s_sum2[i] = l_sum[i];
	}
	LL p_cnt, p_sum, q, jump, end, d;
	for(int p = 2; p <= v; ++p) {
		if(s_cnt[p] == s_cnt[p-1]) continue;
		p_cnt = s_cnt[p-1], p_sum = s_sum[p-1];
		q = (LL)p * p;
		l_cnt[1] -= l_cnt[p] - p_cnt;
		l_sum[1] -= ((LL)p * (l_sum[p] - p_sum)) % mod;
		s_sum2[1] += (((LL)p * (l_cnt[p] - p_cnt)) % mod - ((LL)p * (l_sum[p] - p_sum)) % mod + mod)%mod;
		// mods
		// if(l_cnt[1] >= mod) l_cnt[1] -= mod;
		if(l_cnt[1] < 0) l_cnt[1] += mod;
		// if(l_sum[1] >= mod) l_sum[1] -= mod;
		if(l_sum[1] < 0) l_sum[1] += mod;
		if(s_sum2[1] >= mod) s_sum2[1] -= mod;
		// mods
		jump = (p & 1) + 1, end = min(v, (LL)(N / q));
		for(int i = p + jump; i <= end; i += jump) {
			if(vis[i]) continue;
			d = p * i;
			if(d <= v) {
				l_cnt[i] -= l_cnt[d] - p_cnt;
				l_sum[i] -= ((LL)p * (l_sum[d] - p_sum)) % mod;
				s_sum2[i] += (((LL)p * (l_cnt[d] - p_cnt)) % mod - ((LL)p * (l_sum[d] - p_sum)) % mod + mod)%mod;
			} else {
				d = N / d;
				l_cnt[i] -= s_cnt[d] - p_cnt;
				l_sum[i] -= ((LL)p * (s_sum[d] - p_sum)) % mod;
				s_sum2[i] += (((LL)p * (s_cnt[d] - p_cnt)) % mod - ((LL)p * (s_sum[d] - p_sum)) % mod + mod)%mod;
			}
			// mods
			// if(l_cnt[i] >= mod) l_cnt[i] -= mod;
			if(l_cnt[i] < 0) l_cnt[i] += mod;
			// if(l_sum[i] >= mod) l_sum[i] -= mod;
			if(l_sum[i] < 0) l_sum[i] += mod;
			if(s_sum2[i] >= mod) s_sum2[i] -= mod;
			// mods
		}
		if(q <= v) {
			for(int i = q; i < end; i += jump * p) vis[i] = 1;
		}
		for(int i = v; i >= q; --i) {
			d = i / p;
			s_cnt[i] -= s_cnt[d] - p_cnt;
			s_sum[i] -= ((LL)p * (s_sum[d] - p_sum)) % mod;
			// mods
			// if(s_cnt[i] >= mod) s_cnt[i] -= mod;
			if(s_cnt[i] < 0) s_cnt[i] += mod;
			// if(s_sum[i] >= mod) s_sum[i] -= mod;
			if(s_sum[i] < 0) s_sum[i] += mod;
			// mods
		}
	}
	// l_cnt[1] -> count primes 
	// l_sum[1] -> sum primes
	// s_sum2[1] -> sum spfs
	return s_sum2[1];
}

int32_t main(){
	
  double _tBeg = clock();
    
	cout<<Psum((LL)1e12,(LL)1e9);
	
	
	
  double _tEnd = clock();
  printf("\ntotal time %.6f\n", (_tEnd - _tBeg) / CLOCKS_PER_SEC);
  
	return 0;
}