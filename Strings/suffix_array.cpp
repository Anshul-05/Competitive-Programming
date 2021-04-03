char s[M];
int n;
int ra[M],sa[M];
int t_ra[M],t_sa[M];
int c[M];
int phi[M],lcp[M],plcp[M];

void sort(int k){
	int i,sum,mx=max(300,n),t;
	memset(c,0,sizeof(c));
	for(i=0;i<n;++i)c[i+k<n?ra[i+k]:0]++;
	for(i=sum=0;i<mx;++i)t=c[i],c[i]=sum,sum+=t;
	for(i=0;i<n;++i)t_sa[c[sa[i]+k<n?ra[sa[i]+k]:0]++]=sa[i];
	for(i=0;i<n;++i)sa[i]=t_sa[i];
}
void SA(){
	int i,k,r;
	for(i=0;i<n;++i)ra[i]=s[i],sa[i]=i;
	for(k=1;k<n;k<<=1){
		sort(k);sort(0);
		t_ra[sa[i]]=r=0;
		for(i=1;i<n;++i)t_ra[sa[i]]=(ra[sa[i]]==ra[sa[i-1]] and ra[sa[i]+k]==ra[sa[i-1]+k])?r:++r;
		for(i=0;i<n;++i)ra[i]=t_ra[i];
		if(ra[sa[n-1]]==n-1)break;
	}
}
void findlcp(){
	phi[sa[0]]=-1;
	for(int i=1;i<n;++i)phi[sa[i]]=sa[i-1];
	for(int i=0,L=0;i<n;++i){
		if(phi[i]==-1){plcp[i]=0;continue;}
		while(s[i+L]==s[phi[i]+L])L++;
		plcp[i]=L,L=max(L-1,0);
	}
	for(int i=0;i<n;++i)lcp[i]=plcp[sa[i]];
}
void prepare(){
	cin>>s;
	n=strlen(s);
	s[n++]='$';
	SA();findlcp();
}