#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define st first
#define nd second

constexpr ll H = 18, N = (1<<H);
vector<ll> tree(2*N, 0), tree2(2*N, 0);

void push(ll v) {
    tree[2*v] += tree2[v];
    tree2[2*v] += tree2[v];
    tree[2*v+1] += tree2[v];
    tree2[2*v+1] += tree2[v];
    tree2[v] = 0;
}

void update(ll v, ll a, ll b, ll l, ll r, ll val) {
    if(a > r || b < l) return;
    else if(a >= l && b <= r) {
        tree[v] += val;
        tree2[v] += val;
        return;
    }
    else {
        ll mid = (a+b)/2;
        push(v);
        update(2*v, a, mid, l, r, val);
        update(2*v+1, mid+1, b, l, r, val);
        tree[v] = max(tree[2*v], tree[2*v+1]);
    }
}

ll query(ll v, ll a, ll b, ll l, ll r) {
    if(a > r || b < l) return 0;
    else if(a >= l && b <= r) return tree[v];
    else {
        ll mid = (a+b)/2;
        push(v);
        return max(query(2*v, a, mid, l, r), query(2*v+1, mid+1, b, l, r)); 
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n, m;
    cin >> n >> m;
    vector<ll> cost(n+1);
    for(int i = 1; i <= n; i++) cin >> cost[i];
    vector<vector<pair<ll, ll>>> race(n+1);
    for(int i = 0; i < m; i++) {
        ll l, r, p;
        cin >> l >> r >> p;
        race[r].push_back({l, p}); 
    }

    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        update(1, 1, N, 1, i, -cost[i]);
        for(auto j : race[i])
            update(1, 1, N, 1, j.st, j.nd);
        ll maxi = query(1, 1, N, 1, i);
        ans = max(ans, maxi);
        update(1, 1, N, i+1, i+1, ans);
    }
    cout << ans << "\n";
    return 0;
}