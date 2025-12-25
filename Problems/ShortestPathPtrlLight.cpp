#include <iostream>
#include <bits/stdc++.h>
using namespace std;

typedef pair<long long, int> PII;
const int N = 2e5 + 7;
const long long INF = 1e18; 

int inps[N][3];
vector<pair<int, int>> adj[N * 2];
int green_red_times[N][2];
long long dist[N * 2];
bool has_gas[N];


void dijkstra(int n, int src){
    fill(dist, dist + N * 2, INF);
    priority_queue<PII, vector<PII>, greater<PII>> keep;
    dist[src] = 0;
    keep.push(PII(0, src));
    while(!keep.empty()){
        auto curr = keep.top();
        keep.pop();
        long long d = curr.first, u = curr.second;
        if(d != dist[u])
            continue;
        for(auto e: adj[u]){
            int v = e.first;
            long long w = e.second;

            long long cycle = green_red_times[u / 2][0] + green_red_times[u / 2][1];
            long long wait = 0;
            if (d % cycle >= green_red_times[u / 2][0]) {
                wait = cycle - (d % cycle);
            }

            long long nd = d + wait + w;  
            if (dist[v] > nd) {
                dist[v] = nd;
                keep.push({nd, v});
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
    int k; cin >> k;
    fill(has_gas, has_gas + N, false);
    for(int i = 0; i < k; i++){
        int tmp;
        cin >> tmp;
        has_gas[--tmp] = true;
    }
    for(int i = 0; i < n; i++){
        cin >> green_red_times[i][0] >> green_red_times[i][1];
    }

    for(int i = 0; i < m; i++){
        int u = inps[i][0], v = inps[i][1];
        int w = inps[i][2];
        u--; v--;

        if(has_gas[v])
            adj[u*2+0].push_back({v*2+1, w}); 
        else
            adj[u*2+0].push_back({v*2+0, w}); 

        adj[u*2+1].push_back({v*2+1, w}); 

        if(has_gas[u])
            adj[v*2+0].push_back({u*2+1, w});
        else
            adj[v*2+0].push_back({u*2+0, w});
        
        adj[v*2+1].push_back({u*2+1, w});

    }

    if(has_gas[0]){
        dijkstra(n, 0 * 2 + 1);
    } 
    else {
        dijkstra(n, 0 * 2 + 0);
    }

    cout << dist[(n - 1) * 2 + 1] << endl;

    return 0;
}