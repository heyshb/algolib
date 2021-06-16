#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
// 1-base
class SSSPGraph {
public:
    typedef LL len_type;
    const len_type INF = 1e18;
    typedef pair<len_type, int> pr;
    int n, m, S;
    vector<vector<pr> > e;
    vector<len_type> dis;

    void init(int _n) {
        e.clear();
        e.resize(_n + 1);
        dis.clear();
        dis.assign(_n + 1, INF);
    }
    SSSPGraph(){}
    SSSPGraph(int _n, int _m, int _S = 1) : n(_n), m(_m), S(_S) {
        init(_n);
    }
    void add_edge(int u, int v, len_type w) {
        e[u].push_back(pr(w, v));
    }
    void dijkstra() {
        priority_queue<pr, vector<pr>, greater<pr> > hp;
        vector<int> vis(n + 1, 0);
        hp.emplace(0, S);
        dis[S] = 0;
        while(!hp.empty()) {
            auto p = hp.top();
            hp.pop();
            if (vis[p.second]) continue;
            dis[p.second] = p.first;
            for (auto &t : e[p.second]) {
                hp.emplace(p.first + t.first, t.second);
            }
            vis[p.second] = 1;
        }
    }
    void spfa() {
        queue<int> q;
        vector<int> inq(n + 1, 0);
        q.push(S);
        dis[S] = 0;
        inq[S] = 1;
        while(!q.empty()) {
            int now = q.front();
            q.pop();
            for (auto &t : e[now]) {
                if (dis[now] + t.first < dis[t.second]) {
                    dis[t.second] = dis[now] + t.first;
                    if (!inq[t.second]) {
                        inq[t.second] = 1;
                        q.push(t.second);
                    }
                }
            }
            inq[now] = 0;
        }
    }
};

int main() {
    int n, m, S, T;
    scanf("%d%d%d%d",&n,&m,&S,&T);
    SSSPGraph G(n, m, S);
    while(m--) {
        int u, v, w;
        scanf("%d%d%d",&u,&v,&w);
        G.add_edge(u, v, w);
        G.add_edge(v, u, w);
    }
    //G.dijkstra();
    G.spfa();
    /*
    for (int i = 1; i <= n; i++) {
        if (G.dis[i] == G.INF) G.dis[i] = -1;
        printf("%lld%c",G.dis[i]," \n"[i==n]);
    }
    */
    printf("%lld\n",G.dis[T]);
}