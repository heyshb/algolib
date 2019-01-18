#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<int,int> pii;
const int MAXN = 1000010;

const int HASH_SIZE = 2;
const int HASH_TOTAL = 3;
const LL seeds[HASH_TOTAL] = {233, 237, 239};
const LL MODS[HASH_TOTAL] = {1000000007, 1000000009, 998244353};
typedef array<LL,HASH_SIZE> arr;
struct Hash {
    LL seed, MOD;
    LL v[MAXN],po[MAXN];
    Hash(){}
    void init(char *s, int N,LL _seed = seeds[0],LL _MOD = MODS[0]) {
        MOD = _MOD;
        seed = _seed;
        v[0] = 0;
        po[0] = 1;
        for (int i=1;i<=N;i++) {
            v[i] = (v[i - 1] * seed + s[i]) % MOD;
            po[i] = po[i - 1] * seed % MOD;
        }
    }
    LL get_interval_hash(int L,int R) {
        LL ret = v[R] - v[L - 1] * po[R - L + 1] % MOD;
        if (ret < 0) {
            ret += MOD;
        }
        if (ret >= MOD) {
            ret -= MOD;
        }
        return ret;
    }
    bool same(int L1,int R1,int L2,int R2) {
        if (R1 - L1 != R2 - L2) {
            return false;
        }
        return get_interval_hash(L1,R1) == get_interval_hash(L2,R2);
    }
    LL get_string_hash(char *s,int N) {
        LL ret = 0;
        for (int i=0;i<N;i++) {
            ret = (ret * seed + s[i]) % MOD;
        }
        return ret;
    }
};

struct MHash {
    char *s;//1-base
    int N;
    Hash h[HASH_SIZE];
    MHash() {}

    void init(char *_s, int _N) {
        s = _s;
        N = _N;
        for (int i=0;i<HASH_SIZE;i++) {
            h[i].init(s, N, seeds[i], MODS[i]);
        } 
    }

    //O(1)
    bool same(int L1,int R1,int L2,int R2) {
        if (R1 - L1 != R2 - L2) {
            return false;
        }
        for (int i=0;i<HASH_SIZE;i++) {
            if (h[i].get_interval_hash(L1,R1) != h[i].get_interval_hash(L2,R2)) {
                return false;
            }
        }
        return true;
    }

    //O(len(s))
    bool appear(char *s,int L) {
        int len = strlen(s);
        if (L + len - 1 > N) {
            return false;
        }
        for (int i=0;i<HASH_SIZE;i++) {
            if (h[i].get_string_hash(s,len) != h[i].get_interval_hash(L,L + len - 1)) {
                return false;
            }
        }
        return true;
    }

    //O(len(s) + N)
    vector<int> appear_pos(char *s) {
        LL hv[HASH_SIZE];
        int len = strlen(s);
        for (int i=0;i<HASH_SIZE;i++) {
            hv[i] = h[i].get_string_hash(s, len);
        }
        vector<int>ret;
        for (int i=1;i+len-1<=N;i++) {
            bool ok = true;
            for (int j=0;j<HASH_SIZE;j++) {
                if (h[j].get_interval_hash(i,i+len-1) != hv[j]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                ret.push_back(i);
            }
        }
        return ret;
    }

    arr get_hash(char *s) {
        arr ret;
        int len = strlen(s);
        for (int i=0;i<HASH_SIZE;i++) {
            ret[i] = h[i].get_string_hash(s,len);
        }
        return ret;
    }

    arr get_hash(int L,int R) {
        arr ret;
        for (int i=0;i<HASH_SIZE;i++) {
            ret[i] = h[i].get_interval_hash(L,R);
        }
        return ret;
    }
};

void print(arr hsh) {
    for (int i=0;i<HASH_SIZE;i++) {
        printf("%lld%c",hsh[i],",\n"[i==hsh.size()-1]);
    }
}