#include <bits/stdc++.h>

using namespace std;

class DinicFLow {
    public:
    const static int MAXN = 100010;
    const static int MAXM = 200010;
    typedef long long flowtype;
    int N, M;
    int S, T;
    int en[MAXM * 2], nxt[MAXM * 2];
    int head[MAXN], cur[MAXN];
    flowtype f[MAXM * 2];
    const flowtype FLOW_INF = 1e9;
    void init(int n, int s, int t) {
        N = n;M = 1;
        S = s;T = t;
    }
    void clear() {
        for (int i=1;i<=N;i++) {
            head[i] = 0;
        }
    }
    void addedge(int x,int y,int w) {
        M++;
        en[M] = y;
        nxt[M] = head[x];
        f[M] = w;
        head[x] = M;
        M++;
        en[M] = x;
        nxt[M] = head[y];
        f[M] = 0;
        head[y] = M;
    }
    int d[MAXN];
    queue<int>q;
    bool bfs(int st) {
        for (int i=1;i<=N;i++) {
            d[i] = -1;
            cur[i] = head[i];
        }
        d[st] = 0;
        q.push(st);
        while(!q.empty()) {
            int now = q.front();
            q.pop();
            for (int i=head[now];i;i=nxt[i]) {
                if (d[en[i]] == -1 && f[i]) {
                    d[en[i]] = d[now] + 1;
                    q.push(en[i]);
                }
            }
        }
        return (d[T] != -1);
    }
    flowtype dfs(int x, flowtype a) {
        if (a == 0 || x == T) return a;
        flowtype ret = 0;
        for (int &i = cur[x]; i; i = nxt[i]) {
            if (d[en[i]] == d[x] + 1 && f[i]) {
                int nf = dfs(en[i], min(a, f[i]));
                a -= nf;
                ret += nf;
                f[i] -= nf;
                f[i ^ 1] += nf;
            }
        }
        return ret;
    }
    flowtype MaxFLow() {
        flowtype ret = 0;
        while(bfs(S)) {
            ret += dfs(S, FLOW_INF);
        }
        return ret;
    }
}NF;

int main() {
    int N, M, S, T;
    scanf("%d%d%d%d",&N,&M,&S,&T);
    NF.init(N, S, T);
    for (int i=1;i<=M;i++) {
        int u, v, w;
        scanf("%d%d%d",&u,&v,&w);
        NF.addedge(u, v, w);
    }
    printf("%lld\n",NF.MaxFLow());
}