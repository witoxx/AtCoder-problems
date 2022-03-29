#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> red(n+1, 0);
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        red[a]++; red[b]++;
    }
    int all = n*(n-1)*(n-2)/6, dif = 0;
    for(int i = 1; i <= n; i++)
        dif += red[i] * (n-red[i]-1);
    int ans = all - dif/2;
    cout << ans << "\n";
    return 0;
}