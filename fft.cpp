#include <bits/stdc++.h>

using namespace std;

struct Complex {
    double R,I;
    Complex(){R = I = 0;}
    Complex(double _R,double _I):R(_R),I(_I){}
    Complex operator + (const Complex &r) {return Complex(R + r.R, I + r.I);}
    Complex operator - (const Complex &r) {return Complex(R - r.R, I - r.I);}
    Complex operator * (const Complex &r) {return Complex(R * r.R - I * r.I, R * r.I + I * r.R);}
};

typedef vector<double> vd;
const int MAXN = (1 << 20);
void dft()
vd mul(vd a,vd b) {
    int N1,N2;
    N1 = a.size();
    N2 = b.size();
}

int main() {
    
}