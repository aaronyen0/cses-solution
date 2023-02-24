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

ll mypow(ll val, int k) {
    if(k == 0) return 1;
    if(k == 1) return val;
    ll half = mypow(val, k / (ll)2);
    ll res = (half * half) % MOD;
    if(k & 1) {
        return (res * val) % MOD;
    }
    return res;
}

class BIT {
public:
    // range udpate and single search by BIT
    int n;
    vector<ll> bit;

    BIT(int _n) {
        n = _n;
        bit.assign(n + 1, 0);
    }

    void update(int a, int b, ll val) {
        while(b > 0) {
            bit[b] += val;
            b -= b & -b;
        }

        a--;
        while(a > 0) {
            bit[a] -= val;
            a -= a & -a;
        }
    }

    ll getsum(int idx) {
        ll res = 0;
        while(idx <= n) {
            res += bit[idx];
            idx += idx & -idx;
        }
        return res;
    }
};



void solve() {
    ll n, x, val, diff;
    cin >> n;
    ll res = -LL_MAX, cur = -LL_MAX;
    for(int i = 1; i <= n; ++i) {
        cin >> val;
        if(val + cur < val) {
            cur = val;
        } else {
            cur += val;
        }
        res = max(res, cur);
    }
    cout << res << endl;
}


int main() {
    AC
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}
