#include <iostream>
#include <bits/stdc++.h>
using namespace std;

typedef pair<long long, long long> PII;
const int N = 1000 + 7;
const long long INF = 1e18;
int inps[N][3];
vector<PII> adj[N * N];
long long dist[N * N];
int slowness [N];


int main(){
    int t;
    cin >> t;
    while(t--){
        int n, m; cin >> n >> m;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < 3; j++)
                cin >> inps[i][j];
        }

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                adj[i * N + j].clear();
            }
        }

        for(int i = 0; i < n; i++)
            cin >> slowness[i];

        for(int i = 0; i < m; i++){
            int u = inps[i][0], v = inps[i][1], w = inps[i][2];
            u--; v--;
            for(int j = 0; j < n; j++){
                adj[u * N + j].push_back(PII(v * N + j, w * slowness[j]));
                adj[v * N + j].push_back(PII(u * N + j, w * slowness[j]));
            }
        }

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                adj[i * N + j].push_back(PII(i * N + i, 0));
            }
        }

        fill(dist, dist + N*N, INF);
        dist[0] = 0;
        priority_queue<PII, vector<PII>, greater<PII>> keep;
        keep.push(PII(0, 0));

        while(!keep.empty()){
            auto tmp = keep.top();
            long long d = tmp.first; long long now = tmp.second;
            keep.pop();

            if(dist[now] != d)
                continue;

            for(auto help : adj[now]){
                long long on = help.first, wei = help.second;
                if(dist[on] > dist[now] + wei){
                    dist[on] = dist[now] + wei;
                    keep.push(PII(dist[on], on));
                }
            }

        }

        long long ans = INF;
        for(int i = 0; i < n; i++){
            ans = min(ans, dist[(n - 1) * N + i]);
        }

        cout << ans << "\n";
}

    return 0;
}