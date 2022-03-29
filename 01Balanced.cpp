#include <bits/stdc++.h>
using namespace std;
#define st first
#define nd second

constexpr int H = 5, N = (1<<H);
vector<int> tree(2*N, 0);

void update(int v) {
    v += N-1;
    while(v > 1) tree[v]++, v /= 2;
}

int query(int l, int r) {
    l += N-1; r += N;
    int res = 0;
    while(l < r) {
        if(l&1) res += tree[l], l++;
        if(r&1) r--, res += tree[r];
        l /= 2; r /= 2;
    }
    return res;
}

bool order(const pair<int, int> &a, const pair<int, int> &b) {
    if(a.first != b.first)
        return a.first < b.first;
    else 
        return a.second > b.second;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> con(m);
    for(int i = 0; i < m; i++)
        cin >> con[i].nd >> con[i].st;
    sort(con.begin(), con.end(), order);
    for(auto i : con) cout << i.nd << "," << i.st << "\n";
    vector<int> ans(n+1, 0);
    set<int> used;
    for(int i = 1; i <= n; i++) used.insert(i);
    cout << "\n\n";
    for(auto i : con) {
        cout << i.nd << " " << i.st << "  ";
        int pos, zeros = (i.st-i.nd+1)/2 - query(i.nd, i.st);
        cout << zeros << " ";
        while(zeros > 0) {
            pos = *used.lower_bound(i.nd);
            cout << pos << " ";
            used.erase(pos);
            update(pos);
            zeros--;
        }
        cout << "\n P: ";
        set<int>::iterator it = used.lower_bound(i.nd);
        while(it != used.end() && *it <= i.st) {
            cout << pos << " ";
            used.erase(*it);
            ans[*it] = 1;
            it = used.lower_bound(i.nd);
        }
        cout << "\n";
        for(int j = 1; j <= n; j++) cout << ans[j] << " ";
        cout << "\n";
    }
    for(int i = 1; i <= n; i++) cout << ans[i];
    cout << "\n";
    return 0;
}