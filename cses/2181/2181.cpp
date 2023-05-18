#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <limits>
#include <assert.h>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <list>
#include <assert.h>
#include <array>
#include <cstring>
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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	vector<mi> dp(1 << n);
	vector<mi> ndp(1 << n);
	
	dp[0] = 1;
	const int mask = (1 << n) - 1;
	for (int k = 0; k < m; k++) {
		for (int j = 0; j < n - 1; j++) {
			for (int i = 0; i < (1 << n); i++) {
				if (!((3 << j) & i)) {
					dp[i | (3 << j)] += dp[i];
				}
			}
		}
		for (int i = 0; i < (1 << n); i++) {
			ndp[mask ^ i] = dp[i]; 
		}
		dp = ndp;
		
	}
	cout << dp[0].v << endl;


	// IF STUCK:
		// DIV CONQUER?
		// CONSIDER SMALL CASES
	return 0;
}
