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

class SegmentTree {
public:
    vector<ll> tree, lazy;
    vector<ll> vals;

    SegmentTree(vector<ll> _vals) {
        int n = _vals.size();
        vals = _vals;
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    void build(int v, int tl, int tr) {
        if(tl == tr) tree[v] = vals[tl];
        else {
            int tm = (tl + tr) / 2;
            build(2 * v, tl, tm);
            build(2 * v + 1, tm + 1, tr);
        }
    }

    ll pull(int v) {
        return tree[2 * v] + tree[2 * v + 1];
    }

    void push(int v, int tl, int tr) {
        int tm = (tl + tr) / 2;
        tree[2 * v] += lazy[v] * (tm - tl + 1);
        tree[2 * v + 1] += lazy[v] * (tr - tm);
        lazy[2 * v] += lazy[v];
        lazy[2 * v + 1] += lazy[v];
        lazy[v] = 0;
    }

    void update(int v, int l, int r, int tl, int tr, ll diff) {
        if(r < tl || l > tr) return;
        if(l <= tl && r >= tr) {
            tree[v] += (tr - tl + 1) * diff;
            lazy[v] += diff;
        } else {
            push(v, tl, tr);
            int tm = (tl + tr) / 2;
            update(2 * v, l, r, tl, tm, diff);
            update(2 * v + 1, l, r, tm + 1, tr, diff);
            pull(v);
        }
    }

    ll getsum(int v, int l, int r, int tl, int tr) {
        if(r < tl || l > tr) return 0;
        if(l <= tl && r >= tr) {
            return tree[v];
        } else {
            push(v, tl, tr);
            int tm = (tl + tr) / 2;
            return getsum(2 * v, l, r, tl, tm) + getsum(2 * v + 1, l, r, tm + 1, tr);
        }
    }
};


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
    cin >> n >> x;
    vector<ll> vals(n + 1);
    unordered_map<ll, ll, custom_hash> ump;
    for(int i = 1; i <= n; ++i) {
        cin >> val;
        diff = x - val;
        if(ump.count(diff)) {
            cout << ump[diff] << " " << i << endl; 
            return;
        }
        ump[val] = i;
    }
    cout << "IMPOSSIBLE" << endl;
}


int main() {
    AC
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}
