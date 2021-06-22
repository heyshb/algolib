#include <bits/stdc++.h>

using namespace std;

// 1-base!!
// return an array of length n + 1
// f[i] = \max{j | j < i && s[1, j] == s[i - j + 1, i]}
vector<int> KMP(char *s, int n) {
    vector<int> f(n + 1, 0);
    for (int i = 2; i <= n; i++) {
        int j;
        for (j = f[i - 1]; j && s[j + 1] != s[i]; j = f[j]);
        if (s[j + 1] == s[i]) f[i] = j + 1;
    }
    return f;
}

// 1-base!!
// s has a length of n
// t has a length of m
// return all the indexes i in s, where s[i - m + 1, i] = t
vector<int> match(char *s, char *t, int n, int m) {
    assert(n > 0 && m > 0);
    auto f = KMP(t, m);
    int node = 0;
    vector<int> ret;
    for (int i = 1; i <= n; i++) {
        while(node && t[node + 1] != s[i]) node = f[node];
        if (t[node + 1] == s[i]) node++;
        if (node == m) {
            ret.push_back(i);
            node = f[node];
        }
    }
    return ret;
}

int main() {
    char *s = " aaabaabaa";
    char *t = " aabaa";
    int n = strlen(s + 1);
    auto f = KMP(s, n);
    int m = strlen(t + 1);
    for (int i = 1; i <= n; i++) {
        printf("f[%d] = %d\n",i,f[i]);
    }
    auto mt = match(s, t, n, m);
    for (auto &t : mt) {
        printf("%d ",t);
    }
}