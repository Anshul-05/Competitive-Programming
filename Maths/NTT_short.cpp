const int LN=22;
const int M=1<<LN;
const int root=3;
const int md=998244353;

int add(const int& a,const int& b){
	int c=a+b;
	if(c>=md) c-=md;
	return c;
}
int sub(const int& a,const int& b){
	int c=a-b;
	if(c<0) c+=md;
	return c;
}
int mul(const int& a,const int& b){
	return (a*1ll*b)%md;
}
int ex(int a,int b=md-2){
	int ans=1;
	while(b) {
		if(b&1) ans=mul(ans,a);
		a=mul(a,a),b/=2;
	}
	return ans;
} 

int rev[M],cur_len=0;
int W[M];

void init() {
	W[0]=W[1]=1;
	for(int k=1;k<LN;++k) {
		int z[]={1,ex(root,(md-1)>>(k+1))};
		for(int i=(1<<k);i<(2<<k);++i) {
			W[i]=mul(W[i/2],z[i&1]);
		}
	}
}

void reverse(int n) {
	for(int i=0;i<n;++i) {
		rev[i]=rev[i>>1]>>1;
		if(i&1) rev[i]^=(n>>1);
	}
}

void fft(vector<int>& A,bool inv=0) {
		int n=A.size();
		if(cur_len!=n) reverse(n),cur_len=n;
		
		for(int i=0;i<n;++i) {
			if(i<rev[i]) swap(A[i],A[rev[i]]);
		}
		
		for(int s=1;s<n;s<<=1) {
			for(int i=0;i<n;i+=2*s) {
				for(int j=0;j<s;++j) {
					int u=A[i+j],v=(A[i+j+s]*1ll*W[j+s])%md;
					A[i+j]=(u+v>=md)?u+v-md:u+v;
					A[i+j+s]=(u<v)?u-v+md:u-v;
				}
			}
		}
		if(inv) {
			int x=ex(n);
			for(int i=0;i<n;++i) A[i]=mul(A[i],x);
		}
}

vll brute(vll& a,vll& b) {
	vll c(sz(a)+sz(b),0);
	rep(i,0,sz(a))rep(j,0,sz(b))c[i+j]=add(c[i+j],mul(a[i],b[j]));
	return c;
}

vector<int> mul(const vector<int>& a,const vector<int>& b) {
	int n=1,k=sz(a)+sz(b);
	while(n<k) n<<=1;
	vector<int> A(a.begin(),a.end()),B(b.begin(),b.end());
	A.resize(n),B.resize(n);
	fft(A),fft(B);
	for(int i=0;i<n;++i) A[i]=mul(A[i],B[i]);
	reverse(A.begin()+1,A.begin()+n);
	fft(A,1);
	A.resize(k);
	while(!A.back()) A.pop_back();
	return A;
}
