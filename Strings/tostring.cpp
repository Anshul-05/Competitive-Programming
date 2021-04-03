string tostring(int n,int k=1) {
	string ans;
	while(n) ans+=(char)(n%2+'0'),n/=2;
	while(sz(ans)<k) ans+="0";
	reverse(all(ans));
	return ans;
}
