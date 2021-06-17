#include <bits/stdc++.h>

using namespace std;

struct RootedTree {
    using len_type = long long;
    using pr = pair<len_type, int>;
    static const int MAXD = 21; // for LCA; (1 << (MAXD - 1)) >= N
    vector<vector<pr> >e;
    vector<int> fa;
    vector<len_type> dis_to_root; // dis from root
    vector<int> dep; // Root has a dep of 1
    vector<vector<int> > anc; // anc[i][j] is the (2^j) ancestor of i
    vector<int> dfn, dfnL, dfnR;

    int N, Root;
    RootedTree() {}
    RootedTree(int _N, int _Root = 1) : N(_N), Root(_Root) {
        e.assign(N + 1, vector<pr>());
        fa.assign(N + 1, 0);
        dis_to_root.assign(N + 1, 0);
        dep.assign(N + 1, 0);
        dfn.assign(N + 1, 0); // If need multiple dfn, modify to 2 * N + 1?
        dfnL.assign(N + 1, 0);
        dfnR.assign(N + 1, 0);
    }
    void add_edge(int u, int v, len_type w = 1) {
        e[u].push_back(pr(w, v));
        e[v].push_back(pr(w, u));
    }
    void dfs(int x, int FA, bool calc_lca, int &time_tag) {
        dfn[++time_tag] = x;
        dfnL[x] = time_tag;
        fa[x] = FA;
        if (calc_lca) {
            anc[x][0] = FA;
            for (int i = 1; i < MAXD; i++) anc[x][i] = anc[anc[x][i - 1]][i - 1];
        }
        for (auto &t : e[x]) {
            if (t.second == FA) continue;
            dep[t.second] = dep[x] + 1;
            dis_to_root[t.second] = dis_to_root[x] + t.first;
            dfs(t.second, x, calc_lca, time_tag);
        }
        dfnR[x] = time_tag;
    }
    void init(bool calc_lca = false) {
        dep[0] = 1;
        dis_to_root[0] = 0;
        if (calc_lca) anc.assign(N + 1, vector<int>(MAXD, 0));
        int time_tag = 0;
        dfs(Root, 0, calc_lca, time_tag);
    }
    int lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        int delta = dep[u] - dep[v];
        for (int i = MAXD - 1; i >= 0; i--) {
            if (delta & (1 << i)) {
                u = anc[u][i];
            }
        }
        if (u == v) return u;
        for (int i = MAXD - 1; i >= 0; i--) {
            if (anc[u][i] != anc[v][i]) {
                u = anc[u][i];
                v = anc[v][i];
            }
        }
        return anc[u][0];
    }
    int unweighted_dis(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
    len_type weighted_dis(int u, int v) {
        return dis_to_root[u] + dis_to_root[v] - 2 * dis_to_root[lca(u, v)];
    }
};

int main() {
    int n;
    scanf("%d",&n);
    RootedTree Tr(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        scanf("%d%d%d",&u,&v,&w);
        Tr.add_edge(u, v, w);
    }
    Tr.init(1);
    for (int i = 1; i <= n; i++) {
        printf("%d %d %d\n",Tr.dfn[i],Tr.dfnL[i],Tr.dfnR[i]);
    }
    /*
    while(true) {
        int u, v;
        scanf("%d%d",&u,&v);
        printf("%d %d %lld\n",Tr.lca(u, v),Tr.weighted_dis(u, v),Tr.unweighted_dis(u, v));
    }
    */
}