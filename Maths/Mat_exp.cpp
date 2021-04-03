#define K 15

struct mat{
	int data[K][K];
};

mat operator*(mat &a, mat &b){
	mat c;
	for(int i=0;i<K;++i)for(int j=0;j<K;++j){
		c.data[i][j]=0;
		for(int k=0;k<K;++k) {
			c.data[i][j]+=(a.data[i][k]*1ll*b.data[k][j])%md;
			if(c.data[i][j]>=md) c.data[i][j]-=md;
		}
	}
	return c;
}

mat operator^(mat &a,int b){
	mat c;
	for(int i=0;i<K;++i)for(int j=0;j<K;++j) c.data[i][j]=(i==j);
	while(b){if(b&1)c=c*a;a=a*a;b/=2;}
	return c;
}
