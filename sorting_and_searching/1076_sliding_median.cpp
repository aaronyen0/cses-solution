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
    ll n, k;
    cin >> n >> k;
    vector<ll> vals(n + 1);
    set<ll> svals;
    unordered_map<ll, ll> val2idx, idx2val;
    for(int i = 1; i <= n; ++i) {
        cin >> vals[i];
        svals.insert(vals[i]);
    }

    ll idx = 1;
    for(auto val : svals) {
        val2idx[val] = idx;
        idx2val[idx] = val;
        idx++;
    }

    ll k2 = (k + 1) / 2;
    BIT bit = BIT(val2idx.size());
    vector<ll> res;
    for(int i = 1; i <= n; ++i) {
        ll idx = val2idx[vals[i]];
        if(i > k) {
            bit.update(val2idx[vals[i - k]], -1);
        }
        bit.update(idx, 1);
        if(i >= k) {
            res.push_back(idx2val[bit.find_kth(k2)]);
        }
    }
    for(auto x : res) {
        cout << x << " ";
    }
    cout << endl;

}


int main() {
    AC
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}
