struct node{
	node* to[26];
	int pos;
};
node* create(){
	node* t=new node();
	t->pos=0;
	memset(t->to,0,sizeof(t->to));
	return t;
}
void add(node* x,const string &s){
	rep(i,0,sz(s)){
		int c=s[i]-'a';
		if(!x->to[c])x->to[c]=create();
		x=x->to[c];
	}
	x->pos=1;
}