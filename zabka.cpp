#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void dfs(int v, vector<vector<int>> &jump, vector<int> &isCycle, vector<int> &vis) {
    if(vis[v] == 2 || vis[v] == 1) return;
    vis[v] = 1;
    if(vis[jump[0][v]] == 1)
        isCycle.push_back(v);
    dfs(jump[0][v], jump, isCycle, vis);
    vis[v] = 2;
}

void dfs1(int v, vector<vector<int>> &jump, vector<int> &dis, vector<int> &par, vector<int> &vis) {
    if(vis[v] == 1) return;
    vis[v] = 1;
    dfs1(jump[0][v], jump, dis, par, vis);
    if(par[v] == -1) {
        dis[v] = dis[jump[0][v]]+1;
        if(dis[v] == 1) par[v] = jump[0][v];
        else par[v] = par[jump[0][v]];
    }
    else dis[v] = 0;
}

int binaryLifting(int i, int moves, int n, vector<vector<int>> &jump) {
    int ans = i;
    for(int j = (long long) log2(n); j >= 0; j--) {
        if((1<<j) <= moves) {
            moves -= (1<<j);
            ans = jump[j][ans];
        }
        if(moves == 0) return ans;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n, k, m;
    cin >> n >> k >> m;
    vector<ll> p(n+1, -1e9);
    vector<vector<int>> jump(log2(n)+1,  vector<int> (n));
    for(int i = 0; i < n; i++) cin >> p[i];
    int l = 0, r = k;
    jump[0][0] = k;
    for(int i = 1; i < n; i++) {
        while(r < n-1 && p[r+1]-p[i] < p[i]-p[l]) l++, r++;
        if(p[i]-p[l] >= p[r]-p[i]) jump[0][i] = l;
        else jump[0][i] = r;
    }

    vector<int> isCycle, vis(n, 0);
    for(int i = 0; i < n; i++)
        dfs(i, jump, isCycle, vis);
    vector<vector<int>> cycles(isCycle.size());
    vector<int> par(n, -1), cyc(n, -1);
    int id = 0;
    for(auto c : isCycle) {
        cycles[id].push_back(c);
        par[c] = c;
        cyc[c] = id;
        int next = jump[0][c];
        while(next != c) {
            cycles[id].push_back(next);
            cyc[next] = id;
            par[next] = next;
            next = jump[0][next];
        }
        id++;
    }

    vis.assign(n, 0);
    vector<int> dis(n, 0);
    for(int i = 0; i < n; i++)
        dfs1(i, jump, dis, par, vis);

    for(int i = 1; i < (int) jump.size(); i++) {
        for(int j = 0; j < n; j++)
            jump[i][j] = jump[i-1][jump[i-1][j]];
    }

    for(int i = 0; i < n; i++) {
        ll moves = m, ans = i;
        if(dis[i] > moves)
            ans = binaryLifting(i, moves, n, jump);
        else {
            moves -= (ll) dis[i];
            moves %= cycles[cyc[par[i]]].size();
            ans = binaryLifting(par[i], moves, n, jump);
        }
        cout << ans+1 << " ";
    }
    return 0;
}