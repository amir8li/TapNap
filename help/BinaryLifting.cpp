#include <iostream>
using namespace std;

const int N = 2e5 + 7;
const int LOG = 22;

int up[N][LOG];

int lift(int v, int k){
    for(int i = 0; i < LOG; i++){
        if((k >> i) & 1)
            v = up[v][i];
    }
    return v;
}

int main(){
    int n, q;
    cin >> n >> q;
    for(int i = 1; i < n; i++){
        int p; cin >> p;
        p--;
        up[i][0] = p;
    }   
    up[0][0] = n;
    up[n][0] = n;
    for(int l = 1; l < LOG; l++){
        for(int i = 0; i <= n; i++){
            up[i][l] = up[up[i][l-1]][l-1];
        }
    }

    while(q--){
        int v, k;
        cin >> v >> k;
        v--;
        if(lift(v, k) == n)
            cout << -1 << endl;
        else
            cout << (lift(v, k) + 1) << endl;
    }

    return 0;
}