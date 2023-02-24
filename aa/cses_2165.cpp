// https://cses.fi/problemset/task/1068
#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
using ll = long long int;
using pii = pair<ll, ll>;
#define AC ios::sync_with_stdio(0),cin.tie(0);
 
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


void dfs(int idx, int* counter, string& cur) {
    if(idx == 0) {
        cout << cur << endl;
        return;
    }

    for(int i = 0; i < 26; ++i) {
        if(counter[i]) {
            counter[i]--;
            cur.push_back((char)('a' + i));
            dfs(idx - 1, counter, cur);
            cur.pop_back();
            counter[i]++;
        }
    }
}


void solve() {
    int n;
    string s, cur;
    cin >> s;
    n = s.size();

    int counter[26] = {0};
    for(auto x : s) counter[x - 'a']++;
    int fac[9];
    fac[0] = 1;
    for(int i = 1; i <= 8; ++i) fac[i] = fac[i - 1] * i;
    int res = fac[n];
    for(auto val : counter) res /= fac[val];

    cout << res << endl;
    dfs(n, counter, cur);
}



int main() {
    AC
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}