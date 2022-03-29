#include <bits/stdc++.h>
using namespace std;
#define st first
#define nd second

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    srand(4567898);
    long long n, m;
    cin >> n >> m;
    vector<vector<int>> a(n);
    vector<int> w(n);
    map<int,long long> mp;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
           long long x;
            cin >> x;
            a[i].push_back(x);
            mp[x] = 1;
        }
        cin >> w[i];
    }
   long long val = 1;
    for(auto& i : mp) i.nd = val, val++;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            a[i][j] = mp[a[i][j]];
    }

   long long INF = 2e9 + 5, C = 20;
   long long ans = INF;
    vector<int> num(val+2);
    while(clock() <= 2.7 * CLOCKS_PER_SEC)  {
        vector<int> dp((1<<C)+1, INF);
        for(int j = 1; j <= val; j++) num[j] = rand() % C;
        for(int j = 0; j < n; j++) {
           long long mask = 0;
            for(auto k : a[j])
                mask |= (1<<num[k]);
            dp[mask] = min(dp[mask], w[j]);
        }
        for(int j = 0; j < C; j++) {
            for(int mask = 0; mask < (1<<C); mask++) {
                if(mask&(1<<j))
                    dp[mask] = min(dp[mask], dp[mask^(1<<j)]);
            }
        }
        for(int mask = 0; mask < (1<<C); mask++)
            ans = min(ans, (long long) dp[mask]+dp[mask^((1<<C)-1)]);
    }
    if(ans < INF) cout << ans << "\n";
    else cout << "-1\n";
    return 0;
}
