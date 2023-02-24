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
    int n;
    int shift;
    vector<ll> bit;

    BIT(int _n) {
        shift = __lg(_n);
        n = 1 << (shift + 1);
        bit.assign(n, 0);
    }

    void update(int idx, ll val) {
        while (idx <= n) {
            bit[idx] += val;
            idx += idx & -idx;
        }
    }

    ll query(int idx) {
        ll res = 0;
        while (idx > 0) {
            res += bit[idx];
            idx -= idx & -idx;
        }
        return res;
    }

    ll find_kth(int k) {
        int pos = 0, rng = 1 << shift;
        ll cur = 0;
        while(rng > 0) {
            if (cur + bit[pos + rng] < k) {
                cur += bit[pos + rng];
                pos += rng;
            }
            rng >>= 1;
        }
        return pos + 1;
    }

};


void solve() {
    ll n, m, k;
    cin >> n >> m >> k;
    vector<ll> apartments(m), people(n);
    for(int i = 0; i < n; ++i) cin >> people[i];
    for(int i = 0; i < m; ++i) cin >> apartments[i];
    sort(people.begin(), people.end());
    sort(apartments.begin(), apartments.end());
    
    int idx = 0;
    ll res = 0;
    for(auto val : people) {
        while(idx < m && apartments[idx] < val - k) {
            idx++;
        }
        if(idx < m && apartments[idx] <= val + k) {
            idx++;
            res++;
        }
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
