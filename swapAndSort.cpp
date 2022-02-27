#include <bits/stdc++.h>
using namespace std;
#define st first
#define nd second

int n, m, k = 0;
vector<int> p, comp, ans;
vector<bool> vis, removed;
vector<vector<pair<int, int>>> g;
queue<int> order;

void components(int v, int num) {
    if(comp[v] != -1) return;
    comp[v] = num;
    for(auto w : g[v]) components(w.st, num);
}

void topo(int v) {
    if(vis[v]) return;
    vis[v] = true;
    for(auto w : g[v]) topo(w.st);
    order.push(v);
}

void bfs(int v, int s) {
    int beg = v;
    bool stop = false;
    vector<pair<int, int>> par(n+1, {-1, -1});
    queue<int> q;
    par[v] = {v, 0};
    q.push(v);
    
    while(!q.empty() && !stop) {
        v = q.front();
        q.pop();
        for(auto w : g[v]) {
            if(par[w.st].st == -1 && !removed[w.st]) {
                q.push(w.st);
                par[w.st] = {v, w.nd};
                if(w.st == s) {
                    stop = true;   
                    break;
                }
            }
        }
    }
    
    vector<pair<int, int>> swaping;
    int x = ans.size();
    do {
        k++;
        swaping.push_back({s, par[s].st});
        ans.push_back(par[s].nd);
        s = par[s].st;
    } while(s != beg);
    reverse(ans.begin() + x, ans.end());
    reverse(swaping.begin(), swaping.end());
    for(auto i : swaping) swap(p[i.st], p[i.nd]);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    p.resize(n+1);
    g.resize(n+1);
    for(int i = 1; i <= n; i++) cin >> p[i];
    cin >> m;
    for(int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
    }

    comp.assign(n+1, -1);
    int num = 0;
    for(int i = 1; i <= n; i++) {
        if(comp[i] == -1) {
            components(i, num);
            num++;
        }
    }
    bool isPossible = true;
    for(int i = 1; i <= n; i++) {
        if(comp[p[i]] != comp[i]) {
            isPossible = false;
            break;
        }
    }
    if(!isPossible) {
        cout << "-1\n";
        return 0;
    }

    vis.assign(n+1, false);
    removed.assign(n+1, false);
    for(int i = 1; i <= n; i++) topo(i);
    
    while(!order.empty()) {
        int s = order.front(), pos;
        order.pop();
        for(int i = 1; i <= n; i++) {
            if(p[i] == s) {
                pos = i;
                break;
            }
        }
        if(pos != s) bfs(pos, s);
        removed[s] = true;
    }
    cout << k << "\n";
    for(auto i : ans) cout << i << " ";
    cout << "\n";
    return 0;