#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g;
vector<int> nim;
vector<bool> vis;

void dfs(int v) {
    if(vis[v]) return;
    vis[v] = true;
    for(auto w : g[v]) {
        if(!vis[w]) {
            dfs(w);
            nim[v] ^= 1+nim[w];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    g.resize(n+1);
    for(int i = 0; i < n-1; i++) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    nim.assign(n+1, 0);
    vis.assign(n+1, false);
    dfs(1);
    cout << (nim[1] ? "Alice\n" : "Bob\n");
    return 0;
}