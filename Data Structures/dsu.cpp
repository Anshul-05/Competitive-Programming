int p[M];
int find(int v){
	return (v==p[v])?v:p[v]=find(p[v]);
}
void join(int a,int b){
	a=find(a),b=find(b);
	if(rand()%2)swap(a,b);
	p[b]=a;
}
