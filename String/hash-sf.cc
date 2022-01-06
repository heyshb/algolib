#include <bits/stdc++.h>

using namespace std;

using ll = long long;

template <int SEED, int MOD>
struct Hash {
    using type = int;

    vector<int> val, e;
    template <class T>
    void set(const T& s) {
        cout << "init " << SEED << " " << MOD << endl;
        val.resize(s.size());
        e.resize(s.size());

        val[0] = s[0] % MOD;
        e[0] = 1;
        for (size_t i = 1; i < val.size(); ++i) {
            val[i] = (val[i - 1] * (ll)SEED + s[i]) % MOD;
            e[i] = (e[i - 1] * (ll)SEED) % MOD;

            cout << val[i] << " " << e[i] << endl;
        }
    }

    int prefix(size_t i) const { return val[i]; }
};

template <class... Hs>
struct MultiHash {
    using type = tuple<typename Hs::type...>;
    using Seq = index_sequence_for<Hs...>;
    tuple<Hs...> hashs;

    template <class T, size_t... I>
    void set(const T& s, index_sequence<I...>) {
        (get<I>(hashs).set(s), ...);
    }
    template <class T>
    void set(const T& s) {
        set(s, Seq());
    }

    template <size_t... I>
    type prefix(size_t i, index_sequence<I...>) {
        return make_tuple(get<I>(hashs).prefix(i)...);
    }
    type prefix(size_t i) {
        return prefix(i, Seq());
    };
};

int main(){
    MultiHash<Hash<10, 100000000>, Hash<16, 1 << 28>> hash;
    hash.set(vector{1, 2, 3, 4, 5, 6, 7, 8, 9});

    auto t = hash.prefix(5);
    printf("%d\n", get<0>(t));
    printf("%x\n", get<1>(t));

    return 0;
}
