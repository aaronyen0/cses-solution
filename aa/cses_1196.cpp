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
    ll n, m, k, a, b, c;
    cin >> n >> m >> k;
    vector<vector<pii>> adj(n + 1);
    for(int i = 0; i < m; ++i) {
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }

    vector<ll> counter(n + 1, 0);
    set<pii> pq;
    vector<set<ll>> dist(n + 1);
    vector<unordered_map<ll, ll, custom_hash>> dp(n + 1);

    pq.insert({0, 1}); //cost, node
    dp[1][0] = 1;
    dist[1].insert(0);

    while(pq.size()) {
        auto [cost, node] = *pq.begin(); pq.erase(pq.begin());
        if(counter[node] >= k) continue;
        counter[node] += dp[node][cost];
        // cout << node << ", " << cost << ": " << dp[node][cost] << endl;
        for(auto [nxt, val] : adj[node]) {
            ll new_cost = cost + val;
            if(dist[nxt].count(new_cost)) {
                dp[nxt][new_cost] += dp[node][cost];
            } else {
                dist[nxt].insert(new_cost);
                dp[nxt][new_cost] = dp[node][cost];
                pq.insert({new_cost, nxt});
            }
            // cout << "#### "<< nxt << ", " << new_cost << ": " << dp[nxt][new_cost] << endl;
            ll num = 0;
            auto iter = dist[nxt].begin();
            while(iter != dist[nxt].end()) {
                if(num >= k) break;
                num += dp[nxt][*iter];
                iter++;
            }
            // cout << "#### "<< nxt << ", " << num << endl;
            while(iter != dist[nxt].end()) {
                dp[nxt].erase(*iter);
                pq.erase({*iter, nxt});
                iter = dist[nxt].erase(iter);
            }


            // if(
            //     counter[nxt] >= k || 
            //     (dist[nxt].size() == k && dist[nxt].lower_bound(new_cost) == dist[nxt].end())
            // ) {
            //     continue;
            // }
            // if(dist[nxt].count(new_cost)) {
            //     dp[nxt][new_cost] += dp[node][cost];
            // } else {
            //     dist[nxt].insert(new_cost);
            //     dp[nxt][new_cost] = dp[node][cost];

            //     pq.insert({new_cost, nxt});
            //     if(dist[nxt].size() > k) {
            //         auto iter = --dist[nxt].end();
            //         auto remove_cost = *iter;
            //         dist[nxt].erase(iter);
            //         pq.erase({remove_cost, nxt});
            //         dp[nxt].erase(remove_cost);
            //     }
            // }
        }
    }
    for(auto dis : dist[n]) {
        ll cnt = dp[n][dis];
        while(cnt && k) {
            cnt--;
            k--;
            cout << dis << " ";
        }
        if(!k) break;
    }

}


int main() {
    AC
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}