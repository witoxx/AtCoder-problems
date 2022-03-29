#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int sum = 0;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        sum += x;
    }
    int m;
    cin >> m;
    int sum1 = 0;
    for(int i = 0; i < m; i++) {
        int x;
        cin >> x;
        sum1 += x;
    }
    cout << sum - sum1 << "\n";
    return 0;
}