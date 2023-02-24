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

void solve() {
    int n;
    cin >> n;
    if(n == 1) cout << 1 << endl;
    else if(n ==2 || n == 3) cout << "NO SOLUTION" << endl;
    else if (n == 4) cout << "2 4 1 3" << endl;
    else {
        for(int i = 1; i <= n; i += 2) {
            cout << i << " ";
        }
        for(int i = 2; i <= n; i += 2) {
            cout << i << " ";
        }
        cout << endl;
    }
}


int main() {
    AC
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}