#include <bits/stdc++.h>
using namespace std;
#define st first
#define nd second

int n;
vector<pair<int, int>> inv;
vector<vector<int>> nim;

int grundy(int l, int r) {
    if(nim[l][r] != -1) return nim[l][r];
    vector<bool> mex(100, false);
    for(int i = 0; i < n; i++) {
        if(inv[i].st >= l && inv[i].nd <= r) {
            int left = 0, right = 0;
            if(l < inv[i].st) left = grundy(l, inv[i].st);
            if(r > inv[i].nd) right = grundy(inv[i].nd, r);            
            mex[left ^ right] = true;
        }
    }
    for(int i = 0; ; i++) {
        if(!mex[i]) {
            nim[l][r] = i;
            break;
        }
    }
    return nim[l][r];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        cin >> n;
        nim.assign(101, vector<int> (101, -1));
        inv.assign(n, {0, 0});
        for(int i = 0; i < n; i++)
            cin >> inv[i].st >> inv[i].nd;
        cout << (grundy(1, 100) ? "Alice\n" : "Bob\n");
    }
    return 0;
}