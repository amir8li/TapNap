#include <iostream>
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 7;
const int LOG = 22;

int up[N][LOG];
int height[N];
vector<int> adj[N];
int n, q;

int lift(int v, int k){
    for(int i = 0; i < LOG; i++){
        if((k >> i) & 1)
            v = up[v][i];
    }
    return v;
}

void get_info(){
    for(int i = 1; i < n; i++){
        int p; cin >> p;
        p--;
        up[i][0] = p;
        adj[i].push_back(p);
        adj[p].push_back(i);
    }   
    up[0][0] = n;
    up[n][0] = n;
    for(int l = 1; l < LOG; l++){
        for(int i = 0; i <= n; i++){
            up[i][l] = up[up[i][l-1]][l-1];
        }
    }
}

void dfs(int now, int par){
    up[now][0] = par;
    if(now != 0)
        height[now] = height[par] + 1;
    for(auto on : adj[now]){
        if(on != par)
            dfs(on , now);
    }
}

int lca(int u, int v){
    if(height[u] < height[v])
        swap(u, v);
    u = lift(u, height[u] - height[v]);

    if(u == v)
        return u;

    for(int l = LOG - 1; l >= 0; l--){
        if(up[u][l] != up[v][l]){
            u = up[u][l];
            v = up[v][l];
        }
    }
    return up[u][0];
}

int main(){
    cin >> n >> q;

    get_info();
    dfs(0, n);
    while(q--){
        int v, u;
        cin >> v >> u;
        v--; u--;
        cout << lca(u, v) + 1 << endl;
    }
    return 0;
}