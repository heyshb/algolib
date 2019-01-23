#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

typedef long long LL;
typedef pair<LL,LL> pll;
typedef pair<int,int> pii;

LL gcd(LL x,LL y) {
    return y==0?x:gcd(y,x%y);
}

LL lcm(LL x,LL y) {
    return x / gcd(x, y) * y;
}

/*
Find a solution of 
Ax + By = gcd(A,B) 
with minimum |x| + |y|

exgcd(B,A%B,tx,ty) 
--> B*tx + (A%B)*ty = g = A*x + B*y
--> A*x + B*y = B*tx + (A-(A/B)*B)*ty
--> A*x + B*y = B*tx + A*ty - (A/B)*B*ty
--> A*x + B*y = A*ty + B*(tx-ty*(A/B))
--> (x = ty, y = tx -  ty * (A / B))
*/
LL exgcd(LL A,LL B,LL &x,LL &y) {
    if (B == 0) {
        x = 1;
        y = 0;
        return A;
    }
    LL tx,ty;
    LL d = exgcd(B, A%B, tx, ty);
    x = ty;
    y = tx - ty * (A / B);
    return d;
}

//solve Ax + By = C with minimum x >= 0
//No solution: (-1, -1)
pll solve(LL A,LL B,LL C) {
    LL x,y;
    LL g = exgcd(A,B,x,y);
    if (C % g != 0) {
        return pll(-1,-1);
    }
    x *= C / g;
    y *= C / g;
    LL retx = x % (B / g);
    if (retx < 0) {
        retx += B / g;
    }
    LL rety = y - A / g * (retx - x) / (B / g); 
    //printf("%lld %lld %lld\n",retx,rety,A*retx+B*rety);
    return pll(retx,rety);
}

int main() {
    while(true) {
        LL A,B,C;
        scanf("%lld%lld%lld",&A,&B,&C);
        auto ret = solve(A,B,C);
        printf("%lld %lld\n",ret.first,ret.second);
    }
}