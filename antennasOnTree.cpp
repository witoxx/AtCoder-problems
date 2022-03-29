#include <bits/stdc++.h>
using namespace std;

int ans = 0, maxi = 0, root;
vector<vector<int>> g;
vector<int> num;
vector<bool> vis;

void countSons(int v) {
    if(vis[v]) return;
    vis[v] = true;
    int count = 0;
    for(auto w : g[v]) {
        count++;
        countSons(w);
    }
    if(count >= maxi) {
        maxi = count;
        root = v;
    }
}

void dfs(int v) {
    if(vis[v]) return;
    vis[v] = true;
    int sons = 0;
    for(auto w : g[v]) {
        if(!vis[w]) {
            sons++;
            dfs(w);
            num[v] += min(1, num[w]);
        }
    }
    ans += max(0, sons-num[v]-1);
    num[v] += max(0, sons-num[v]-1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    g.resize(n);
    for(int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vis.assign(n, false);
    countSons(0);
    num.assign(n, 0);
    vis.assign(n, false);
    dfs(root);
    cout << max(1, ans) << "\n";
    return 0;
}