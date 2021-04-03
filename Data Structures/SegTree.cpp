struct Node {
	// Node info
	
	Node() {
		
	}	
	void Reset() {
		
	}
};

class SegTree {
	int N;
	vector<Node> t;
	public:
	SegTree(){}
	
	SegTree(int n){
		N=n;
		t.assign(4*N+10,Node());
	}
	
	SegTree(vector<int> &A) {
		N=(int)A.size();
		t.assign(4*N+10,Node());
		Build(A,1,0,N-1);
	}
	
	Node Merge(Node& A,Node& B) {
		// merge two Nodes
		Node C;
		
		return C;
	}
	
	void Build(vector<int> &a,int u,int s,int e) {
		if(s==e) {
			// leaf
			t[u].sum=a[s];
			return;
		}
		int mid=(s+e)>>1;
		Build(a,2*u,s,mid);
		Build(a,2*u+1,mid+1,e);
		t[u]=Merge(t[2*u],t[2*u+1]);
	}
	
	void Push(int u,int par) {
		// push info to child
		
	}
	
	void push(int u,int l,int r) {
		// update Node info
		
		
		if(l!=r) {
			Push(2*u,u);
			Push(2*u+1,u);
		}
		t[u].Reset();
	}
	
	void update(int l,int r,int x,int type=1) {
		update(1,0,N-1,l,r,x);
	}
	
	int query(int l,int r) {
		return query(1,0,N-1,l,r).sum;
	}
	
	void update(int u,int s,int e,int l,int r,int x) {
		if(e<l or r<s) return;
		if(l<=s and e<=r) {
			// update Node
			
			return;
		}
		push(u,s,e);
		int mid=(s+e)>>1;
		update(2*u,s,mid,l,r,x);
		update(2*u+1,mid+1,e,l,r,x);
		push(2*u,s,mid);
		push(2*u+1,mid+1,e);
		t[u]=Merge(t[2*u],t[2*u+1]);
	}
	
	Node query(int u,int s,int e,int l,int r) {
		if(e<l or r<s) return Node(); 
		push(u,s,e);
		if(l<=s and e<=r) return t[u];
		int mid=(s+e)>>1;
		Node L=query(2*u,s,mid,l,r);
		Node R=query(2*u+1,mid+1,e,l,r);
		return Merge(L,R);
	}
};