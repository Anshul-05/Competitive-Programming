int LIS(vector<int> &v){
	int n=v.size();
	if(!n)return 0;
	vector<int>dp;
	dp.pb(v[0]);
	for(int i=1;i<n;++i){
		auto it=upper_bound(all(dp),v[i]);
		if(it==dp.end())dp.pb(v[i]);
		else *it=v[i];
	}
	return sz(dp);
}