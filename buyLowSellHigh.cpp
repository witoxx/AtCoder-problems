#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define st first
#define nd second


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<ll> p(n);
    for(int i = 0; i < n; i++) cin >> p[i];
    priority_queue<pair<ll, bool>, vector<pair<ll, bool>>, greater<pair<ll, bool>>> pq;
    pq.push({p[0], false});
    ll ans = 0;
    for(int i = 1; i < n; i++) {
        if(pq.empty()) {
            pq.push({p[i], false});
            continue;
        }
        ll mini = pq.top().st;
        bool used = pq.top().nd;
        if(p[i] <= mini)
            pq.push({p[i], false});
        else {
            pq.pop();
            ans += p[i]-mini;
            pq.push({p[i], true});
            if(used)
                pq.push({mini, false});
        }
    }
    cout << ans << "\n";
    return 0;
}