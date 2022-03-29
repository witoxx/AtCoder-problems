#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll ans = 0, maxi;
vector<ll> h, coin, tow;
vector<vector<ll>> g;
vector<bool> vis, leaf;

void dfs(ll v, ll par) {
    if(vis[v]) return;
    vis[v] = true;
    if(leaf[v]) {
        tow[v] = v;
        coin[v] = h[v];
        ans += h[v];
        if(coin[v] > coin[par]) {
            coin[par] = coin[v];
            tow[par] = v;
        }
        return;
    }
    for(auto w : g[v]) dfs(w, v);
    if(par != 0) {
        if(coin[v] < h[v]) {
            ans += (h[v] - coin[v]);
            coin[v] = h[v];
            coin[tow[v]] = h[v];
        }
        if(coin[v] > coin[par]) {
            coin[par] = coin[v];
            tow[par] = tow[v]; 
        }
    }
}

void dfs1(int v) {
    if(vis[v]) return;
    vis[v] = true;
    maxi = max(maxi, coin[v]);
    for(auto w : g[v]) dfs1(w);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n;
    cin >> n;
    h.resize(n+1);
    for(int i = 1; i <= n; i++) cin >> h[i];
    g.resize(n+1);
    for(int i = 0; i < n-1; i++) {
        ll a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    if(n == 2) {
        cout << 2*max(h[1], h[2]) << "\n";
        return 0;
    }

    vis.assign(n+1, false);
    leaf.assign(n+1, false);
    tow.assign(n+1, -1);
    coin.assign(n+1, -1);
    ll root = 0, rootH = 0;
    for(int i = 1; i <= n; i++) {
        if(h[i] > rootH) {
            rootH = h[i];
            root = i;
        }
        if((int) g[i].size() == 1) leaf[i] = true; 
    }
    bool rootIsLeaf = false;
    if(leaf[root]) {
        leaf[root] = false;
        rootIsLeaf = true;
    }
    dfs(root, 0);

    ll one = 0, two = 0;
    vis.assign(n+1, false);
    vis[root] = true;
    for(auto v : g[root]) {
        maxi = 0;
        dfs1(v);
        if(maxi > one) {
            two = one;
            one = maxi;
        }
        else if(maxi > two) two = maxi;
    }
    if(rootIsLeaf) ans += h[root] + (h[root]-one);
    else ans += 2*h[root] - (one+two);
    cout << ans << "\n";
    return 0;
}