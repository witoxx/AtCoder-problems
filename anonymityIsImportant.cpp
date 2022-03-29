#include <bits/stdc++.h>
using namespace std;

constexpr int H = 18, N = (1 << H), INF = 1e9;
vector<int> tree;

void update(int l, int r) {
    l += N-1;
    while(l >= 1) {
        tree[l] = min(tree[l], r);
        l /= 2;
    }
}

int query(int l, int r) {
    l += N-1; r += N;
    int ans = INF;
    while(l < r) {
        if(l&1) ans = min(ans, tree[l]), l++;
        if(r&1) r--, ans = min(ans, tree[r]);
        l /= 2; r /= 2;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    tree.assign(2*N, INF);
    int n, q, t;
    cin >> n >> q;
    set<int> ill;
    set<int>::iterator it, it1;
    for(int i = 1; i <= n; i++) ill.insert(i);
    while(q--) {
        cin >> t;
        if(t == 0) {
            int l, r, x;
            cin >> l >> r >> x;
            if(x == 0) {
                it = ill.lower_bound(l);
                while(it != ill.end() && *it <= r) {
                    int a = *it;
                    ill.erase(a);
                    it = ill.upper_bound(a);
                }
            }
            else update(l, r);
        }
        else {
            int j, l, r;
            cin >> j;
            it = ill.find(j);
            if(it == ill.end()) cout << "NO\n";
            else {
                it1 = ill.upper_bound(j);
                if(it == ill.begin()) l = 1;
                else {
                    it--;
                    l = *it+1;
                }
                if(it1 == ill.end()) r = n+1;
                else r = *it1;
                cout << ((query(l, j) < r) ? "YES\n" : "N/A\n");
            }
        }
    }
    return 0;
}