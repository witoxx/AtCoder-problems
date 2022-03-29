#include <bits/stdc++.h>
using namespace std;

struct node {
    int l = 0, r = 0, q = 0, m = 0;
};

constexpr int H = 17, N = (1<<H);
vector<node> tree(2*N), tree1(2*N);

void modify(node &j, node t, node t1) { // do ponownego przeanalizowania
    // cout << "T: " << t.l << " " << t.r << " " << t.q << " " << t.m << "\n";
    // cout << "T1: " << t1.l << " " << t1.r << " " << t1.q << " " << t1.m << "\n";
    j.l = max(0, t.l-t1.r) + t1.l;
    j.r = max(0, t1.r-t.l) + t.r;
    int x = t.l;
    t.l = max(0, t.l-t1.r);
    t1.r = max(0, t1.r-x);

    j.r -= min(t1.r, t.q);
    j.m = min(t1.r, t.q);
    x = t1.r;
    t1.r = max(0, t1.r-t.q);
    t.q = max(0, t.q-x);

    j.m += max(0, t1.m-t.l) + t.m;
    j.l -= min(t1.m, t.l);
    t1.q += min(t.l, t1.m);
    j.q = t.q + t1.q;
}

void build(string &s, int n) {
    for(int i = 0; i < n; i++) {
        if(s[i] == '(') {
            tree[N+i].l++;
            tree1[N+i].r++;
            // cout << tree[N+i].l << " " << i << "\n";
        }
        if(s[i] == ')') {
            tree[N+i].r++;
            tree1[N+i].l++;
        }
        if(s[i] == '?') {
            tree[N+i].q++;
            tree1[N+i].q++;
        }
    }
    for(int i = H-1; i >= 0; i--) {
        for(int j = (1<<i); j < (1<<(i+1)); j++) {
            // cout << j << "\n";
            modify(tree[j], tree[j*2], tree[j*2+1]);
            modify(tree1[j], tree1[j*2+1], tree1[j*2]);
        }
    }
}

bool query(int str, int end, int ql, int qr) {
    str += N-1; end += N;
    int l = 0, r = 0, q = 0, tm;
    while(str < end) {
        if(str&1) {
            if(l < tree[str].r) return false;
            l -= tree[str].r;
            
            tm = max(0, tree[str].m-l);
            q = tree[str].q + min(tree[str].m, l);
            l = max(0, l-tree[str].m);
            if(ql < tm) return false;
            ql -= tm; tm = 0;

            if(q <= ql) l += q, ql -= q;
            else {
                l += ql; q -= ql;
                ql = 0;
                if(l < q) return false;
                l -= q; qr -= q;
            }
            q = 0;
            str++;
        }
        if(end&1 && end != str) {
            end--;
            if(l < tree1[end].r) return false;
            l -= tree1[end].r;

            tm = max(0, tree1[end].m-l);
            q = tree1[end].q + min(tree1[end].m, l);
            l = max(0, l-tree1[end].m);
            if(qr < tm) return false;
            qr -= tm; tm = 0;

            if(q <= qr) r += q, qr -= q;
            else {
                r += qr; q -= qr;
                qr = 0;
                if(r < q) return false;
                r -= q; ql -= q;
            }
            q = 0;
        }
        str /= 2; end /= 2;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, q;
    string s;
    cin >> n >> s >> q;
    build(s, n);
    vector<int> left(n+1, 0), right(n+1, 0);
    for(int i = 1; i <= n; i++) {
        left[i] = left[i-1];
        right[i] = right[i-1];
        if(s[i-1] == '(') left[i]++;
        if(s[i-1] == ')') right[i]++;
    }
    // for(auto i : left) cout << i << " ";
    // cout << "\n";
    // for(auto i : right) cout << i << " ";
    // cout << "\n"; cout << "\n";

    // for(auto i : tree)
    //     cout << i.l << " " << i.r << " " << i.q << " " << i.m << "\n";
    // cout << "\n";
    // for(auto i : tree1)
    //     cout << i.l << " " << i.r << " " << i.q << " " << i.m << "\n";

    while(q--) {
        int l, r;
        cin >> l >> r;
        int qr = (r-l+1)/2 - (right[r]-right[l-1]);
        int ql = (r-l+1)/2 - (left[r]-left[l-1]);
        // cout << "Q: " << right[r] << " " << right[l] << " " << ql << " " << qr << "\n";
        bool ans = query(l, r, ql, qr);
        if((r-l+1)%2 != 0 || qr < 0 || ql < 0) ans = false;
        cout << (ans ? "Yes\n" : "No\n");
    }
    return 0;
}