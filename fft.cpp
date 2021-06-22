#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

struct FFTClass {
    struct Complex {
        double R,I;
        Complex(){R = I = 0;}
        Complex(double _R,double _I):R(_R),I(_I){}
        Complex operator + (const Complex &r) {return Complex(R + r.R, I + r.I);}
        Complex operator - (const Complex &r) {return Complex(R - r.R, I - r.I);}
        Complex operator * (const Complex &r) {return Complex(R * r.R - I * r.I, R * r.I + I * r.R);}
    };

    using vd = vector<double>;
    static const int MAXN = (1 << 20);
    void dft() {
        
    }
    vd mul(vd a,vd b) {
        int N1,N2;
        N1 = a.size();
        N2 = b.size();
    }
}FFT;
const int MM = 200000;
int fac[MM + 10], ifac[MM + 10];
const int MOD = 998244353;
 
LL quick_pow(LL a,LL x) {
    LL ret = 1;
    while(x) {
        if (x & 1) {
            ret = ret * a % MOD;
        }
        a = a * a % MOD;
        x >>= 1;
    }
    return ret;
}
 
struct NTTClass{
    static const int MAXL=22;
    static const int MAXN=1<<MAXL;
    static const int root=3;
    static const int MOD=998244353;
    int rev[MAXN];
    int a[MAXN], b[MAXN], c[MAXN];
    using vi = vector<int>;
 
    int fast_pow(int a,int b){
        int ans=1;
        while(b){
            if(b&1)ans=1ll*ans*a%MOD;
            a=1ll*a*a%MOD;
            b>>=1;
        }
        return ans;
    }
 
    void transform(int n,int *t,int typ){
        for(int i=0;i<n;i++)
            if(i<rev[i])swap(t[i],t[rev[i]]);
        for(int step=1;step<n;step<<=1){
            int gn=fast_pow(root,(MOD-1)/(step<<1));
            for(int i=0;i<n;i+=(step<<1)){
                int g=1;
                for(int j=0;j<step;j++,g=1ll*g*gn%MOD){
                    int x=t[i+j],y=1ll*g*t[i+j+step]%MOD;
                    t[i+j]=(x+y)%MOD;
                    t[i+j+step]=(x-y+MOD)%MOD;
                }
            }
        }
        if(typ==1)return;
        for(int i=1;i<n/2;i++)swap(t[i],t[n-i]);
        int inv=fast_pow(n,MOD-2);
        for(int i=0;i<n;i++)t[i]=1ll*t[i]*inv%MOD;
    }
 
    void ntt(int p,int *A,int *B,int *C){
        transform(p,A,1);
        transform(p,B,1);
        for(int i=0;i<p;i++)C[i]=1ll*A[i]*B[i]%MOD;
        transform(p,C,-1);
    }
 
    void mul(int *A,int *B,int *C,int n,int m) {
        int p=1,l=0;
        while(p<=n+m)p<<=1,l++;
        //printf("n = %d, m = %d\n",n,m);
        for (int i=n+1;i<p;i++) A[i] = 0;
        for (int i=m+1;i<p;i++) B[i] = 0;
        //for (int i=0;i<p;i++) printf("%d ",A[i]);puts("");
        //for (int i=0;i<p;i++) printf("%d ",B[i]);puts("");
        for(int i=0;i<p;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
        ntt(p,A,B,C);
        //puts("C:");for (int i=0;i<p;i++) printf("%d ",C[i]);puts("");
    }

    vi conv(vi &v1, vi &v2) {
        int n = v1.size() - 1, m = v2.size() - 1; // degree of poly v1 and v2
        for (int i = 0; i <= n; i++) a[i] = v1[i];
        for (int i = 0; i <= m; i++) b[i] = v2[i];
        mul(a, b, c, n, m);
        vi ret(c, c + n + m + 1);
        return ret;
    }
}NTT;
 
int C(int N, int M) {
    if (M > N || M < 0) return 0;
    return 1LL * fac[N] * ifac[M] % MOD * ifac[N - M] % MOD;
}
 
int N, v[400010];
 
vector<int>solve(int L, int R) {
    if (L == R) return {1, v[L]};
    int mid = (L + R) / 2; 
    auto v1 = solve(L, mid);
    auto v2 = solve(mid + 1, R);
    return NTT.conv(v1, v2);
}
 
int main() {
    fac[0] = ifac[0] = 1;
    for (int i=1;i<=MM;i++) {
        fac[i] = 1LL * fac[i - 1] * i % MOD;
        ifac[i] = quick_pow(fac[i], MOD - 2);
    }
    int T;
    scanf("%d",&T);
    while(T--) {
        scanf("%d",&N);
        for (int i=1;i<=N;i++) {
            scanf("%d",&v[i]);
        }
        auto ret = solve(1, N);
        int ans = 0;
        for (int i=1;i<=N;i++) {
            ans += 1LL * ret[i] * fac[i] % MOD * fac[N - i] % MOD;
            if (ans >= MOD) ans -= MOD;
        }
        ans = 1LL * ans * ifac[N] % MOD;
        printf("%d\n",ans);
    }
}