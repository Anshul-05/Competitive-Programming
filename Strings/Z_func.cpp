vector<int> Z_func(const string s){
	int n=sz(s),l=0,r=0;
	vector<int> z(n,n);
	for(int i=1;i<n;++i){
		z[i]=i>r?0:min(r-i+1,z[i-l]);
		while((i+z[i])<n and s[z[i]]==s[i+z[i]])z[i]++;
		if(i+z[i]-1>r) l=i,r=i+z[i]-1;
	}
	return z;
}
vector<int> pi(string s){
	int n=sz(s);
	vector<int> Z(n,0);
	for(int i=1;i<n;++i){
		int j=Z[i-1];
		while(j and s[i]!=s[j])j=Z[j-1];
		if(s[i]==s[j])++j;
		Z[i]=j;
	}
	return Z;
}