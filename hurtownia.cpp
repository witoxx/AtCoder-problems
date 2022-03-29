#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define st first
#define nd second

constexpr ll H = 18, N = (1<<H);
vector<ll> tree(2*N, 0), tree2(2*N, -1);


void update(ll v, ll val) {
    v += N-1;
    tree[v] = val;
    while(v > 1) {
        v /= 2;
        tree[v] = tree[v*2]+tree[v*2+1];
    }
}

ll query(ll l, ll r) {
    l += N-1; r += N;
    ll res = 0;
    while(l < r) {
        if(l&1) res += tree[l], l++;
        if(r&1) r--, res += tree[r];
        l /= 2; r /= 2; 
    }
    return res;
}

void update2(ll v, ll pos) {
    v += N-1;
    tree2[v] = pos;
    while(v > 1) {
        v /= 2;
        tree2[v] = max(tree2[v*2], tree2[v*2+1]);
    }
}

ll query2(ll l, ll r) {
    l += N-1; r += N;
    ll res = 0;
    while(l < r) {
        if(l&1) res = max(res, tree2[l]), l++;
        if(r&1) r--, res = max(res, tree2[r]);
        l /= 2; r /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n;
    cin >> n;
    for(ll i = 1; i <= n; i++) {
        ll a;
        cin >> a;
        update(i, a);
        update2(i, i);
    }
    vector<pair<ll, ll>> b(n);
    for(ll i = 0; i < n; i++) {
        ll x;
        cin >> x;
        b[i] = {x, i+1};
    }

    // for(auto i : tree) cout << i << " ";
    // cout << "\n";

    sort(b.begin(), b.end());
    vector<ll> ans;
    for(auto i : b) {
        ll sum = query(1, i.nd);
        if(sum < i.st) continue;
        ll pos = query2(1, i.nd), a = tree[pos+N-1];
        while(i.st > 0 && i.st >= a) {
            update(pos, 0);
            update2(pos, -1);
            i.st -= a;
            pos = query2(1, pos-1);
            a = tree[pos+N-1];
        }
        if(i.st > 0) update(pos, a-i.st);
        ans.push_back(i.nd);
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for(auto i : ans) cout << i << " ";
    cout << "\n";
    return 0;
}