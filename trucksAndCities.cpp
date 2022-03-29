#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct truck {
    ll s, f, c, r;
};

bool enoughFuel(ll &V, truck t, vector<ll> &dis) {
    ll fuel = V;
    while(t.s < t.f && t.r >= 0) {
        if(dis[t.s+1] - dis[t.s] > fuel/t.c) {
            if(t.r > 0) {
                t.r--;
                fuel = V;
            }
            else if(t.r <= 0 || fuel == V) return false;
        }
        else {
            fuel -= (dis[t.s+1] - dis[t.s])*t.c;
            t.s++;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937 rng(seed);

    ll n, m;
    cin >> n >> m;
    vector<ll> dis(n+1);
    for(int i = 1; i <= n; i++) cin >> dis[i];
    vector<truck> query(m);
    for(int i = 0; i < m; i++) {
        ll s, f, c, r;
        cin >> s >> f >> c >> r;
        query[i].s = s;
        query[i].f = f;
        query[i].c = c;
        query[i].r = r;
    }
    shuffle(query.begin(), query.end(), rng);
    ll V = 1;
    for(auto i : query) {
        if(enoughFuel(V, i, dis)) continue;
        ll l = V+1, r = LLONG_MAX, mid;
        while(l <= r) {
            mid = (l+r)/2;
            if(enoughFuel(mid, i, dis)) {
                r = mid-1;
                V = mid;
            }
            else l = mid+1;
        }
    }
    cout << V << "\n";
    return 0;
}