#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 7;
const int LOG = 22;
const int INF = 1e9 + 7;

typedef pair<int,int> PII;

int n, m;
vector<PII> adj[N];
vector<PII> adj_MST[N];
int up[N][LOG];
int mn[N][LOG];
int height[N];
int comp[N];

void primMaxST(int n){
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    vector<int> key(n, -INF);
    priority_queue<PII> pq;
    for(int start = 0; start < n; ++start){
        if(visited[start]) continue;
        key[start] = INF;
        pq.push({key[start], start});
        while(!pq.empty()){
            auto temp = pq.top();
            int w = temp.first;
            int u = temp.second;
            pq.pop();
            if(visited[u]) continue;
            visited[u] = true;
            if(parent[u] != -1){
                int p = parent[u];
                adj_MST[u].push_back({p, key[u]});
                adj_MST[p].push_back({u, key[u]});
            }
            for(const auto &e : adj[u]){
                int v = e.first, weight = e.second;
                if(!visited[v] && weight > key[v]){
                    key[v] = weight;
                    parent[v] = u;
                    pq.push({key[v], v});
                }
            }
        }
    }
}

void dfs(int now, int par, int cid){
    comp[now] = cid;
    up[now][0] = par;
    if(par == -1){
        mn[now][0] = INF;
        height[now] = 0;
    }
    for(const auto &p : adj_MST[now]){
        int on = p.first, wei = p.second;
        if(on == par) continue;
        mn[on][0] = wei;
        height[on] = height[now] + 1;
        dfs(on, now, cid);
    }
}

void precalc(){
    for(int i = 1; i < LOG; i++){
        for(int j = 0; j < n; j++){
            int mid = up[j][i-1];
            if(mid == -1){
                up[j][i] = -1;
                mn[j][i] = INF;
            } else {
                up[j][i] = up[mid][i-1];
                mn[j][i] = min(mn[j][i-1], mn[mid][i-1]);
            }
        }
    }
}

int lca(int u, int v){
    if(u == v) return INF;
    int min_res = INF;
    if(height[u] < height[v]) swap(u, v);
    int diff = height[u] - height[v];
    for(int i = LOG - 1; i >= 0; i--){
        if((diff >> i) & 1){
            min_res = min(min_res, mn[u][i]);
            u = up[u][i];
        }
    }
    if(u == v) return min_res;
    for(int i = LOG - 1; i >= 0; i--){
        if(up[u][i] != up[v][i]){
            min_res = min(min_res, mn[u][i]);
            min_res = min(min_res, mn[v][i]);
            u = up[u][i];
            v = up[v][i];
        }
    }
    min_res = min(min_res, mn[u][0]);
    min_res = min(min_res, mn[v][0]);
    return min_res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < LOG; ++j){
            up[i][j] = -1;
            mn[i][j] = INF;
        }
        comp[i] = -1;
        height[i] = 0;
    }
    primMaxST(n);
    int cid = 0;
    for(int i = 0; i < n; ++i){
        if(comp[i] == -1) dfs(i, -1, cid++);
    }
    precalc();

    int q; cin >> q;
    multiset<int> trucks;
    while(q--){
        int option; cin >> option;
        if(option == 1){
            int in; cin >> in;
            trucks.insert(in);
        } else if(option == 2){
            int out; cin >> out;
            auto it = trucks.find(out);
            if(it != trucks.end()) trucks.erase(it);
        } else {
            int u, v; cin >> u >> v;
            u--; v--;
            if(comp[u] != comp[v]){
                cout << -1 << '\n';
            } else {
                int cap = lca(u, v);
                if(cap == INF){
                    if(trucks.empty()) cout << -1 << '\n';
                    else cout << *prev(trucks.end()) << '\n';
                } 
                else{
                    auto it = trucks.upper_bound(cap);
                    if(it == trucks.begin()) 
                        cout << -1 << '\n';
                    else { 
                        --it; 
                        cout << *it << '\n'; 
                    }
                }
            }
        }
    }
    return 0;
}