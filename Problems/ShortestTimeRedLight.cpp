#include <iostream>
#include <bits/stdc++.h>
using namespace std;

typedef pair<long long, int> PII;
const int N = 2e5 + 7;
const long long INF = 1e18; 

long long inps[N][3];
vector<pair<int, long long>> adj[N];
int green_red_times[N][2];
long long dist[N];

void dijkstra(int n, long long dist[]){
    fill(dist, dist + N, INF);
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    dist[0] = 0;
    pq.push(PII(0, 0));
    while(!pq.empty()){
        auto cur = pq.top(); pq.pop();
        long long d = cur.first;
        int u = cur.second;
        if(d > dist[u]) 
            continue;
    for(auto e : adj[u]){
        int v = e.first;
        long long w = e.second;

        long long cycle_u = green_red_times[u][0] + green_red_times[u][1];
        long long mod_u = d % cycle_u;
        long long leave_time = d;
        if(mod_u >= green_red_times[u][0]){
            leave_time += cycle_u - mod_u; 
        }

        long long arrival_time = leave_time + w;

        if(dist[v] > arrival_time){
            dist[v] = arrival_time;
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
    for(int i = 0; i < n; i++){
        cin >> green_red_times[i][0] >> green_red_times[i][1];
    }

    for(int i = 0; i < m; i++){
        int u = inps[i][0], v = inps[i][1];
        long long w = inps[i][2];
        u--; v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    dijkstra(n, dist);
    cout << dist[n - 1] << "\n";

    return 0;
}