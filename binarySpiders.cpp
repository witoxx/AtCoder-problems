#include <bits/stdc++.h>
using namespace std;
#define st first
#define nd second

int mostSignificant(int k) {
    int pos = 0;
    while(k > 1) {
        k /= 2;
        pos++;
    }
    return pos;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    vector<int> a(n+1);
    map<int, int> pos;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(pos.find(a[i]) == pos.end())
            pos.insert({a[i], i});
    }

    if(k == 0) {
        cout << n << "\n";
        for(int i = 1; i <= n; i++) cout << i << " ";
        cout << "\n";
        return 0;
    }

    int suf = mostSignificant(k), fac = 1<<suf, ID = -1;
    map<int, int> mp;
    vector<vector<int>> v(n);
    for(int i = 1; i <= n; i++) {
        int x = a[i]/fac;
        if(mp.find(x) == mp.end()) {
            ID++;
            mp.insert({x, ID});
            v[ID].push_back(a[i]);
        }
        else v[mp.find(x)->nd].push_back(a[i]);
    }
    
    vector<int> ans;
    for(auto i : v) {
        if(i.empty()) continue;
        int x = i[0]/fac;
        if(x%2 == 0) {
            if(mp.find(x+1) == mp.end())
                ans.push_back(i[0]);
            else {
                int siz = 1;
                vector<vector<int>> trie(i.size()*(suf+2), vector<int> (2, -1));
                for(auto j : i) {
                    vector<int> bin(suf, 0);
                    int id = suf-1, y = j%fac;
                    while(y >= 1) {
                        bin[id] = y%2;
                        y /= 2; id--;
                    }
                    id = 0;
                    for(auto m : bin) {
                        if(trie[id][m] == -1) {
                            trie[id][m] = siz;
                            id = siz; siz++;
                        }
                        else id = trie[id][m];
                    }
                }

                int i1 = mp.find(x+1)->nd;
                int res = k%fac;
                bool added = false;
                for(auto j : v[i1]) {
                    int id = suf-1, y = j%fac;
                    vector<int> bin(suf, 0);
                    while(y >= 1) {
                        bin[id] = y%2;
                        y /= 2; id--;
                    }

                    id = 0;
                    int need = res, p = suf-1, two = 0;
                    for(auto m : bin) {
                        if(trie[id][m^1] != -1) {
                            need -= (1<<p);
                            id = trie[id][m^1];
                            two += (m^1)*(1<<p);
                        }
                        else {
                            id = trie[id][m];
                            two += m*(1<<p);
                        }
                        p--;
                    }
                    if(need <= 0) {
                        ans.push_back(x*(1<<suf) + two);
                        ans.push_back(j);
                        added = true;
                        break;
                    }
                }
                if(!added) ans.push_back(i[0]);
            }
        }
        else if (mp.find(x-1) == mp.end())
            ans.push_back(i[0]); 
    }
    if((int) ans.size() <= 1) cout << "-1\n";
    else {
        cout << ans.size() << "\n";
        for(auto i : ans)
            cout << pos.find(i)->nd << " ";
        cout << "\n";
    }
    return 0;
}