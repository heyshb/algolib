#include <bits/stdc++.h>

using namespace std;

struct BCCGraph {
    int n, m;
    vector<int>head;    // size: n + 1
    vector<int>en, nxt; // size: m
    vector<int>dfn, low;
    BCCGraph(int _n) : n(_n) {
        head.assign(n + 1, -1);     // Notice that the link list ends at -1
        dfn.assign(n + 1, 0);
        low.assign(n + 1, 0);
        en.clear();
        nxt.clear();
        m = 0;
    }
    
    void addedge(int u, int v) {
        add_directed_edge(u, v);
        add_directed_edge(v, u);
    }
private: 
    void add_directed_edge(int u, int v) {
        m++;
        en.push_back(v);
        nxt.push_back(head[u]);
        head[u] = m - 1;
    }
};

// Edge-BCC
struct EBCCGraph : BCCGraph{
    vector<int> is_bridge; // size: m    whether a edge is bridge
    vector<int> id; // size: n + 1          EBCC id of vertices
    EBCCGraph(int _n) : BCCGraph(_n) {
        id.assign(n + 1, 0);
    }

    void tarjan(int x, int from_edge_id, int &time_tag) {
        time_tag++;
        dfn[x] = low[x] = time_tag;
        for (int i = head[x]; i != -1; i = nxt[i]) {
            if (i == (from_edge_id ^ 1)) continue;
            int to = en[i];
            if (!dfn[to]) {
                tarjan(to, i, time_tag);
                low[x] = min(low[x], low[to]);
                if (low[to] > dfn[x]) {
                    is_bridge[i] = is_bridge[i ^ 1] = 1;
                }
            } else {
                low[x] = min(low[x], dfn[to]);
            }
        }
    }

    void assign_id(int x, int ID) {
        id[x] = ID;
        for (int i = head[x]; i != -1; i = nxt[i]) {
            if (is_bridge[i] || id[en[i]]) continue;
            assign_id(en[i], ID);
        }
    }

    void solve_EBCC() {
        is_bridge.assign(m, 0);
        int time_tag = 0;
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                tarjan(i, -1, time_tag);
            }
        }
        int ID = 0;
        for (int i = 1; i <= n; i++) {
            if (!id[i]) {
                ID++;
                assign_id(i, ID);
            }
        }
    }

    using pii = pair<int,int>;
    vector<pii> get_bridges() {
        vector<pii> ret;
        for (int i = 1; i <= n; i++) {
            for (int j = head[i]; j != -1; j = nxt[j]) {
                if (j % 2 == 0 && is_bridge[j]) {
                    // ret.emplace_back(i, en[j]);
                    ret.emplace_back(id[i], id[en[j]]);
                }
            }
        }
        return ret;
    }
};

// Vertex-BCC
struct VBCCGraph : BCCGraph{
    vector<int> is_cut; // size: n + 1
    vector<int> vertex_id; // size: n + 1    the id of VBCC the i-th vertex belongs to; id of cut points are -1
    vector<int> edge_id; // size: m          the id of VBCC the i-th edge belongs to.
    vector<int> vertex_stack, edge_stack;

    VBCCGraph(int _n) : BCCGraph(n) {
        is_cut.assign(n + 1, 0);
        vertex_id.assign(n + 1, 0);
        vertex_stack.clear();
        edge_stack.clear();
    }

    void tarjan(int x, int from_edge, int &time_tag, int root) {
        time_tag++;
        dfn[x] = low[x] = time_tag;
        vertex_stk.push_back(x);
        int cnt = 0;
        for (int i = head[x]; i != -1; i = nxt[i]) {
            if (i == from_edge ^ 1) continue;
            int to = en[i];
            if (!dfn[to]) {
                tarjan(to, i, time_tag, root);                
                low[x] = min(low[x], low[to]);
            } else {
                low[x] = min(low[x], dfn[to]);
            }
            if (dfn[x] <= low[to]) {
                cnt++;
            }
        }
    }

    void solve_VBCC() {
        edge_id.assign(m, 0);
        int time_tag = 0;
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                tarjan(i, -1, time_tag, i);
            }
        }
    }
};

int main() {
    int n, m;
    scanf("%d%d",&n,&m);
    EBCCGraph G(n);
    while(m--) {
        int u, v;
        scanf("%d%d",&u,&v);
        G.addedge(u, v);
    }
    G.solve_EBCC();
    for (auto &t : G.get_bridges()) {
        printf("%d %d\n",t.first,t.second);
    }
}