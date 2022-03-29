#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define st first
#define nd second

vector<vector<ll>> g;
vector<pair<ll, ll>> seg;
vector<bool> vis;
bool ans = true;

void dfs(ll v) {
    if(vis[v]) return;
    vis[v] = true;
    for(auto w : g[v]) {
        if(!vis[w]) {
            if(seg[w].st == seg[w].nd) {
                if(seg[v].st == seg[v].nd) {
                    if(abs(seg[w].st - seg[v].st) != 1) {
                        ans = false;
                        return;
                    }
                }
                if(seg[w].st < seg[v].st-1 || seg[w].st > seg[v].nd+1) {
                    ans = false;
                    return;
                }
            }
            else {
                seg[w].st = seg[v].st-1;
                seg[w].nd = seg[v].nd+1;
            }
            dfs(w);
            seg[v].st = max(seg[v].st, seg[w].st-1);
            seg[v].nd = min(seg[v].nd, seg[w].nd+1);
            if(seg[v].st > seg[v].nd) {
                ans = false;
                return;
            }
        }
    }
}

void dfs1(ll v) {
    if(vis[v]) return;
    vis[v] = true;
    for(auto w : g[v]) {
        if(!vis[w]) {
            seg[w].st = max(seg[w].st, seg[v].st-1);
            seg[w].nd = min(seg[w].nd, seg[v].nd+1);
            seg[w].nd = seg[w].st;
            dfs1(w);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n, k;
    cin >> n;
    g.resize(n+1);
    for(ll i = 0; i < n-1; i++) {
        ll a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    cin >> k;
    ll root = 1;
    seg.assign(n+1, {-1e8, 1e8});
    for(ll i = 0; i < k; i++) {
        ll v, x;
        cin >> v >> x;
        if(i == 0) root = v;
        seg[v] = {x, x};
    }
    vis.assign(n+1, false);
    dfs(root);
    if(!ans) {
        cout << "No\n";
        return 0;
    }
    vis.assign(n+1, false);
    dfs1(root);
    cout << "Yes\n";
    for(ll i = 1; i <= n; i++)
        cout << seg[i].st << "\n"; 
    return 0;
}