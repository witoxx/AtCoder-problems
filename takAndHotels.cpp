#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, l, q;
    cin >> n;
    vector<int> x(n+1);
    for(int i = 1; i <= n; i++) cin >> x[i];
    cin >> l >> q;
    
    vector<vector<int>> jump(20, vector<int> (n+2, n+1));
    long long id = 1, sum = 0;
    for(int i = 2; i <= n; i++) {
        sum += x[i]-x[i-1];
        while(sum > l) {
            jump[0][id] = i-1;
            sum -= (x[id+1]-x[id]);
            id++;
        }
    }
    for(int i = 1; i < 20; i++) {
        for(int j = 1; j < n; j++)
            jump[i][j] = jump[i-1][jump[i-1][j]];
    }

    while(q--) {
        int a, b, ans = 0;
        cin >> a >> b;
        if(a > b) swap(a, b);
        for(int i = 19; i >= 0; i--) {
            if(jump[i][a] < b) {
                a = jump[i][a];
                ans += (1<<i);
            }
            if(jump[i][a] == b) {
                ans += (1<<i);
                break;
            }
            if(i == 0 && jump[i][a] > b) ans++;
        }
        cout << ans << "\n";
    }
    return 0;
}