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

// vector<int> primes = sieve(200000);

void solve() {
    ll n;

    cin >> n;
    vector<ll> lt = {0, 0, 6, 28, 96, 252, 550, 1056, 1848};
    ll shift = 4 * 15 - 12;
    for(int i = 9; i <= n; ++i) {
        ll cnt2 = i * i;
        ll cnt1 = (i - 1) * (i - 1);
        ll pre = cnt1 * (cnt1 - 1) / 2 - lt[i - 1];
        shift += 8;
        lt.push_back(cnt2 * (cnt2 - 1) / 2 - pre - shift);
    }
    for(int i = 1; i <= n; ++i) {
        cout << lt[i] << endl;
    }
}




int main() {
    AC
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}