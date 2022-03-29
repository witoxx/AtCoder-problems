#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<int> v(2*n), ans;
    stack<int> d, u;
    for(int i = 0; i < 2*n; i++) {
        int x; cin >> x;
        v[i] = x;
    }
    for(int i = 2*n-1; i >= 0; i--)
        u.push(v[i]);

    vector<bool> used(n+1, false);
    int len = 0, len1 = 2*n;
    while(!u.empty()) {
        int x = u.top();
        u.pop(); len1--;
        if(!used[x]) {
            d.push(x), len++;
            used[x] = true;
        }
        else {
            while(d.top() != x) {
                ans.push_back(len);
                u.push(d.top());
                used[d.top()] = false;
                d.pop();
                len--; len1++;
            }
            d.pop(); len--;
        }
    }

    cout << ans.size() << "\n";
    for(auto i : ans) cout << i << "\n";
    return 0;
}