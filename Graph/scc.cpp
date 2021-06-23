#include <bits/stdc++.h>

using namespace std;

struct ShrinkedDAG {
    int N;
    vector<vector<int> > e;
    using pii = pair<int, int>;
    set<pii> edge_set;
    ShrinkedDAG(){}
    ShrinkedDAG(int _N) : N(_N) {
        e.assign(N + 1, vector<int>());
        edge_set.clear();
    }
    void add_edge(int u, int v) {
        pii p(u, v);
        if (edge_set.find(p) != edge_set.end()) return;
        edge_set.insert(p);
        e[u].push_back(v);
    }
};

struct SCCGraph {
    int N;
    vector<vector<int> > e;
    vector<int> stk;
    vector<int> in_stack;
    vector<int> dfn, low, scc_id;
    int num_scc;
    SCCGraph(){}
    SCCGraph(int _N) : N(_N) {
        e.assign(N + 1, vector<int>());
        in_stack.assign(N + 1, 0);
        stk.assign(N + 1, 0);
        dfn.assign(N + 1, 0);
        low.assign(N + 1, 0);
        scc_id.assign(N + 1, 0);
    }

    void add_edge(int u, int v) {
        e[u].push_back(v);
    }

    void tarjan(int x, int &time_tag) {
        time_tag++;
        dfn[x] = low[x] = time_tag;
        in_stack[x] = 1;
        stk.push_back(x);
        for (auto &t : e[x]) {
            if (!dfn[t]) {
                tarjan(t, time_tag);
                low[x] = min(low[x], low[t]);
            } else {
                if (in_stack[t]) {
                    low[x] = min(low[x], dfn[t]);
                }
            }
        }
        if (low[x] == dfn[x]) {
            num_scc++;
            int now;
            do {
                now = stk.back();
                stk.pop_back();
                in_stack[now] = false;
                scc_id[now] = num_scc;
            } while(now != x);
        }
    }

    void solve() {
        int time_tag = 0;
        num_scc = 0;
        for (int i = 1; i <= N; i++) {
            if (!dfn[i]) {
                tarjan(i, time_tag);
            }
        }
    }

    ShrinkedDAG GetDAG() {
        ShrinkedDAG DAG(num_scc);
        for (int i = 1; i <= N; i++) {
            for (auto &j : e[i]) {
                if (scc_id[i] == scc_id[j]) continue;
                DAG.add_edge(scc_id[i], scc_id[j]);
            }
        }
        return DAG;
    }
};

int main() {
    SCCGraph G(6);
    G.add_edge(1, 2);
    G.add_edge(2, 3);
    G.add_edge(3, 1);
    G.add_edge(4, 5);
    G.add_edge(5, 4);
    G.add_edge(1, 4);
    G.add_edge(2, 5);
    G.add_edge(4, 6);
    G.solve();
    auto DAG = G.GetDAG();
    for (int i = 1; i <= 6; i ++) {
        printf("%d belongs to scc_%d\n",i,G.scc_id[i]);
    }
    for (auto &t : DAG.edge_set) {
        printf("%d %d\n",t.first,t.second);
    }
}