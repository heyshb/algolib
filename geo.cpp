#include <bits/stdc++.h>

using namespace std;

typedef double flt;
const flt eps = 1e-12;
char cor_buf[50];
flt cmp(flt a,flt b) {
	return fabs(a - b) >= eps + fabs(a) * eps ? a - b : 0;
}
int sign(flt x) {
	if (x < -eps) return -1;
	if (x > eps) return 1;
	return 0;
}
class point {
public:
	flt x,y;
	point(){}
	point(flt tx,flt ty):x(tx),y(ty) {}
	void read() {
		flt tx,ty;
		scanf("%lf%lf",&tx,&ty);
		x = tx;
		y = ty;
	}
	void print() {
		printf("(%.5lf,%.5lf)",x,y);
	}
	void println() {
		print();
		puts("");
	}
	
	friend point operator + (const point &a,const point &b) {
		return point(a.x + b.x, a.y + b.y);
	}
	friend point operator - (const point &a, const point &b) {
		return point(a.x - b.x, a.y - b.y);
	}
	friend flt operator % (const point &a, const point &b) { // a·b
		return a.x * b.x + a.y * b.y;
	}
	friend flt operator * (const point &a, const point &b) { // a x b
		return a.x * b.y - a.y * b.x;
	}
	friend point operator - (const point &a) {
		return point(-a.x, -a.y);
	}
	friend point operator * (const point &a,flt u) {
		return point(a.x * u, a.y * u);
	}
	friend bool operator == (const point &a,const point &b) {
		return !cmp(a,b);
	}
};

class cir {
	point O;
	flt r;
}

flt cmp(const point &a, const point &b) { // if (a == b), return 0, else not 0
		flt at = cmp(a.x,b.x);
		return !at?cmp(a.y,b.y):at;
	}
flt sqr(point a) {
	return a.x * a.x + a.y * a.y;
}
flt length(point a) {
	return sqrt(sqr(a));
}
int cmp_side(const point &a, const point &b) {
	return sign(cmp(a.x * b.y, ))
}

int main() {
	point p1,p2;
	p1.read();
	p2.read();
	point p;
	p = p1 + p2;
	p.println();
	p = p1 - p2;
	p.println();
	double ret;
	ret = p1 * p2;
	printf("%.5lf\n",ret);
	ret = p1 % p2;
	printf("%.5lf\n",ret);
}