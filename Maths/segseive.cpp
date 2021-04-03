vector<bool> segseive(int L,int R){
	int lim = sqrt(R);
	vector<bool> vis(lim+1,0);
	vector<int> pr;
	for(int i=2;i<=lim;++i){
		if(!vis[i])pr.pb(i);
		for(int j=0;j<pr.size() and i*pr[j]<=lim;++j){
			vis[i*pr[j]]=1;
			if(i%pr[j]==0)break;
		}
	}
	vector<bool>isprime(R-L+1,1);
	for(int i:pr){
		for(int j=max(i*i,(L+i-1)/i*i);j<=R;j+=i) {
			if(j>=L)isprime[j-L]=0;
		}
	}
	if(L==1)isprime[0]=0;
	return isprime;
}