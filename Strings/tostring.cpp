string tostring(int n) {
	if(!n) return "0";
	string ans;
	while(n) ans+=(char)(n%2+'0'),n/=2;
	reverse(all(ans));
	return ans;
}