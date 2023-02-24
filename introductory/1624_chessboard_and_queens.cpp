#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
using ll = long long int;
using pii = pair<ll, ll>;
#define AC ios::sync_with_stdio(0),cin.tie(0);

// std::cout << std::fixed << std::setprecision(n);
ll LL_MAX = 1e18 + 1;
ll const N = 200005;
ll const BLEN = __lg(N) + 1;
ll const MOD = 1e9 + 7;
 
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
 
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
 
int gcd(int x, int y) {
    int tmp;
    while(x) {
        y -= y / x * x;
        tmp = x;
        x = y;
        y = tmp;
    }
    return y;
}


int const INF = 1e8;

vector<int> sieve(int n) {
    vector<int> primes(n + 1, 0);
    for(int i = 2; i <= n; ++i) {
        if(primes[i] != 0) continue;
        primes[i] = i;
        for(int base = i; base <= n; base += i) {
            if(primes[base] == 0) primes[base] = i;
        }
    }
    return primes;
}




int dfs(int r, vector<vector<int>>& chessboard, vector<int>& cols, vector<int>& diag1, vector<int>& diag2) {
    if(r == 8) return 1;

    int res = 0;
    for(int c = 0; c < 8; ++c) {
        if(chessboard[r][c] == -1) continue;
        if(cols[c]) continue;
        if(diag1[r + c]) continue;
        if(diag2[r - c + 8]) continue;

        cols[c] = 1;
        diag1[r + c] = 1;
        diag2[r - c + 8] = 1;
        res += dfs(r + 1, chessboard, cols, diag1, diag2);
        cols[c] = 0;
        diag1[r + c] = 0;
        diag2[r - c + 8] = 0;
    }
    return res;
}

void solve() {
    ll n;
    string x;
    vector<vector<int>> chessboard(8, vector<int>(8, 0));
    vector<int> cols(8, 0), diag1(20, 0), diag2(20, 0);
    for(int i = 0; i < 8; ++i) {
        cin >> x;
        for(int j = 0; j < 8; ++j) {
            if(x[j] == '*') chessboard[i][j] = -1;
        }
    }

    
    cout << dfs(0, chessboard, cols, diag1, diag2) << endl;
}




int main() {
    AC
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}