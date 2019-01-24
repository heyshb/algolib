#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;
class num {

public:
    int v;
    num(){v = 0;}
    num(int _v):v(_v){}
    int to_int() const{
        return v;
    }
    num& operator = (const num &r) {
        v = r.v;
        return *this;
    }
    num& operator = (const int &r) {
        v = r % MOD;
        return *this;
    }
    num operator - () const {
        if (v == 0) {
            return *this;
        }
        return num(MOD - v);
    }
    num operator + (const num &r) const {
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
    num operator ^ (const int &r) const {
        num ret = 1;
        num a = *this;
        int x = r;
        while(x) {
            if (x & 1) ret = ret * a;
            a = a * a;
            x >>= 1;
        }
        return ret;
    }
    num operator / (const num &r) const {
        return (*this) * (r ^ (MOD - 2));
    }
    num operator + (const int &r) const {
        return (*this) + num(r);
    }
    num operator - (const int &r) const {
        return (*this) - num(r);
    }
    num operator * (const int &r) const {
        return (*this) * num(r);
    }
    num operator / (const int &r) const {
        return (*this) / num(r);
    }
    num& operator += (const num &r) {
        (*this) = (*this) + r;
        return *this;
    }
    num& operator -= (const num &r) {
        (*this) = (*this) - r;
        return *this;
    }
    num& operator *= (const num &r) {
        (*this) = (*this) * r;
        return *this;
    }
    num& operator /= (const num &r) {
        (*this) = (*this) / r;
        return *this;
    }
};

num operator + (const int &l, const num &r) {
    return r + l;
}

num operator - (const int &l, const num &r) {
    return - r + l;
}

num operator * (const int &l, const num &r) {
    return r * l;
}

num operator / (const int &l, const num &r) {
    return num(l) / r;
}

int main() {
    num a,b;
    b = 2;
    printf("%d\n",(3 / b).v);
}