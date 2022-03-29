#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

constexpr ll H = 18, N = (1<<H);
vector<ll> tree(2*N, 0);

void update(ll v) {
    v += N;
    while(v >= 1) tree[v]++, v /= 2;
}

ll query(ll l, ll r) {
    l += N; r += N+1;
    ll ans = 0;
    while(l < r) {
        if(l&1) ans += tree[l], l++;
        if(r&1) r--, ans += tree[r];
        l /= 2; r /= 2;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;
    ll n = s.size(), odd = 0, oddPos = -1;
    vector<vector<ll>> pos(26);
    for(ll i = 0; i < n; i++)
        pos[s[i] - 'a'].push_back(i);
    for(int i = 0; i < 26; i++) {
        if(((ll) pos[i].size()) % 2 == 1) {
            odd++;
            oddPos = pos[i][((int) pos[i].size())/2];
        }
    }
    if(odd > 1) {
        cout << "-1\n";
        return 0;
    }
    ll id = 0;
    vector<ll> num(n, -1);
    for(ll i = 0; i < n; i++) {
        if(num[i] != -1) continue;
        if(i == oddPos) {
            num[i] = n/2;
            continue;
        }
        num[i] = id;
        ll pair = pos[s[i] - 'a'].back();
        if(num[pair] == -1) {
            num[pair] = n-id-1;
            pos[s[i] - 'a'].pop_back();
        }
        id++;
    }
    ll res = 0;
    for(auto i : num) {
        update(i);
        res += query(i+1, n-1);
    }
    cout << res << "\n";
    return 0;
}