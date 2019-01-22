#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010;
class Suffix_Array {
public:
    int N;
    char *s;
    int scp[MAXN],a[MAXN];
    int sa[MAXN],rank[MAXN],cnt[MAXN];
    int fir[MAXN],sec[MAXN],tmp[MAXN];
    int height[MAXN];
    int st[MAXN][22];
    int lg[MAXN];
    Suffix_Array(){}

    void init(char *_s) {
        s = _s;
        N = strlen(s + 1);
        build();
        get_height();
        get_st();
    }

    void build() {
        for (int i=1;i<=N;i++) scp[i] = s[i];
        sort(scp+1,scp+N+1);
        int *end = unique(scp+1,scp+N+1);
        for (int i=1;i<=N;i++)a[i] = lower_bound(scp+1, end, s[i]) - scp;
        for (int i=0;i<=N;i++) cnt[i] = 0;
        for (int i=1;i<=N;i++) cnt[a[i]]++;
        for (int i=1;i<=N;i++) cnt[i] += cnt[i - 1];
        for (int i=1;i<=N;i++) rank[i] = cnt[a[i] - 1] + 1;
        for (int L=1;L<=N;L<<=1) {
            for (int i=1;i<=N;i++) {
                fir[i] = rank[i];
                sec[i] = (i + L <= N ? rank[i + L] : 0);
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
            int last = 0;
            bool done = true;
            for (int j=1;j<=N;j++) {
                int i = sa[j];
                if (last == 0) {
                    rank[i] = 1;
                }
                else if (fir[i] == fir[last] && sec[i] == sec[last]) {
                    rank[i] = rank[last];
                    done = false;
                }
                else {
                    rank[i] = rank[last] + 1;
                }
                last = i;
            }
            if (done) {
                break;
            }
        }
    }

    void print() {
        puts("SA:");
        for (int i=1;i<=N;i++) printf("%d ",sa[i]);
        puts("\nRANK:");
        for (int i=1;i<=N;i++) printf("%d ",rank[i]);
        puts("");
    }

    void get_height() {
        for (int i=1,k=0;i<=N;i++) {
            if (rank[i] == 1) {
                k = 0;
            }
            else {
                if (k > 0) k--;
                int j = sa[rank[i] - 1];
                while(i + k <= N && j + k <= N && a[i + k] == a[j + k]) k++;
            }
            height[rank[i]] = k;
        }
    }

    void get_st() {
        for (int i=0,j=1;j<=N;i++,j*=2) {
            lg[j] = i;
        }
        for (int i=1;i<=N;i++) {
            if (!lg[i]) {
                lg[i] = lg[i - 1];
            }
        }
        for (int i=1;i<=N;i++) {
            st[i][0] = height[i];
        }
        for (int j=1;j<=lg[N];j++) {
            for (int i=1;i<=N;i++) {
                st[i][j] = min(st[i][j-1], st[min(N,i+(1<<(j-1)))][j-1]);
            }
        }
    }

    int LCP(int x,int y) {
        if (x == y) {
            return N + 1 - x;
        }
        x = rank[x];
        y = rank[y];
        if (x > y) swap(x, y);
        return rmq(x + 1, y);
    }

    int rmq(int L,int R) {
        int len = R - L + 1;
        len = lg[len];
        return min(st[L][len],st[R-(1<<len)+1][len]);
    }
}SA;//1-base!

char s[MAXN];

int main() {
    scanf("%s",s + 1);
    SA.init(s);
    SA.print();
}