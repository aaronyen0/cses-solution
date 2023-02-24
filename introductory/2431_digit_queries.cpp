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

// 1 * 9
// 2 * 90
// 3 * 900
// 4 * 10000

// k * 1ek

// [9 189 2889]
// [1, 2, 3, 4, 5]

// 10 / 2 = 5 % 0

// 1 2 3 4 5 6 7 8 9 
// 1 0 1 1 1 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 
// 2 0


// 190 > 100
// k

// 3
// 7   7
// 19  4
// 12  1



void solve() {
    ll n;

    cin >> n;
    vector<ll> queries(n + 1);
    for(int i = 1; i <= n; ++i) cin >> queries[i];
    
    llu base = 10;
    vector<llu> lt = {0, 9};
    vector<llu> pows = {0, 1};
    for(llu i = 2; i <= 18; ++i) {
        lt.push_back(lt.back() + (i * base * 9));
        pows.push_back(base);
        base *= 10;
    }

    for(int i = 1; i <= n; ++i) {
        auto iter = lower_bound(lt.begin(), lt.end(), queries[i]);
        ll cur = *iter;
        ll idx = (int)(iter - lt.begin());
        ll diff = queries[i] - lt[idx - 1];
        ll r1 = diff / idx;
        ll r2 = diff - idx * r1;
        string s;
        if(r2 == 0) {
            s = to_string(pows[idx] + r1 - 1);
            cout << s.back() << endl;
        } else {
            s = to_string(pows[idx] + r1);
            cout << s[r2 - 1] << endl;
        }

        // cout << s[r1]
        // cout << s << endl;
        // cout << diff << ", " << r1 << ", " << r2 << endl;
    }

}




int main() {
    AC
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}