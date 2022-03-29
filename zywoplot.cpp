#include <bits/stdc++.h>
using namespace std;
#define st first
#define nd second

struct edge {
    int v, w, c;
};

bool comp(edge e1, edge e2) {
    return e1.c < e2.c;
}

vector<int> par, len, ans, ans1;
vector<edge> e;
int maxi = 0, used = 0;

int Find(int a) {
    if(par[a] == a) return a;
    return par[a] = Find(par[a]);
}

void Union(int a, int b) {
    a = Find(a);
    b = Find(b);
    if(a == b) return;
    if(len[a] > len[b]) swap(a, b);
    len[b] += len[a];
    par[a] = par[b];
}

void kruskal(int &n) {
    for(auto i : e) {
        if(Find(i.v) != Find(i.w)) {
            Union(i.v, i.w);
            if(i.c == 2) maxi--;
            used--;
            if(i.w-i.v > 1) ans1[i.v] = 1;
            else ans[i.v] = 1;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int m, n;
    cin >> m >> n;
    used = (n-1)*m + n*(m-1);
    par.resize(n*m);
    len.resize(n*m);
    ans.resize(n*m);
    ans1.resize(n*m);
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n-1; j++) {
            par[j+n*i] = j+n*i;
            par[j+1+n*i] = j+1+n*i;
            char c; cin >> c;
            edge E;
            if(c == 'C') {
                maxi++;
               E.v = j+n*i; E.w = j+1+n*i; E.c = 2;
               e.push_back(E);
            }
            else {
                E.v = j+n*i; E.w = j+1+n*i; E.c = 1;
                e.push_back(E);
            }
        }
    }
    for(int i = 0; i < m-1; i++) {
        for(int j = 0; j < n; j++) {
            char c; cin >> c;
            edge E;
            if(c == 'C') {
                maxi++;
                E.v = j+n*i; E.w = j+n*(i+1); E.c = 2;
                e.push_back(E);
            }
            else {
                E.v = j+n*i; E.w = j+n*(i+1); E.c = 1;
                e.push_back(E);
            }
        }
    }
    sort(e.begin(), e.end(), comp);
    kruskal(n);
    
    cout << used << " " << maxi << "\n";
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n-1; j++) {
            if(ans[j+i*n] == 1) cout << '.';
            else cout << 'Z';
        }
        cout << "\n";
    }
    for(int i = 0; i < m-1; i++) {
        for(int j = 0; j < n; j++) {
            if(ans1[j+n*i] == 1) cout << '.';
            else cout << 'Z';
        }
        cout << "\n";
    }
    return 0;
}
