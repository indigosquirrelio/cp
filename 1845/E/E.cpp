#include <bits/stdc++.h>
using namespace std;
 
 
const long long MOD = 1e9 + 7;
 
struct mi { // WARNING: needs some adjustment to work with FFT
 	long long v; explicit operator int() const { return v; } 
	mi():v(0) {}
	mi(long long _v):v((int)(_v%MOD)) { v += (v<0)*MOD; }
};
mi& operator+=(mi& a, mi b) { 
	if ((a.v += b.v) >= MOD) a.v -= MOD; 
	return a; }
mi& operator-=(mi& a, mi b) { 
	if ((a.v -= b.v) < 0) a.v += MOD; 
	return a; }
mi operator+(mi a, mi b) { return a += b; }
mi operator-(mi a, mi b) { return a -= b; }
mi operator*(mi a, mi b) { return mi((long long)a.v*b.v); }
mi& operator*=(mi& a, mi b) { return a = a*b; }
mi pow(mi a, long long p) { assert(p >= 0); // won't work for negative p
	return p==0?1:pow(a*a,p/2)*(p&1?a:1); }
mi inv(mi a) { assert(a.v != 0); return pow(a,MOD-2); }
mi operator/(mi a, mi b) { return a*inv(b); }
bool operator==(mi a, mi b) { return a.v == b.v; }
 
const int MAXN = 200000 + 5;
mi fact[MAXN], invfact[MAXN];
mi nCr(int n, int r) {
	return fact[n] * invfact[r] * invfact[n - r];
}
 
void prepareFact() {
	fact[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		fact[i] = fact[i - 1] * i;
	}
	invfact[MAXN - 1] = mi(1) / fact[MAXN - 1];
	for (int i = MAXN - 2; i >= 0; i--) {
		invfact[i] = invfact[i + 1] * (i + 1);
	}
}
 
mi modExp(mi a, long long b) {
	if (b == 0) return 1;
	mi res = modExp(a, b / 2);
	res *= res;
	if (b % 2) res *= a;
	return res;
}
 
mi dp[1501][1501];
mi ndp[1501][1501];
 
int len = 80;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	vector<int> inds;
	vector<int> zinds;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		if (a[i]) inds.push_back(i + 1);
		else zinds.push_back(i + 1);
	}
	if (inds.size() > zinds.size()) swap(inds, zinds);
	dp[0][0] = 1;
	for (int i = 0; i < inds.size(); i++) {
		mi cur = 0;
		int mini = 0;
		int maxi = n;
		if (i + len < inds.size()) maxi = min(maxi, inds[i + len]);
		if (i - len >= 0) mini = max(mini, inds[i - len]);
		for (int j = mini; j <= maxi; j++) {
			for (int l = 0; l <= k; l++) {
				dp[j][l] += dp[j - 1][l];
			}
		}
		
		for (int j = maxi; j >= mini; j--) {
			int dist = abs(inds[i] - j);
			for (int l = k; l >= 0; l--) {
				if (l - dist < 0) dp[j][l] = 0;
				else dp[j][l] = dp[j - 1][l - dist];
				/*
				for (int x = 0; x < j; x++) {
					ndp[j][l] += dp[x][l - dist];
				}
				*/
			}
		}
		//swap(dp, ndp);
	}
	mi res = 0;
	for (int i = 0; i <= n; i++) {
		for (int j = k; j >= 0; j-= 2) {
			res += dp[i][j];
		}
	}
	cout << res.v << endl;
 
	// IF STUCK:
		// DIV CONQUER?
		// CONSIDER SMALL CASES
	return 0;
}