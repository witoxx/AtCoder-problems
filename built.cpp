#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define st first
#define nd second

struct node {
    ll a, b, w;
};

bool comp(node n1, node n2) {
    return n1.w < n2.w;
}

vector<ll> par, siz;

ll Find(ll v) {
    if(v == par[v]) return v;
    return par[v] = Find(par[v]);
}

void Union(ll a, ll b) {
    a = Find(a);
    b = Find(b);
    if(a == b) return;
    if(siz[a] > siz[b]) swap(a, b);
    siz[b] += siz[a];
    par[a] = par[b];
}

ll kruskal(vector<node> &edge, ll &n) {
    par.resize(n+1);
    siz.assign(n+1, 1);
    ll res = 0;
    for(ll i = 1; i <= n; i++) par[i] = i;
    for(auto e : edge) {
        ll a = Find(e.a);
        ll b = Find(e.b);
        if(a != b) {
            Union(a, b);
            res += e.w;
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n;
    cin >> n;
    vector<pair<ll, ll>> gx, gy;
    for(ll i = 1; i <= n; i++) {
        ll x, y;
        cin >> x >> y;
        gx.push_back({x, i});
        gy.push_back({y, i});
    }
    sort(gx.begin(), gx.end());
    sort(gy.begin(), gy.end());
    vector<node> edge;
    for(ll i = 1; i < n; i++) {
        node N;
        N.a = gx[i-1].nd; N.b = gx[i].nd;
        N.w = gx[i].st - gx[i-1].st;
        edge.push_back(N);
        N.a = gy[i-1].nd; N.b = gy[i].nd;
        N.w = gy[i].st - gy[i-1].st;
        edge.push_back(N);
    }

    sort(edge.begin(), edge.end(), comp);
    ll ans = kruskal(edge, n);
    cout << ans << "\n";
    return 0;
}