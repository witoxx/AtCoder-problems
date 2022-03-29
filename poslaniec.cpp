#include <bits/stdc++.h>
using namespace std;
#define st first
#define nd second

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, z, q;
    cin >> n >> m >> z;
    vector<vector<int>> g(n+1);
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    cin >> q;
    vector<vector<int>> dp;
    while(q--) {
        int s, e, d;
        cin >> s >> e >> d;
        dp.assign(n+1, vector<int> (d+1, 0));
        dp[s][0] = 1;
        for(int i = 0; i < d; i++) {
            for(int j = 1; j <= n; j++) {
                for(auto w : g[j]) {
                    if(w != s && (w != e || i == d-1))
                        dp[w][i+1] = (dp[w][i+1] + dp[j][i]) % z;
                }
            }
        }
        cout << dp[e][d] << "\n";
    }
    return 0;
}