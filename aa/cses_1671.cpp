// https://cses.fi/problemset/task/1068
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

void csum(int& a, int b) {
    a = (a + b) % MOD;
}



void solve() {
    ll n, m, x, y, c;
    cin >> n >> m;
    vector<vector<pii>> adj(n + 1);
    for(int i = 0; i < m; ++i) {
        cin >> x >> y >> c;
        adj[x].push_back({y, c});
    }

    vector<bool> seen(n + 1, false);
    vector<ll> dist(n + 1, LL_MAX);

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, 1});
    dist[1] = 0;

    while(pq.size()) {
        auto [cost, node] = pq.top(); pq.pop();
        if(seen[node]) continue;
        seen[node] = true;
        for(auto [nxt, val] : adj[node]) {
            if(val + cost < dist[nxt]) {
                dist[nxt] = val + cost;
                pq.push({val + cost, nxt});
            }
        }
    }
    for(int i = 1; i <= n; ++i) {
        cout << dist[i] << " ";
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