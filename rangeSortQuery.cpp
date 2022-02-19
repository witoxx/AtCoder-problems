#include <bits/stdc++.h>
using namespace std;
#define st first
#define nd second

const int h = 18, base = 1 << h;
int xpos;
vector<int> tree(2*base, 0);
vector<pair<int, int>> p(2*base, {-1, -1});

void update(int v, int a, int b, int strt, int end, int s, int val) {
    if(strt > b || end < a) return;
    else if(strt >= a && end <= b) {
        tree[v] = val;
        p[v] = {val, s};
    }
    else {
        int l = v<<1, r = (v<<1)+1, mid = (strt+end)>>1;
        int v1, v2;
        if(s == 1) {
            v1 = min(min(val, (end-strt+1)/2), max(0, mid-a+1));
            v2 = val - v1;
        }
        else {
            v2 = min(min(val, (end-strt+1)/2), max(0, b-mid));
            v1 = val - v2;
        }
        update(l, a, b, strt, mid, s, v1);
        update(r, a, b, mid+1, end, s, v2);
        tree[v] = tree[l] + tree[r];
    }
}

int query(int v, int a, int b, int strt, int end) {
    if(strt > b || end < a) return 0;
    else if(strt >= a && end <= b) return tree[v];
    else {
        int l = v<<1, r = (v<<1)+1, mid = (strt+end)>>1;
        if(p[v].st != -1 && p[v].nd == 1) {
            tree[l] = min(p[v].st, (end-strt+1)/2);
            tree[r] = p[v].st - tree[l]; 
            p[l] = {tree[l], 1};
            p[r] = {tree[r], 1};
            p[v] = {-1, -1};
        }
        else if(p[v].st != -1 && p[v].nd == 2) {
            tree[r] = min(p[v].st, (end-strt+1)/2);
            tree[l] = p[v].st - tree[r];
            p[r] = {tree[r], 2};
            p[l] = {tree[l], 2};
            p[v] = {-1, -1};
        }
        return query(l, a, b, strt, mid) + query(r, a, b, mid+1, end);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q, x;
    cin >> n >> q >> x;
    for(int i = base; i < base+n; i++) {
        int y;
        cin >> y;
        if(y == x) xpos = i-base+1;
        if(y < x) {
            int j = i;
            while(j >= 1) {
                tree[j]++;
                j /= 2;
            }
        }
    }

    while(q--) {
        int c, l, r;
        cin >> c >> l >> r;
        int value = query(1, l, r, 1, base);
        if(l <= xpos && xpos <= r) {
            if(c == 1) xpos = l+value;
            else xpos = r-value;
        }
        update(1, l, r, 1, base, c, value);
    }
    cout << xpos << "\n";
    return 0;
}