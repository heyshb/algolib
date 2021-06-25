#include <bits/stdc++.h>

using namespace std;

// 1-base!!
struct Manachar {
    static const char padding = '#';
    vector<int> f; // f[i]: maximum expand length from i to both side
    vector<char> s_pad;
    Manachar(){}
    Manachar(char *s, int n) {
        // 'abcd' --> '#a#b#c#d#'
        // valid index: [1 ... 2 * n + 1]
        s_pad.resize(2 * n + 2);
        f.resize(2 * n + 2);
        for (int i = 1; i <= 2 * n + 1; i++) {
            if (i % 2 == 1) {
                s_pad[i] = padding;
            } else {
                s_pad[i] = s[i / 2];
            }
        }
        int mx = 0, center = 0;
        for (int i = 1; i <= 2 * n + 1; i++) {
            f[i] = 0;
            if (mx >= i) {
                int reflect = 2 * center - i;
                f[i] = min(mx - i, f[reflect]);
            }
            while(i + f[i] + 1 <= 2 * n + 1 && i - f[i] - 1 > 0 && s_pad[i + f[i] + 1] == s_pad[i - f[i] - 1]) {
                f[i]++;
            }
            if (i + f[i] > mx) {
                mx = i + f[i];
                center = i;
            }
        }
    }
    using pii = pair<int, int>;
    // return the indexes of endpoints L, R
    // s[L...R]
    pii longest_pal_substring() {
        int max_length = 0;
        pii ret(0, 0);
        for (int i = 1; i < f.size(); i++) {
            int L = (i - f[i] + 1) / 2;
            int R = (i + f[i] - 1) / 2;
            if (R - L > ret.second - ret.first) {
                ret = pii(L, R);
            }
        }
        return ret;
    }
};

// original index i --> 2 * i
char s[1000100];

int main() {
    scanf("%s",s + 1);
    int n = strlen(s + 1);
    Manachar M(s, n);
    for (int i = 1; i <= 2 * n + 1; i++) printf("%c ", M.s_pad[i]);puts("");
    for (int i = 1; i <= 2 * n + 1; i++) {
        printf("%d ",M.f[i]);
    } puts("");
    auto lps = M.longest_pal_substring();
    printf("%d %d\n",lps.first, lps.second);
}