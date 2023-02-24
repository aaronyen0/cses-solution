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
    vector<ll> bit;

    BIT(int _n) {
        n = _n;
        bit.assign(n + 5, 0);
    }

    void update(int idx, ll val) {
        while (idx <= n) {
            bit[idx] = max(bit[idx], val);
            idx += idx & -idx;
        }
    }

    ll query(int idx) {
        ll res = 0;
        while (idx > 0) {
            res = max(bit[idx], res);
            idx -= idx & -idx;
        }
        return res;
    }
};

/*
      5 3
      4 2 1 5 3

2 3:  4 1 2 5 3 -> 2
1 5:  3 1 2 5 4 -> 3
2 3:  3 2 1 5 4 -> 4

x x a x x x b x x
a < b >>  ----
a > b >>  ++++


1 2 3 4 5 6 >> 1
1 5 3 4 2 6 >> 3
6 2 3 4 5 1 >> 3
*/

ll get_round(vector<ll> vals) {
    ll n = vals.size(), res = 0, x;
    vector<ll> seen = vector<ll>(n + 1, 0);
    reverse(vals.begin(), vals.end());
    for(auto x : vals) {
        if(x == 1 || seen[x - 1]) res++;
        seen[x] = 1;
    }
    return res;
}

void solve() {
    ll n, q, x, y, a, b;
    cin >> n >> q;
    vector<ll> vals(n + 1), val2idx(n + 1, -1);
    for(int i = 1; i <= n; ++i) {
        cin >> vals[i];
        val2idx[vals[i]] = i;
    }
    bool left1, right1, left2, right2;
    bool left11, right11, left22, right22;
    ll base = get_round(vector<ll>(vals.begin() + 1, vals.end()));
    // cout << base << endl;
    for(int i = 0; i < q; ++i) {
        cin >> x >> y;
        a = min(x, y);
        b = max(x, y);
        ll val1 = vals[a];
        ll val2 = vals[b];

        left1 = right1 = left2 = right2 = false;
        if(val1 != 1 && val2idx[val1 - 1] < a) left1 = true;
        if(val1 != n && val2idx[val1 + 1] > a) right1 = true;

        if(val2 != 1 && val2idx[val2 - 1] < b) left2 = true;
        if(val2 != n && val2idx[val2 + 1] > b) right2 = true;
        // printf("val1: %d, flags: %d, %d\n", val1, left1, right1);
        // printf("val2: %d, flags: %d, %d\n", val2, left2, right2);

        vals[a] = val2;
        vals[b] = val1;
        val2idx[val1] = b;
        val2idx[val2] = a;

        left11 = right11 = left22 = right22 = false;
        if(val1 != 1 && val2idx[val1 - 1] < b) left11 = true;
        if(val1 != n && val2idx[val1 + 1] > b) right11 = true;

        if(val2 != 1 && val2idx[val2 - 1] < a) left22 = true;
        if(val2 != n && val2idx[val2 + 1] > a) right22 = true;

        // printf("val1: %d, flags: %d, %d\n", val1, left11, right11);
        // printf("val2: %d, flags: %d, %d\n", val2, left22, right22);


        base -= (left11 - left1) + (right11 - right1) + (left22 - left2) + (right22 - right2);
        if(val1 + 1 == val2) {
            base -= 1;
        } else if (val1 - 1 == val2) {
            base += 1;
        }
        printf("%d\n", base);
    }
    
    
}


int main() {
    AC
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}