#include <iostream>
#include <bits./stdc++.h>
using namespace std;

const int N = 2e5 + 7;
const int LOG = 22;
const int INF = 1e9;

typedef pair<int, int> PII;
int up[N][LOG];
int mn[N][LOG];
int height[N];
int mx[N][LOG];
vector<PII> adj[N];

int n, q;

void precalc(){
    up[n][0] = n;
    up[0][0] = n;
    for(int i = 1; i < LOG; i++){
        for(int j = 0; j <= n; j++){
            up[j][i] = up[up[j][i-1]][i-1];
            mn[j][i] = min(mn[j][i-1], mn[up[j][i-1]][i-1]);
            mx[j][i] = max(mx[j][i-1], mx[up[j][i-1]][i-1]);
        }
    }
}

int lift(int v, int k){
    for(int i = 0; i < LOG; i++){
        if((k >> i) & 1)
            v = up[v][i];
    }
    return v;
}

PII lca(int u, int v){
    int min_res = INF;
    int max_res = -INF;
    if(height[u] < height[v])
        swap(u, v);

    for(int i = LOG - 1; i >= 0; i--){
        if(height[u] - (1<<i) >= height[v]){
            min_res = min(min_res, mn[u][i]);
            max_res = max(max_res, mx[u][i]);
            u = up[u][i];
        }
    }

    if(u == v)
        return PII(min_res, max_res);
    
    for(int l = LOG - 1; l >= 0; l--){
        if(up[u][l] != up[v][l]){
            min_res = min({min_res, mn[u][l], mn[v][l]});
            max_res = max({max_res, mx[u][l], mx[v][l]});
            u = up[u][l];
            v = up[v][l];
        }
    }
    min_res = min({min_res, mn[u][0], mn[v][0]});
    max_res = max({max_res, mx[u][0], mx[v][0]});
    return PII(min_res, max_res);
}

void dfs(int now, int par = n){
    for(auto &p : adj[now]){
        int on = p.first, wei = p.second;
        if(on != par){
            up[on][0] = now;
            mn[on][0] = wei;
            mx[on][0] = wei;
            height[on] = height[now] + 1;
            dfs(on , now);
        }
    }
}

void solve(){
    cin >> n;
    for(int i = 0; i < n; i++)
        adj[i].clear();
    for(int i = 1; i < n; i++){
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].push_back(PII(v, w));
        adj[v].push_back(PII(u, w));
    }
    dfs(0);
    precalc();
    cin >> q;
    while(q--){
        int u, v;
        cin >> u >> v;
        u--; v--;
        PII ans = lca(u, v);
        cout << ans.first << " " << ans.second << "\n";
    } 
}

int main(){
    int cases;
    cin >> cases;
    for(int i = 1; i <= cases; i++){
        cout << "Case " << i << ":"<< endl;
        solve();
    }
    return 0;
}