#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;
class num {

public:
    int v;
    num(){}
    num(int _v):v(_v){}
    operator int();
    num& operator = (const int &r) {
        v = r;
        return *this;
    }
    num operator + (const num &r) const{
        int tmp = v + r.v;
        if (tmp >= MOD) tmp -= MOD;
        return num(tmp);
    }
    num operator - (const num &r) const{
        int tmp = v - r.v;
        if (tmp < 0) tmp += MOD;
        return num(tmp);
    }
    num operator * (const num &r) const{
        return num(1LL * r.v * v % MOD);
    }
    num pow(int x) {
        num ret = 1;
        num &a = *this;
        while(x) {
            if (x & 1) ret = ret * a;
            a = a * a;
            x >>= 1;
        }
        return ret;
    }
    num inv() {
        return pow(MOD - 2);
    }
    num operator / (const num &r) {
        num tmp = r.inv();
        return (*this) * r.inv();
    }
};

int main() {
    num a,b;
    a = 2;
    b = 3;
    printf("%d\n",(a / b).v);
}