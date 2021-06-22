#include <bits/stdc++.h>

using namespace std;

struct Trie {
    static const int ALPHABET = 26;
    static const int MAXN = 100010;
    //int ch[MAXN][ALPHABET];
    vector<vector<int> >ch;
    int M; // number of nodes
    void clear() {
        M = 1; 
        for (int i = 0; i < ALPHABET; i++) {
            ch[1][i] = 0;
        }
    }
    Trie() {
        ch.assign(MAXN, vector<int>(ALPHABET, 0));
        clear();
    }
    // 1-base
    void insert(char *s, int n) {
        int now = 1;
        for (int i = 1; i <= n; i++) {
            int &CH = ch[now][s[i] - 'a'];
            if (!CH) {
                CH = ++M;
                for (int j = 0; j < ALPHABET; j++) ch[M][j] = 0;
            }
            now = CH;
        }
    }
};

struct AC_Automaton : Trie {
    vector<int>fail;
    vector<vector<int> >go;
    AC_Automaton(){
        fail.resize(MAXN);
        go.assign(MAXN, vector<int>(ALPHABET, 0));
    }
    void calc_fail_and_go() {
        queue<int> q;
        q.push(1);
        fail[1] = 0;
        while(!q.empty()) {
            int now = q.front();
            q.pop();
            for (int i = 0; i < ALPHABET; i++) {
                int CH = ch[now][i];
                if (!CH) continue;
                int tmp = fail[now];
                while(tmp && !ch[tmp][i]) tmp = fail[tmp];
                if (tmp && ch[tmp][i]) {
                    fail[CH] = ch[tmp][i];
                } else {
                    fail[CH] = 1;
                }
                q.push(CH);
            }
        }
        for (int i = 1; i <= M; i++) {
            for (int j = 0; j < ALPHABET; j++) {
                int tmp = i;
                while(tmp && !ch[tmp][j]) tmp = fail[tmp];
                if (tmp) {
                    go[i][j] = ch[tmp][j];
                } else {
                    go[i][j] = 1;
                }
            }
        }
    }
};

int n;
char s[100010];

int main() {
    scanf("%d",&n);
    AC_Automaton AC;
    for (int i = 1; i <= n; i++) {
        scanf("%s", s + 1);
        int len = strlen(s + 1);
        AC.insert(s, len);
    }
    AC.calc_fail_and_go();
    for (int i = 1; i <= AC.M; i++) {
        for (int j = 0; j < 26; j++) {
            if (AC.ch[i][j]) {
                printf("%d--%c-->%d\n",i,j+'a',AC.ch[i][j]);
            }
        }
    }
    for (int i = 1; i <= AC.M; i++) {
        printf("fail %d = %d\n",i,AC.fail[i]);
    }
}