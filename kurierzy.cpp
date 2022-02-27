#include <bits/stdc++.h>
using namespace std;
#define st first
#define nd second

constexpr int H = 19, N = (1<<H);  
vector<pair<int, int>> tree(2*N, {0, 0});

pair<int, int> dominant(pair<int, int> &one, pair<int, int> &two) {
    if(one.st == two.st)
        return {one.st, one.nd + two.nd};
    else if(one.nd > two.nd)
        return {one.st, one.nd - two.nd};
    else if(one.nd < two.nd)
        return {two.st, two.nd - one.nd};
    else return {0, 0};
}

void build(int &n, vector<int> &p) {
    for(int i = N; i < N+n; i++) tree[i] = {p[i-N+1], 1};
    for(int i = H-1; i >= 0; i--) {
        for(int j = (1<<i); j < (1<<(i+1)); j++)
            tree[j] = dominant(tree[j*2], tree[j*2+1]);
    }
}

int query(int l, int r) {
    l += N-1; r += N;
    pair<int, int> dom = {0, 0};
    while(l < r) {
        if(l&1) {
            dom = dominant(dom, tree[l]);
            l++;
        }
        if(r&1) {
            r--;
            dom = dominant(dom, tree[r]);
        } 
        l /= 2; r /= 2;
    }
    return dom.st;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> p(n+1);
    for(int i = 1; i <= n; i++) cin >> p[i];
    build(n, p);

    vector<int> can(m), seg_len(m);
    vector<pair<int, pair<bool, int>>> q(2*m);
    for(int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        seg_len[i] = r-l+1;
        can[i] = query(l, r);
        q[i*2] = {l, {0, i}};
        q[i*2+1] = {r, {1, i}};
    }

    sort(q.begin(), q.end());
    vector<int> occ(n+1, 0), num(m, 0), ans(m);
    int j = 0;
    for(int i = 1; i <= n; i++) {
        occ[p[i]]++;
        while(q[j].st == i) {
            int x = q[j].nd.nd;
            if(!q[j].nd.st) {
                occ[p[i]]--;
                num[x] = occ[can[x]];
                occ[p[i]]++;
            }
            else {
                if(occ[can[x]] - num[x] > seg_len[x]/2) ans[x] = can[x];
                else ans[x] = 0;
            }
            j++;
        }
    }
    for(auto i : ans) cout << i << "\n";
    return 0;
}