#include <bits/stdc++.h>
#include "ckollib.h"
using namespace std;

int main() {
    int x;
    pair<int, int> one = {-1, -1}, two = {-1, -1};
    vector<int> bin(31, 0);
    do {
        x = karta();
        if(x == 0) break;
        if(x == one.first) one.second++;
        else if(x == two.first) two.second++;
        if(one.first == -1) one = {x, 1};
        else if(two.first == -1 && x != one.first) two = {x, 1};
        int id = 0;
        while(x > 0) {
            if(x%2 == 1) bin[id]++;
            x /= 2; id++;
        }
    } while(true);

    if(two.first == -1) odpowiedz(one.first);
    else if(one.second < two.second) odpowiedz(one.first);
    else if(two.second < one.second) odpowiedz(two.first);
    else {
        int ans = 0;
        for(int i = 0; i < 31; i++) {
            if(bin[i]%one.second != 0)
                ans += 1<<i;
        }
        odpowiedz(ans);
    }
    return 0;
}
