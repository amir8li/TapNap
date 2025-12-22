#include <iostream>
#include <bits/stdc++.h>
using namespace std;

typedef pair<long long, int> PII;
const int N = 2e5 + 7;
const long long INF = 1e18; 

int inps[N][3];
bool has_ptrl_stations[N];
vector<pair<int, long long>> adj[N];
long long distS[N], distT[N];

void dijkstra(int n, int src, long long dist[]) {
    for(int i = 0; i < n; i++) 
        dist[i] = INF;
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    dist[src] = 0;
    pq.push(PII(0, src));
    while(!pq.empty()){
        auto cur = pq.top(); pq.pop();
        long long d = cur.first;
        int u = cur.second;
        if(d > dist[u]) 
            continue;
        for(auto e : adj[u]){
            int v = e.first;
            long long w = e.second;
            if(dist[v] > d + w){
                dist[v] = d + w;
                pq.push(PII(dist[v], v));
            }
        }
    }
}

int main(){
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < 3; j++)
            cin >> inps[i][j];
    }
    int k; 
    long long starting_ptrl, max_ptrl;
    cin >> k >> starting_ptrl >> max_ptrl;
    fill(has_ptrl_stations, has_ptrl_stations + N, false);
    for(int i = 0; i < k; i++){
        int tmp; cin >> tmp;
        tmp--;
        has_ptrl_stations[tmp] = true;
    }
    
    for(int i = 0; i < m; i++){
        int u = inps[i][0], v = inps[i][1];
        long long w = inps[i][2];
        u--; v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    dijkstra(n, 0, distS);
    dijkstra(n, n - 1, distT);

    long long ans = INF;

    if(distS[n - 1] <= starting_ptrl) 
        ans = min(ans, distS[n - 1]);

    for(int p = 0; p < n; p++){
        if(!has_ptrl_stations[p]) 
            continue;
        if(distS[p] <= starting_ptrl && distT[p] <= max_ptrl){
            ans = min(ans, distS[p] + distT[p]);
        }
    }

    if(ans == INF) 
        cout << "nemisarfed\n";
    else 
        cout << ans << "\n";

    return 0;
}