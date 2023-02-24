#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
using ll = long long int;
using llu = long long unsigned;
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

// vector<int> primes = sieve(200000);


ll getbit(int r, int c, int d) {
    vector<int> dirs = {0, -1, 0, 1, 0};
    int nr = r + dirs[d];
    int nc = c + dirs[d + 1];
    if(nr < 0 || nc < 0 || nr >= 7 || nc >= 7) return -1;
    return 1 << (nr * 7 + nc);
}

ll full = ((ll)1 << 49) - 1;

ll dfs(ll mask, ll pos, unordered_map<ll, ll, custom_hash>& dp) {
    // cout << mask << ", " << pos << endl;
    if(pos == 42) {
        if (mask == full) return 1;
        return 0;
    }
    ll key = (mask << 7) + pos;
    if(dp.count(key)) return dp[key];
    vector<int> dirs = {0, -1, 0, 1, 0};
    ll res = 0;
    int r = pos / 7;
    int c = pos - 7 * r;
    for(int d = 0; d < 4; ++d) {
        int nr = r + dirs[d];
        int nc = c + dirs[d + 1];
        if(nr < 0 || nc < 0 || nr >= 7 || nc >= 7) continue;
        ll bit = (ll)1 << (nr * 7 + nc);        
        if(mask & bit) continue;
        res += dfs(mask | bit, nr * 7 + nc, dp);
    }
    dp[key] = res;
    return res;
}


void solve() {
    ll n;
    unordered_map<ll, ll, custom_hash> dp;
    ll res = dfs(1, 0, dp);
    
    cout << full << endl;

    cout << res << endl;
}




int main() {
    AC
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}