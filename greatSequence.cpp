#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        ll n, x;
        cin >> n >> x;
        vector<ll> a(n);
        map<ll, ll> m;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            if(m.find(a[i]) != m.end()) m[a[i]]++;
            else m[a[i]] = 1;
        }

        sort(a.begin(), a.end());
        int ans = 0;
        for(auto i : a) {
            if(m.find(i) == m.end()) continue;
            if(m.find(i*x) != m.end()) {
                m[i*x]--;
                if(m[i*x] == 0) m.erase(i*x);
            }
            else ans++;
            m[i]--;
            if(m[i] == 0) m.erase(i);
        }
        cout << ans << "\n";
    }
    return 0;
}