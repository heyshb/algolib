#include <bits/stdc++.h>

using namespace std;
using LL = long long;

namespace FFT {
constexpr int MAXL = 22;
constexpr int MAXN = 1 << MAXL;
const double PI = acos(-1);
// constexpr double PI = acos(-1);
struct Complex {
  double R, I;
  Complex() { R = I = 0; }
  Complex(double _R, double _I) : R(_R), I(_I) {}
  Complex operator+(const Complex& r) { return Complex(R + r.R, I + r.I); }
  Complex operator-(const Complex& r) { return Complex(R - r.R, I - r.I); }
  Complex operator*(const Complex& r) {
    return Complex(R * r.R - I * r.I, R * r.I + I * r.R);
  }
  Complex operator/(const double d) { return Complex(R / d, I / d); }
};

using vd = vector<double>;
using vi = vector<int>;
int rev[MAXN];
Complex a[MAXN], b[MAXN], c[MAXN];

void calc_rev(int n) {
  int l = 31 - __builtin_clz(n);
  for (int i = 0; i < n; i++)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));
}

void transform(int n, Complex* t, int typ) {
  calc_rev(n);
  for (int i = 0; i < n; i++)
    if (i < rev[i]) swap(t[i], t[rev[i]]);
  for (int step = 1; step < n; step <<= 1) {
    Complex gn(cos(PI / step), sin(PI / step));
    for (int i = 0; i < n; i += (step << 1)) {
      Complex g(1, 0);
      for (int j = 0; j < step; j++, g = g * gn) {
        Complex x = t[i + j], y = g * t[i + j + step];
        t[i + j] = x + y;
        t[i + j + step] = x - y;
      }
    }
  }
  if (typ == 1) return;
  for (int i = 1; i < n / 2; i++) swap(t[i], t[n - i]);
  for (int i = 0; i < n; i++) t[i] = t[i] / n;
}

void fft(int p, Complex* A, Complex* B, Complex* C) {
  transform(p, A, 1);
  transform(p, B, 1);
  for (int i = 0; i < p; i++) C[i] = A[i] * B[i];
  transform(p, C, -1);
}

void mul(Complex* A, Complex* B, Complex* C, int n, int m) {
  int p = 1;
  while (p <= n + m) p <<= 1;
  for (int i = n + 1; i < p; i++) A[i] = Complex(0, 0);
  for (int i = m + 1; i < p; i++) B[i] = Complex(0, 0);
  fft(p, A, B, C);
}

// Get the inversion of A, mod x^deg, store in B
void inv(int deg, Complex* A, Complex* B, Complex* tmp) {
  if (deg == 1) {
    B[0] = Complex(1.0 / A[0].R, 0);
    return;
  }
  inv((deg + 1) / 2, A, B, tmp);
  for (int i = 0; i < deg; i++) tmp[i] = A[i];
  int p = 1;
  while (p < 2 * deg) p <<= 1;
  for (int i = deg; i < p; i++) tmp[i] = Complex(0, 0);

  transform(p, tmp, 1);
  transform(p, B, 1);
  for (int i = 0; i < p; i++) {
    B[i] = B[i] * (Complex(2, 0) - tmp[i] * B[i]);
  }
  transform(p, B, -1);
  for (int i = deg; i < p; i++) B[i] = Complex(0, 0);
}

vd conv(vd& v1, vd& v2) {
  int n = v1.size() - 1, m = v2.size() - 1;  // degree of poly v1 and v2
  for (int i = 0; i <= n; i++) a[i] = Complex(v1[i], 0);
  for (int i = 0; i <= m; i++) b[i] = Complex(v2[i], 0);
  mul(a, b, c, n, m);
  vd ret(n + m + 1);
  for (int i = 0; i < n + m + 1; i++) {
    ret[i] = c[i].R;
  }
  return ret;
}

// Find a polynomial g(x), such that f(x) * g(x) = 1 (mod x^deg)
vd poly_inv(vd& f, int deg) {
  if (fabs(f[0]) < 1e-5) {
    return {};
  }
  for (int i = 0; i < deg; i++) {
    if (i < f.size()) {
      a[i] = Complex(f[i], 0);
    } else {
      a[i] = Complex(0, 0);
    }
  }
  inv(deg, a, b, c);
  vd ret(deg);
  for (int i = 0; i < deg; i++) {
    ret[i] = b[i].R;
  }
  return ret;
}

}  // namespace FFT

namespace NTT {
constexpr int MAXL = 22;
constexpr int MAXN = 1 << MAXL;
constexpr int root = 3;
constexpr int MOD = 998244353;
int rev[MAXN];
int a[MAXN], b[MAXN], c[MAXN];
using vi = vector<int>;

int fast_pow(int a, int b) {
  int ans = 1;
  while (b) {
    if (b & 1) ans = 1LL * ans * a % MOD;
    a = 1LL * a * a % MOD;
    b >>= 1;
  }
  return ans;
}

void transform(int n, int* t, int typ) {
  for (int i = 0; i < n; i++)
    if (i < rev[i]) swap(t[i], t[rev[i]]);
  for (int step = 1; step < n; step <<= 1) {
    int gn = fast_pow(root, (MOD - 1) / (step << 1));
    for (int i = 0; i < n; i += (step << 1)) {
      int g = 1;
      for (int j = 0; j < step; j++, g = 1LL * g * gn % MOD) {
        int x = t[i + j], y = 1LL * g * t[i + j + step] % MOD;
        t[i + j] = (x + y) % MOD;
        t[i + j + step] = (x - y + MOD) % MOD;
      }
    }
  }
  if (typ == 1) return;
  for (int i = 1; i < n / 2; i++) swap(t[i], t[n - i]);
  int inv = fast_pow(n, MOD - 2);
  for (int i = 0; i < n; i++) t[i] = 1LL * t[i] * inv % MOD;
}

void ntt(int p, int* A, int* B, int* C) {
  transform(p, A, 1);
  transform(p, B, 1);
  for (int i = 0; i < p; i++) C[i] = 1LL * A[i] * B[i] % MOD;
  transform(p, C, -1);
}

void mul(int* A, int* B, int* C, int n, int m) {
  int p = 1, l = 0;
  while (p <= n + m) p <<= 1, l++;
  // printf("n = %d, m = %d\n",n,m);
  for (int i = n + 1; i < p; i++) A[i] = 0;
  for (int i = m + 1; i < p; i++) B[i] = 0;
  // for (int i=0;i<p;i++) printf("%d ",A[i]);puts("");
  // for (int i=0;i<p;i++) printf("%d ",B[i]);puts("");
  for (int i = 0; i < p; i++)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));
  ntt(p, A, B, C);
  // puts("C:");for (int i=0;i<p;i++) printf("%d ",C[i]);puts("");
}

vi conv(vi& v1, vi& v2) {
  int n = v1.size() - 1, m = v2.size() - 1;  // degree of poly v1 and v2
  for (int i = 0; i <= n; i++) a[i] = v1[i];
  for (int i = 0; i <= m; i++) b[i] = v2[i];
  mul(a, b, c, n, m);
  vi ret(c, c + n + m + 1);
  return ret;
}
}  // namespace NTT

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  n++;
  m++;
  vector<double> a(n), b(m);
  for (int i = 0; i < n; i++) {
    scanf("%lf", &a[i]);
  }
  for (int i = 0; i < m; i++) {
    scanf("%lf", &b[i]);
  }
  auto c = FFT::conv(a, b);
  for (int i = 0; i < c.size(); i++) {
    printf("%d%c", int(c[i] + 1e-5), " \n"[i == c.size() - 1]);
  }
}
