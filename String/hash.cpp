#include <bits/stdc++.h>

using namespace std;

using LL = long long;
typedef pair<int,int> pii;

//1-base !!
namespace StringHash {
    static constexpr int HASH_SIZE = 2;
    static constexpr int MAX_HASH_SIZE = 3;
    static constexpr LL seeds[MAX_HASH_SIZE] = {233, 237, 239};
    static constexpr LL MODS[MAX_HASH_SIZE] = {1000000007, 1000000009, 998244353};
    typedef array<LL,HASH_SIZE> arr;
    struct Hash {
        LL seed, MOD;
        vector<LL> v, po;
        Hash(){}
        Hash(char *s, int N, LL _seed = seeds[0], LL _MOD = MODS[0]) : seed(_seed), MOD(_MOD) {
            v.resize(N + 1);
            po.resize(N + 1);
            v[0] = 0;
            po[0] = 1;
            for (int i = 1; i <= N; i++) {
                v[i] = (v[i - 1] * seed + s[i]) % MOD;
                po[i] = po[i - 1] * seed % MOD;
            }
        }
        LL get_interval_hash(int L, int R) {
            LL ret = v[R] - v[L - 1] * po[R - L + 1] % MOD;
            if (ret < 0) {
                ret += MOD;
            }
            if (ret >= MOD) {
                ret -= MOD;
            }
            return ret;
        }
        bool same(int L1, int R1, int L2, int R2) {
            if (R1 - L1 != R2 - L2) {
                return false;
            }
            return get_interval_hash(L1, R1) == get_interval_hash(L2, R2);
        }
        LL get_string_hash(char *s, int L, int R) {
            LL ret = 0;
            for (int i = L; i <= R; i++) {
                ret = (ret * seed + s[i]) % MOD;
            }
            return ret;
        }
    };

    struct MHash {
        int N;
        vector<Hash> h;
        MHash() {}
        MHash(char *_s, int _N) : N(_N) {
            h.clear();
            for (int i = 0; i < HASH_SIZE; i++) {
                h.emplace_back(_s, N, seeds[i], MODS[i]);
            } 
        }

        //O(1)
        bool same(int L1,int R1,int L2,int R2) {
            if (R1 - L1 != R2 - L2) {
                return false;
            }
            for (int i = 0;i < HASH_SIZE; i++) {
                if (h[i].get_interval_hash(L1, R1) != h[i].get_interval_hash(L2, R2)) {
                    return false;
                }
            }
            return true;
        }

        //O(len(s))
        bool appear(char *s, int L) {
            int len = strlen(s);
            if (L + len - 1 > N) {
                return false;
            }
            for (int i = 0;i < HASH_SIZE; i++) {
                if (h[i].get_string_hash(s, 1, len) != h[i].get_interval_hash(L, L + len - 1)) {
                    return false;
                }
            }
            return true;
        }

        //O(len(s) + N)
        //1 - base
        vector<int> appear_pos(char *s, int len) {
            LL hv[HASH_SIZE];
            for (int i=0;i<HASH_SIZE;i++) {
                hv[i] = h[i].get_string_hash(s, 1, len);
            }
            vector<int>ret;
            for (int i = 1;i + len - 1 <= N; i++) {
                bool ok = true;
                for (int j = 0; j < HASH_SIZE; j++) {
                    if (h[j].get_interval_hash(i, i + len - 1) != hv[j]) {
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

        arr get_string_hash(char *s, int L, int R) {
            arr ret;
            for (int i=0;i<HASH_SIZE;i++) {
                ret[i] = h[i].get_string_hash(s, L, R);
            }
            return ret;
        }

        arr get_interval_hash(int L,int R) {
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
};
using MHash = StringHash::MHash;

char s[101010];
char t[101010];

int main() {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    MHash H(s, n);
    while(true) {
        scanf("%s", t + 1);
        int m = strlen(t + 1);
        auto tmp = H.appear_pos(t, m);
        for (auto &val : tmp) {
            printf("%d ",val);
        }
        puts("");
    }
}