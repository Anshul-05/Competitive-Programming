vector<int> manacher(const string& s) {
	int n=s.size();
	vector<int> d(n),cnt(n,0);
	for(int i=0,l=0,r=-1;i<n;++i) {
		int k=(i>r)?1:min(d[l+r-i],r-i+1);
		while(i-k>=0 and i+k<n and s[i-k]==s[i+k])++k;
		d[i]=k--;
		cnt[i-k]++,cnt[i]--;
		if(i+k>r) l=i-k,r=i+k;
	}
	for(int i=0,l=0,r=-1;i<n;++i) {
		int k=(i>r)?0:min(d[l+r-i+1],r-i+1);
		while(i-k-1>=0 and i+k<n and s[i-k-1]==s[i+k])++k;
		cnt[i-k]++,cnt[i]--;
		d[i]=k--;
		if(i+k>r) l=i-k-1,r=i+k;
	}
	cnt[0]++;
	for(int i=1;i<n;++i) cnt[i]+=cnt[i-1];
	// cnt[i] -> no of palins which start with i
	return cnt;
}
