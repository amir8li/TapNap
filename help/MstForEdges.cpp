#include <iostream>
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 7;

typedef pair<int, int> PII;
vector<PII> adj[N];
int parents[N];

int n, m;

long long primMST(int n, vector<PII> adj[]) {
    vector<bool> visited(n, false);
    priority_queue<PII, vector<PII>, greater<PII>> pq;

    long long mst_cost = 0;
    pq.push({0, 0}); 

    while(!pq.empty()) {
        PII tmp = pq.top();
        int u = tmp.first, w = tmp.second; 
        pq.pop();

        if(visited[u]) continue;
        visited[u] = true;
        mst_cost += w;

        for(auto &p : adj[u]){
            int v = p.first, weight = p.second;
            if(!visited[v]) {
                pq.push({weight, v});
            }
        }
    }
    return mst_cost;
}

void dfs(int now, int p = n){
    for(auto &p : adj[now])
}


void get_info(){
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].push_back(PII(v, w));
        adj[v].push_back(PII(u, w));
    }
    parents[0] = 0;
}

int main(){
    get_info();
    long long normal_cost = primMST(n, adj);

}