#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010;

typedef char my_char;
struct Suffix_Array {
    int N;
    my_char *s;
    int sa[MAXN],rank[MAXN],cnt[MAXN];
    int fir[MAXN],sec[MAXN],tmp[MAXN];
    int height[MAXN];
    int st[MAXN][21];
    int lg[MAXN];
    //tmp[i]: the pos of the i_th LARGEST suffix
    Suffix_Array(){}

    void init(my_char *_s) {
        s = _s;
        N = strlen(s);
        s[N] = '$';
        N++;
        build();
        for (int i=0,j=1;j<=N;i++,j*=2) {
            lg[j] = i;
        }
        for (int i=1;i<=N;i++) {
            if (!lg[i]) {
                lg[i] = lg[i - 1];
            }
        }
    }

    void build() {
        for (int i=0;i<=N;i++) cnt[i] = 0;
        for (int i=1;i<=N;i++) cnt[s[i]]++;
        for (int i=1;i<=N;i++) cnt[i] += cnt[i - 1];
        for (int i=1;i<=N;i++) rank[i] = cnt[s[i] - 1] + 1;
        for (int L=1;L<=N;L<<=1) {
            for (int i=1;i<=N;i++) {
                fir[i] = rank[i];
                sec[i] = (i + L <= N ? rank[i + L] : -1);
            }

            for (int i=0;i<=N;i++) cnt[i]  = 0;
            for (int i=1;i<=N;i++) cnt[sec[i]]++;
            for (int i=1;i<=N;i++) cnt[i] += cnt[i - 1];
            for (int i=1;i<=N;i++) tmp[N - (--cnt[sec[i]])] = i;

            for (int i=0;i<=N;i++) cnt[i]  = 0;
            for (int i=1;i<=N;i++) cnt[fir[i]]++;
            for (int i=1;i<=N;i++) cnt[i] += cnt[i - 1];
            for (int j=1;j<=N;j++) {
                int i = tmp[j];
                sa[cnt[fir[i]]--] = i;
            }
        }
    }

    int rmq(int L,int R) {
        int len = R - L + 1;
        len = lg[len];
        return min(st[L][len],st[R-(1<<len)+1][len]);
    }
}SA;

int main() {
    
}