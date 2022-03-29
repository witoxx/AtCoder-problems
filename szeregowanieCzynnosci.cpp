#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<pair<double, int>> v(n);
    for(int i = 0; i < n; i++) {
        double a, b;
        cin >> a >> b;
        v[i] = {b/a, i+1};
    }
    sort(v.begin(), v.end());
    for(auto i : v) cout << i.second << "\n";
    return 0;
}