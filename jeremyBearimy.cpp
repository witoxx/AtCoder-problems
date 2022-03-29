#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<vector<pair<ll, ll>>> Graph;
typedef vector<ll> vi;
#define st first
#define nd second

ll k, mini, maxi;

void dfs(ll v, Graph &g, vi &vis, vi &sub) {
    if(vis[v]) return;
    vis[v] = true;
    for(auto w : g[v]) {
        if(!vis[w.st]) {
            dfs(w.st, g, vis, sub);
            sub[v] += sub[w.st];
            maxi += w.nd*min(sub[w.st], 2*k-sub[w.st]);
            mini += w.nd*(sub[w.st]%2);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll t;
    cin >> t;
    while(t--) {
        mini = 0; maxi = 0;
        cin >> k;
        Graph g(2*k+1);
        for(ll i = 0; i < 2*k-1; i++) {
            ll a, b, w;
            cin >> a >> b >> w;
            g[a].push_back({b, w});
            g[b].push_back({a, w});
        }
        vi sub(2*k+1, 1), vis(2*k+1, false);
        dfs(1, g, vis, sub);
        cout << mini << " " << maxi << "\n";
    }
    return 0;
}