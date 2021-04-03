using cd = complex<double>;
const double PI = acos(-1.0);

int rev[M],cur_len=0;
cd W[M];

void reverse(int n) {
	for(int i=0;i<n;++i) {
		rev[i]=rev[i>>1]>>1;
		if(i&1) rev[i]^=(n>>1);
	}
}

void fft(vector<cd>& A,bool inv=0) {
		int n=A.size();
		if(cur_len!=n) reverse(n),cur_len=n;
		
		for(int i=0;i<n;++i) {
			if(i<rev[i]) swap(A[i],A[rev[i]]);
		}
		for(int s=1;s<n;s<<=1) {
			double x= (inv?-1:1)*PI/s;
			cd w(cos(x),sin(x));
			W[0]=cd(1,0);
			for(int i=1;i<s;++i) W[i]=W[i-1]*w;
			
			for(int i=0;i<n;i+=2*s) {
				for(int j=0;j<s;++j) {
					cd u=A[i+j],v=A[i+j+s]*W[j];
					A[i+j]=u+v,A[i+j+s]=u-v;
				}
			}
		}
		if(inv) for(int i=0;i<n;++i) A[i]/=(n<<1);
}

vector<int> mul(const vector<int>& a,const vector<int>& b) {
	int n=1;
	while(n<sz(a)+sz(b)) n<<=1;
	vector<cd> A(n);
	rep(i,0,n) {
		double x=0,y=0;
		if(i<sz(a)) x=a[i];
		if(i<sz(b)) y=b[i];
		A[i]=cd(x,y);
	}
	fft(A);
	for(int i=0;i<n;++i) A[i]=A[i]*A[i];
	fft(A,1);
	int k=sz(a)+sz(b);
	vector<int> ans(k);
	for(int i=0;i<k;++i) ans[i]=(int)(A[i].imag()+0.5);
	return ans;
}
