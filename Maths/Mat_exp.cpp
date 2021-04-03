#define K 15
struct mat{
	int data[K][K];
};
mat operator*(mat &a, mat &b){
	mat c;
	rep(i,0,K)rep(j,0,K){
		c.data[i][j]=0;
		rep(k,0,K)(c.data[i][j]+=((a.data[i][k]%md*b.data[k][j]%md))%md)%=md;
	}
	return c;
}
mat operator^(mat &a,int b){
	mat c;
	rep(i,0,K)rep(j,0,K)c.data[i][j]=(i==j);
	while(b){if(b&1)c=c*a;a=a*a;b/=2;}
	return c;
}