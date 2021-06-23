#include <bits/stdc++.h>

using namespace std;

struct DirectedGraph {
    using len_type = long long;
    const len_type INF = 1e18;
    using pr = pair<len_type, int>;
    vector<vector<pr> > e;
    vector<len_type> dis;
    int N;
    DirectedGraph(){}
    DirectedGraph(int _N) : N(_N) {
        e.assign(N + 1, vector<pr>());
    }
    // directed edge
    void add_edge(int u, int v, len_type w = 1) {
        e[u].push_back(pr(w, v));
    }
    void bfs(int S) {
        dis.assign(N + 1, INF);
        queue<int> q;
        q.push(S);
        dis[S] = 0;
        while(!q.empty()) {
            int now = q.front();
            q.pop();
            for (auto &t : e[now]) {
                if (dis[t.second] == INF) {
                    dis[t.second] = dis[now] + 1;
                    q.push(t.second);
                }
            }
        }
    }
    int farthest(int x) {
        bfs(x);
        return max_element(dis.begin() + 1, dis.begin() + N + 1) - dis.begin();
    }
};

int main() {
    int n, m;
    scanf("%d%d",&n,&m);
    DirectedGraph G(n);
    while(m--) {
        int u, v;
        scanf("%d%d",&u,&v);
        G.add_edge(u, v);
        G.add_edge(v, u);
    }
    for (int i = 1; i <= n; i++) {
        printf("%d %d\n",i,G.farthest(i));
    }
}